#include <stdio.h>
#include <stdlib.h>		// exit
#include <unistd.h>		// read
#include <sys/stat.h>	// open	
#include <fcntl.h>		// open
#include <stdint.h>		// uint16_t
#include "fft.h"		// fast fourier transform
//#include "utils_curses.h"
#include "time.h"

/*FREQ		44100*/
#define N_SAMPLES 	512
/*FPS		FREQ/N_SAMPLES*/

int
main(int argc, char *argv[])
{
	int fifo, i, j;
	uint16_t buf[N_SAMPLES];
	unsigned int *fftBuf, *fftAvg;
	int			avgLen;

	while((fifo = open("/tmp/mpd.fifo", O_RDONLY)) == -1);

	while(read(fifo, (uint16_t*)buf, 2*N_SAMPLES) != 0){
		fftBuf = fast_fft(N_SAMPLES, (uint16_t*)buf);
		fftAvg = average_signal(fftBuf, N_SAMPLES, 20, &avgLen);	
		for (i = 0; i < N_SAMPLES; i++)
		{
			printf("%d", fftAvg[i]);
		}
		printf("\n");
		free(fftBuf);
		free(fftAvg);
	}
	close(fifo);

	return 0;
}
