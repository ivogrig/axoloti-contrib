#pragma once

namespace ivofx_sysexbuf {

class ByteRingBuffer
{
public:
	ByteRingBuffer();
	void setMemoryAddress (int8_t* pointer, const uint32_t& size);
	void write (const char& value);
	void write (char*sysexString, const uint32_t& length);
	char read ();
	bool empty();
	bool full();

private:
	void reset();

	int8_t* buffer = nullptr;
	uint32_t head = 0;
	uint32_t tail = 0;
	uint32_t size = 1 << 12;
	uint32_t mask = size - 1;
	uint32_t length = 0;
	bool isFull = false;
};


} // Namespace
