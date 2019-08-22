#define TAGLIB_STATIC
#include "soundfile.h"

SoundFile::~SoundFile() {
	delete file_;
	delete stream_;
	file_ = NULL;
	stream_ = NULL;
}

SoundFile *SoundFile::Open(TagLib::IOStream *stream) {
	TagLib::File* file;
	SoundType type;

	const char *file_ext = strrchr(stream->name(), '.');
	if (file_ext == NULL) {
		return NULL;
	}
	if (iequals(file_ext, ".wav")) {
		file = new TagLib::RIFF::WAV::File(stream);
		type = WAV;
	}
	else if (iequals(file_ext, ".mp3")) {
		file = new TagLib::MPEG::File(stream, TagLib::ID3v2::FrameFactory::instance());
		type = MP3;
	}
	else {
		return NULL;
	}
	return new SoundFile(file, stream, type);
}

int SoundFile::length() {
	return file_->audioProperties()->length();
}

int SoundFile::lengthInMilliseconds() {
	return file_->audioProperties()->lengthInMilliseconds();
}

int SoundFile::bitrate() {
	return file_->audioProperties()->bitrate();
}

int SoundFile::sampleRate() {
	return file_->audioProperties()->sampleRate();
}

SoundFile::SoundFile(TagLib::File* file, TagLib::IOStream* stream, SoundType type) {
	file_ = file;
	stream_ = stream;
	type_ = type;
}
