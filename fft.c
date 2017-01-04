#include "fft.h"

#include <stdio.h>
#include <stdlib.h> // malloc
#include <unistd.h>		// read
#include <sys/stat.h>	// open	
#include <fcntl.h>		// open
#include <stdint.h>		// uint16_t
#include <math.h>
#include <complex.h>
#include <stdint.h>		// uint16_t

#define PI acos(-1.0) // even if it is defined as M_PI in math.h, this is more precise computationally
#define EVEN 0
#define ODD 1
#define N_SAMPLES 	512

typedef double complex cplx;

cplx *split_array(cplx *a, int len, int flag);
cplx *_fast_ft(cplx *compArray, int len);
void print_components(cplx *a, int len);
unsigned int amplitude(cplx c);
unsigned int* fast_fft(int inLen, uint16_t *sig);
unsigned int* average_signal(unsigned int *fftBuf, int inLen, int maxC, int *avgLen);
int fifo;
/* if flag is EVEN (0), it takes only the even elements
 * otherwise if flag is ODD (1) it takes only the odd ones
 */
cplx *split_array(cplx *a, int len, int flag)
{
	int i, cnt = 0;
	cplx *ret = malloc((len/2)*sizeof(cplx));

	for(i=0+flag; i<len; i=i+2){
		ret[cnt] = a[i];
		cnt++;
	}
	return ret;
}

/* recursively compute the fft on an array of complex numbers
 * this algorithm involves splitting the array in two parts each recursion
 * to be more efficient 
 */
cplx *_fast_ft(cplx *compArray, int len)
{
	cplx omegaN, omega;
	cplx *evenA, *oddA, *transformedA;
	int i;
	
	/*termination*/
	if(len == 1){
		return compArray;
	}
	
	omega = 1;
	omegaN = cexp((2)*(PI)*(I)/(len)); //the fourier coefficient
//	printf("omega: %g, pi: %g, I: %g, len: %g\n", creal(omegaN), (double)PI, (double)I, (double)len);
	
	evenA = _fast_ft(split_array(compArray, len, EVEN), len/2);
	oddA = _fast_ft(split_array(compArray, len, ODD), len/2);
	
	/*the final array*/
	transformedA = malloc(len*sizeof(cplx));

	for(i=0; i<(len/2); i++){
		transformedA[i] = evenA[i] + omega*oddA[i];
		transformedA[i+(len/2)] = evenA[i] - omega*oddA[i];
//		printf("transformed:%g, evenA: %g, oddA: %g\n", creal(transformedA[i+(len/2)]), creal(evenA[i]), creal(oddA[i]));
		omega = omegaN*omega;
	}
	free(evenA);
	free(oddA);
	free(compArray);
	return transformedA;
}

void
print_components(cplx *a, int len)
{
	int i;
	for(i=0; i<len; i++){
		/*creal and cimag extract the real and imaginary parts of a[i]*/
		fprintf(stdout, "%g, %g\n", creal(a[i]), cimag(a[i])); 
	}
	fprintf(stdout, "\n");
}

unsigned int
amplitude(cplx c)
{
	double sq;
	unsigned int res;
	
	/*compute amplitude*/
	sq = sqrt(pow(creal(c), 2) + pow(cimag(c), 2));
	res = round(20*log10(sq)); // dB scale
	return res;
}

unsigned int* 
fast_fft(int inLen, uint16_t *sig)
{
	int i;
	cplx *inputComponents;
	cplx *outputComponents;
	unsigned int *fftSig;

	if(inLen % 2 != 0){
		fprintf(stderr, "Note that the length of the array MUST be a power of 2.");
		exit(EXIT_FAILURE);
	}
	inputComponents = (cplx*)malloc((inLen)*sizeof(cplx));
	
	for(i=1; i<inLen; i++){
		inputComponents[i] = sig[i];
	}
	
	/*fprintf(stdout, "in:\n");*/
	/*print_components(inputComponents, inLen);*/
	
	outputComponents = _fast_ft(inputComponents, inLen);
	fftSig = calloc(inLen, sizeof(unsigned int));	
	/*fprintf(stdout, "out:\n");*/
	/*print_components(outputComponents, inLen);*/
	for(i=0; i<inLen; i++){
		fftSig[i] = amplitude(outputComponents[i]);
	}

	free(outputComponents);
	
	return fftSig;	
}

unsigned int*
average_signal(unsigned int *fftBuf, int inLen, int maxC, int *avgLen)
{
	unsigned int* fftAvg = malloc(inLen*sizeof(unsigned int));
	int i, j, step, k=0;
	unsigned int avg;

	if(maxC < 200){
		*avgLen = 128;
	} else {
		*avgLen = 512;
	}
	step = inLen/(2*(*avgLen)) + 1;
	for(i=0; i<inLen; i=i+step){
		avg = 0;
		for(j=0; j<step; j++){
			avg += fftBuf[i+j];	
		}
		fftAvg[k] = avg/step - 80; //the 80 is a correction for the display
//		printf("|%u|", fftAvg[k]);
		k++;
	}
//	printf("\n");
	return fftAvg;
}

void	openFifo()
{
	while((fifo = open("/tmp/mpd.fifo", O_RDONLY)) == -1);
}

void	closeFifo()
{
	close(fifo);
}

unsigned int	*getAvg()
{
	int  i;
	uint16_t buf[N_SAMPLES];
	unsigned int *fftBuf, *fftAvg;
	int			avgLen;
	int			ret;


	while((ret = read(fifo, (uint16_t*)buf, (2 * N_SAMPLES))) != 0) {
		//printf("%u|", ret);
		for (i = 0; i < N_SAMPLES; i++)
		{
		//	printf("u%u|", buf[i]);
		}
	//	tot_size += ret;
		//printf("tot_size: %d\n", tot_size);
	//	if (tot_size < 2 * N_SAMPLES)
	//	{
	//		continue ;
	//	}
	//	tot_size = 0;
		fftBuf = fast_fft(N_SAMPLES, buf);
		for (i = 0; i < N_SAMPLES; i++)
		{
			printf("t%u|", fftBuf[i]);
		}
		//printf("\n");
		fftAvg = average_signal(fftBuf, N_SAMPLES, 238, &avgLen);	
		free(fftBuf);
	//	free(fftAvg);
		return fftAvg;
	}
	return NULL;
}



