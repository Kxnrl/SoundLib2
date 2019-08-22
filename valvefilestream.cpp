#define TAGLIB_STATIC
#include "valvefilestream.h"


ValveFileStream::~ValveFileStream() {
	basefilesystem->Close(handle_);
	handle_ = NULL;
}

ValveFileStream *ValveFileStream::Open(const char *filename, const char *mode, const char *pathID) {
	FileHandle_t handle = basefilesystem->Open(filename, mode, pathID);
	if (!handle) {
		return NULL;
	}
	return new ValveFileStream(handle, filename);
}

TagLib::FileName ValveFileStream::name() const {
	return filename_.c_str();
}

TagLib::ByteVector ValveFileStream::readBlock(unsigned long length) {
	TagLib::ByteVector bytes((unsigned int)length);
	int size = basefilesystem->Read(bytes.data(), length, handle_);
	bytes.resize(size);
	return bytes;
}

void ValveFileStream::writeBlock(const TagLib::ByteVector &data) {
}

void ValveFileStream::insert(const TagLib::ByteVector &data, unsigned long start, unsigned long replace) {
}

void ValveFileStream::removeBlock(unsigned long start, unsigned long length) {
}

bool ValveFileStream::readOnly() const {
	return true;
}

bool ValveFileStream::isOpen() const {
	return true;
}

void ValveFileStream::seek(long offset, TagLib::IOStream::Position p) {
	if (p == Position::Beginning) {
		basefilesystem->Seek(handle_, offset, FILESYSTEM_SEEK_HEAD);
	}
	else if (p == Position::Current) {
		basefilesystem->Seek(handle_, offset, FILESYSTEM_SEEK_CURRENT);
	}
	else if (p == Position::End) {
		basefilesystem->Seek(handle_, offset, FILESYSTEM_SEEK_TAIL);
	}
}

long ValveFileStream::tell() const {
	return basefilesystem->Tell(handle_);
}

long ValveFileStream::length() {
	return size_;
}

void ValveFileStream::truncate(long length) {
}

ValveFileStream::ValveFileStream(FileHandle_t handle, const char *filename) : handle_(handle), filename_(filename) {
	seek(0, Position::End);
	size_ = tell();
	seek(0, Position::Beginning);
}
