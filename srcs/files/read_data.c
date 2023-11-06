//
// Created by tnoulens on 10/2/23.
//

#include "ft_nm.h"

uint16_t    readHalf(const uint16_t data, const int opt)
{
    uint16_t    res = data;

    if (((opt & LEND) && !(opt & L_ARCH)) || ((opt & BEND) && (opt & L_ARCH)))
        reverseEndianness(&res, sizeof(uint16_t));
    return (res);
}

uint32_t    readWord(const uint32_t data, const int opt)
{
	uint32_t    res = data;

	if (((opt & LEND) && !(opt & L_ARCH)) || ((opt & BEND) && (opt & L_ARCH)))
		reverseEndianness(&res, sizeof(uint32_t));
	return (res);
}

int32_t    readSWord(const int32_t data, const int opt)
{
	int32_t    res = data;

	if (((opt & LEND) && !(opt & L_ARCH)) || ((opt & BEND) && (opt & L_ARCH)))
		reverseEndianness(&res, sizeof(int32_t));
	return (res);
}

uint64_t    readXWord(const uint64_t data, const int opt)
{
	uint64_t    res = data;

	if (((opt & LEND) && !(opt & L_ARCH)) || ((opt & BEND) && (opt & L_ARCH)))
		reverseEndianness(&res, sizeof(uint64_t));
	return (res);
}

int64_t    readXSWord(const int64_t data, const int opt)
{
	int64_t    res = data;

	if (((opt & LEND) && !(opt & L_ARCH)) || ((opt & BEND) && (opt & L_ARCH)))
		reverseEndianness(&res, sizeof(int64_t));
	return (res);
}
