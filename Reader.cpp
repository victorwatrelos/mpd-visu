#include "Reader.hpp"

Reader::Reader(void)
{
	if ((this->_fp = fopen("/tmp/mpd.fifo", "r")) == NULL)
	{
		std::cout << "fopen fail" << std::endl;
	}
}

bool Reader::prepare_fft_input(pcm_stereo_sample *buffer,
		uint32_t sample_size,
		double *fftw_input,
		ChannelMode channel_mode)
{
	bool is_silent = true;

	for (auto i = 0u; i < sample_size; ++i)
	{
		switch (channel_mode)
		{
			case ChannelMode::Left:
				fftw_input[i] = buffer[i].l;
				break;
			case ChannelMode::Right:
				fftw_input[i] = buffer[i].r;
				break;
			case ChannelMode::Both:
				fftw_input[i] = buffer[i].l + buffer[i].r;
				break;
		}

		if (is_silent && fftw_input[i] > 0)
		{
			is_silent = false;
		}
	}

	return is_silent;
}

bool	Reader::getFullBuff(void)
{
	int8_t		*buff;
	this->read(
}

bool Reader::read(int8_t *buffer, size_t buff_size)
{
	int		c;
	size_t	i = 0;

	while (((c=getc(this->_fp)) != EOF) && i < buff_size)
	{
		    printf("%d", static_cast<int>(c));
		    buffer[i] = static_cast<char>(c);
		    i++;
	}
	return (true);
}

Reader::~Reader(void)
{
	fclose(this->_fp);
}
