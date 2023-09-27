//
// Created by tnoulens on 9/8/23.
//

#ifndef FT_NM_H
# define FT_NM_H

#ifndef PT_GNU_PROPERTY
# define PT_GNU_PROPERTY	0x6474e553	/* GNU property */
#endif

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
#define SPACE "                                                    "
#define SPACE_PHDR "            "
#define ZERO_PAD "0000000000000000"
#define NULL_PAD "                "
#define PADDING_EHDR 52
#define PADDING_SHT 30
#define PADDING_PHDR 13

t_args  init_args();
void    check_args(int ac, char **av, t_args *args);
void    free_list(t_list **begin);
void    proceed(t_args *args);
void    printEhdr64(const t_file *file, const uint8_t *map);
void    printEhdr32(const t_file *file, const uint8_t *map);
void    printSht64(const t_file *file, const uint8_t *map);
void    printSht32(const t_file *file, const uint8_t *map);
void    printPhdr32(t_file *file, uint8_t *map);
void    printPhdr64(t_file *file, uint8_t *map);
void    parseSymbols64(t_file *file, uint8_t *map);
void    parseSymbols32(t_file *file, uint8_t *map);
void    hex(char *str, unsigned long nbr);

#endif //FT_NM_H
