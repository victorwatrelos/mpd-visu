#include <stdio.h>
#include "fft.h"		// fast fourier transform
//#include "utils_curses.h"
#include "time.h"
#include "Spectre.hpp"

/*FREQ		44100*/
/*FPS		FREQ/N_SAMPLES*/

void	Spectre::_addRect(int height, int col)
{
	emit newRect(QRect(col * 10, 1, 10, height - 600), col);
}

void	Spectre::process(void)
{
	this->run();
}

Spectre::~Spectre(void)
{
}

void	Spectre::run()
{
	int i;
	unsigned int *fftAvg;

	openFifo();

	while (1)
	{
		fftAvg = getAvg();
		for (i = 0; i < 238; i++)
		{
			this->_addRect(fftAvg[i], i);
			//	printf("%d:%u|", i, (fftAvg[i]));
		}
		emit update();
		free(fftAvg);
	}
	closeFifo();
}
