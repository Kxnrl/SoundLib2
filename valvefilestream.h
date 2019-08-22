#ifndef VALVE_FILESTREAM_INCLUDE_H_
#define VALVE_FILESTREAM_INCLUDE_H_

#include <taglib/tag.h>
#include <taglib/tiostream.h>

#include <filesystem.h>

#include <string>

extern IBaseFileSystem *basefilesystem;

class ValveFileStream : public TagLib::IOStream {
public:
	~ValveFileStream();
	static ValveFileStream *Open(const char *filename, const char *mode, const char *pathID = 0);
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
	ValveFileStream(FileHandle_t handle, const char *filename);
private:
	FileHandle_t handle_;
	std::string filename_;
	long size_;
};

#endif // VALVE_FILESTREAM_INCLUDE_H_