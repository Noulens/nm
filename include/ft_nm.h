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
#define NULL_PAD16 "                "
#define NULL_PAD8 "        "
#define PADDING_EHDR 52
#define PADDING_SHT 30
#define PADDING_PHDR 13

t_args  init_args();
void    add_node_obj(t_file *file, char *value, char *type, char *name);
void    check_args(int ac, char **av, t_args *args);
void    free_list(t_list **begin);
void    free_list_obj(t_list **begin);
void    proceed(t_args *args);
void    printEhdr64(t_file *file, const uint8_t *map);
void    printEhdr32(const t_file *file, const uint8_t *map);
void    printSht64(const t_file *file, const uint8_t *map);
void    printSht32(const t_file *file, const uint8_t *map);
void    printPhdr32(t_file *file, uint8_t *map);
void    printPhdr64(t_file *file, uint8_t *map);
void    parseSymbols64(t_file *file, uint8_t *map);
void    parseSymbols32(t_file *file, uint8_t *map);
void    hex(char *str, uint64_t nbr64, uint32_t nbr32, int opt);
void    displayLstObj(t_list **begin);
void    displayLstObjR(t_list **begin);
void    displayLstObjS(t_list **begin);
const char *nameFromSymbol64(Elf64_Ehdr *ehdr, Elf64_Shdr *sht, const uint8_t *shstrtab, const Elf64_Sym *symtab, uint64_t i, int opt);
const char *nameFromSymbol32(Elf32_Ehdr *ehdr, Elf32_Shdr *sht, const uint8_t *shstrtab, const Elf32_Sym *symtab, uint32_t i, int opt);
int isGlobal(uint8_t c);
int isUndefined(uint8_t c);
uint16_t    readHalf(uint16_t data, int opt);
uint32_t    readWord(uint32_t data, int opt);
int32_t    readSWord(int32_t data, int opt);
uint64_t    readXWord(uint64_t data, int opt);
int64_t    readXSWord(int64_t data, int opt);

#endif //FT_NM_H
