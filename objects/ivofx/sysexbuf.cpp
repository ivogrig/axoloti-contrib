#include "sysexbuf.h"


namespace ivofx_sysexbuf {

inline int32_t MAX(int32_t a, int32_t b) { return((a) > (b) ? a : b); }

char ByteRingBuffer::read()
{
	if (empty())
		return -1;

	char result = buffer[head];
	head = (head + 1) & mask;
	length = MAX ((length - 1) & mask, 0);
	isFull = false;
	return result;
}

bool ByteRingBuffer::empty()
{
	return (length <= 0) && !isFull;
}

bool ByteRingBuffer::full()
{
	return isFull;
}

void ByteRingBuffer::reset()
{
	head = tail = 0;
	mask = size-1;
	length = 0;
	isFull = false;
}

ByteRingBuffer::ByteRingBuffer()
{
	reset();
}

void ByteRingBuffer::setMemoryAddress(int8_t *pointer, const uint32_t &size)
{
	buffer = pointer;
	this->size = size;
}

void ByteRingBuffer::write(const char &value)
{
	if (length > mask) {
		isFull = true;
		return;
	}

	buffer[tail] = value;
	tail = (tail + 1) & mask;
	length++;
}

void ByteRingBuffer::write(char* sysexString, const uint32_t &length)
{
	for (int i=0; i<length; i++)
		write (sysexString[i]);
}

} // Namespace
