//Endian
uint32 htonl(uint32 x) {
	union {
		uint32 result;
		uint8 result_array[4];
	};
	result_array[0] = static_cast<uint8>(x >> 24);
	result_array[1] = static_cast<uint8>((x >> 16) & 0xFF);
	result_array[2] = static_cast<uint8>((x >> 8) & 0xFF);
	result_array[3] = static_cast<uint8>(x & 0xFF);

	return result;
}

inline void dtSwapByte(unsigned char* a, unsigned char* b)
{
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

inline void dtSwapEndian(unsigned short* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+1);
}

inline void dtSwapEndian(short* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+1);
}

inline void dtSwapEndian(unsigned int* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

inline void dtSwapEndian(int* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

inline void dtSwapEndian(float* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

