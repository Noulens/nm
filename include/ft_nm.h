//
// Created by tnoulens on 9/8/23.
//

#ifndef FT_NM_H
# define FT_NM_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <elf.h>
#include "libft.h"
#include "struct.h"

#define IS_ELF "File is an ELF file\n"
#define NOT_ELF "ft_nm: %s: file format not recognized"
#define INVALID_OPT "ft_nm: invalid option -- %c\n"
#define SYS_ERR "ft_nm: '%s': %s"

void    free_list(t_list **begin);
void    proceed(t_args *args);
void    printEhdr(const t_file *file, const uint8_t *map);

#endif //FT_NM_H
