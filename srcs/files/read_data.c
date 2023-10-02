//
// Created by tnoulens on 10/2/23.
//

#include "ft_nm.h"

uint16_t    readHalf(const uint16_t data, const int opt)
{
    uint16_t    res = data;

    if (opt & BEND)
        reverseEndianness(&res, sizeof(uint16_t));
    return (res);
}
