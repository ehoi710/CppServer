#pragma once

using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

inline const char* checkEnviroment() {
	uint16 value = 0x1234;
	uint8* pval = (uint8*)&value;

	if (pval[0] == 0x12) {
		return "BigEndian";
	}
	if (pval[0] == 0x34) {
		return "LittleEndian";
	}
}