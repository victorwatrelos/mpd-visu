#ifndef SPECTRE_HPP
# define SPECTRE_HPP

# include "fft.h"		// fast fourier transform
# include <stdio.h>
# include <stdlib.h>		// exit
# include <unistd.h>		// read
# include <sys/stat.h>	// open	
# include <fcntl.h>		// open
# include <stdint.h>		// uint16_t
# include "time.h"
# include <QObject>
# include <QRect>

class	Spectre : public QObject
{
	Q_OBJECT
	public slots:
		void process();
	signals:
		void newRect(QRect rect, int col);
		void	update(void);
	public:
		void run();
		virtual ~Spectre(void);
	private:
		void		_addRect(int height, int col);

};

#endif
