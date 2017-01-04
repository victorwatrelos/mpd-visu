#ifndef READER_HPP
# define READER_HPP

# include <stdio.h>
# include <sys/types.h>
# include <iostream>

class Reader
{
	public:
		Reader(void);
		virtual ~Reader(void);
		bool	read(int8_t *buffer, size_t buff_size);
	private:
		FILE	*_fp;
};

#endif
