#define TAGLIB_STATIC
#include "systemfilestream.h"

SystemFileStream::~SystemFileStream() {
	fclose(file_);
	file_ = NULL;
}

SystemFileStream *SystemFileStream::Open(const char *filename, const char *mode) {
	FILE* file = fopen(filename, mode);
	if (!file) {
		return NULL;
	}
	return new SystemFileStream(file, filename);
}

TagLib::FileName SystemFileStream::name() const {
	return filename_.c_str();
}

TagLib::ByteVector SystemFileStream::readBlock(unsigned long length) {
	TagLib::ByteVector bytes((unsigned int)length);
	int size = fread(bytes.data(), length, 1, file_);
	bytes.resize(size);
	return bytes;
}

void SystemFileStream::writeBlock(const TagLib::ByteVector &data) {
}

void SystemFileStream::insert(const TagLib::ByteVector &data, unsigned long start, unsigned long replace) {
}

void SystemFileStream::removeBlock(unsigned long start, unsigned long length) {
}

bool SystemFileStream::readOnly() const {
	return true;
}

bool SystemFileStream::isOpen() const {
	return true;
}

void SystemFileStream::seek(long offset, TagLib::IOStream::Position p) {
	if (p == Position::Beginning) {
		fseek(file_, offset, SEEK_SET);
	}
	else if (p == Position::Current) {
		fseek(file_, offset, SEEK_CUR);
	}
	else if (p == Position::End) {
		fseek(file_, offset, SEEK_END);
	}
}

long SystemFileStream::tell() const {
	return ftell(file_);
}

long SystemFileStream::length() {
	return size_;
}

void SystemFileStream::truncate(long length) {
}

SystemFileStream::SystemFileStream(FILE* file, const char *filename) : file_(file), filename_(filename) {
	seek(0, Position::End);
	size_ = tell();
	seek(0, Position::Beginning);
}
