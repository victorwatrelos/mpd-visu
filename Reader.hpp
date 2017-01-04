class Reader
{
	public:
		Reader::Reader(void);
		bool	read(int8_t *buffer, int buff_size);
	private:
		FILE	*_fp;
};
