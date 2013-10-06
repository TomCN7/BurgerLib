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
