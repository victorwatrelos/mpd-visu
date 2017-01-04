#ifndef MY_TYPES_H
# define MY_TYPES_H

namespace MyTypes
{
	struct stereo_sample_frame
	{
		int16_t l;
		int16_t r;
	};

	using pcm_stereo_sample = struct stereo_sample_frame;
}

#endif
