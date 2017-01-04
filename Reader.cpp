#include "Reader.cpp"

Reader::Reader(void)
{
	FILE *fp;
	fp = fopen("/tmp/mpd.fifo", "r");
}

bool Reader::read(int8_t *buffer, size_t buff_size)
{
	char c;
	while((c=getc(fp)) != EOF)
	{
		    printf("%c",c);
	}
	fclose(fp);
}
