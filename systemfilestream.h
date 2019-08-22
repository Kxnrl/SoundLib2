#ifndef SYSTEM_FILESTREAM_INCLUDE_H_
#define SYSTEM_FILESTREAM_INCLUDE_H_

#include <taglib/tag.h>
#include <taglib/tiostream.h>

#include <stdio.h>

#include <string>

class SystemFileStream : public TagLib::IOStream {
public:
	~SystemFileStream();
	static SystemFileStream *Open(const char *filename, const char *mode);
	virtual TagLib::FileName name() const;
	virtual TagLib::ByteVector readBlock(unsigned long length);
	virtual void writeBlock(const TagLib::ByteVector &data);
	virtual void insert(const TagLib::ByteVector &data, unsigned long start, unsigned long replace);
	virtual void removeBlock(unsigned long start, unsigned long length);
	virtual bool readOnly() const;
	virtual bool isOpen() const;
	virtual void seek(long offset, TagLib::IOStream::Position p);
	virtual long tell() const;
	virtual long length();
	virtual void truncate(long length);
private:
	SystemFileStream(FILE* file, const char *filename);
private:
	FILE * file_;
	std::string filename_;
	long size_;
};

#endif // SYSTEM_FILESTREAM_INCLUDE_H_