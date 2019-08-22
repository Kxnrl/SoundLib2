#ifndef SOUNDFILE_INCLUDE_H_
#define SOUNDFILE_INCLUDE_H_

#include <taglib/tag.h>
#include <taglib/tiostream.h>
#include <taglib/wavfile.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2framefactory.h>

#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>

struct iequal
{
	bool operator()(int c1, int c2) const
	{
		return std::toupper(c1) == std::toupper(c2);
	}
};

static inline bool iequals(const std::string& str1, const std::string& str2)
{
	return std::equal(str1.begin(), str1.end(), str2.begin(), iequal());
}

class SoundFile
{
public:
	enum SoundType {
		WAV,
		MP3,
	};
	~SoundFile();
	static SoundFile *Open(TagLib::IOStream *stream);
	int length();
	int lengthInMilliseconds();
	int bitrate();
	int sampleRate();

private:
	SoundFile(TagLib::File* file, TagLib::IOStream* stream, SoundType type);
private:
	TagLib::File* file_;
	TagLib::IOStream* stream_;
	SoundType type_;
};

#endif