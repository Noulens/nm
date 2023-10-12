//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

const char  *nameFromSymbol64(Elf64_Ehdr *ehdr, Elf64_Shdr *sht, const uint8_t *shstrtab, const Elf64_Sym *symtab, uint64_t i, int opt)
{
	Elf64_Section   section_index = readHalf(symtab[i].st_shndx, opt);
	// Check if the section index is valid
	if (section_index < readHalf(ehdr->e_shnum, opt))
	{
		Elf64_Shdr  *section_header = &sht[section_index];
		// Check if the section name is not a null pointer
		if (shstrtab != NULL)
		{
			const uint8_t *sect_name = &shstrtab[readWord(section_header->sh_name, opt)];
			// Check if the section name is not a null-terminated string
			if (sect_name != NULL && sect_name[0] != '\0')
				return (const char *)sect_name;
		}
	}
	return ("");
}

const char  *nameFromSymbol32(Elf32_Ehdr *ehdr, Elf32_Shdr *sht, const uint8_t *shstrtab, const Elf32_Sym *symtab, uint32_t i, int opt)
{
	Elf32_Section   section_index = readHalf(symtab[i].st_shndx, opt);
	// Check if the section index is valid
	if (section_index < readHalf(ehdr->e_shnum, opt))
	{
		Elf32_Shdr  *section_header = &sht[section_index];
		// Check if the section name is not a null pointer
		if (shstrtab != NULL)
		{
			const uint8_t *sect_name = &shstrtab[readWord(section_header->sh_name, opt)];
			// Check if the section name is not a null-terminated string
			if (sect_name != NULL && sect_name[0] != '\0')
				return (const char *)sect_name;
		}
	}
	return ("");
}

static void	to_hex(unsigned long addr, char *digit, int i)
{
		digit[i] = (char)(addr % 16);
		if (digit[i] < 10)
			digit[i] += 48;
		else
			digit[i] += 87;
}

void    hex(char *str, uint64_t nbr64, uint32_t nbr32, int opt)
{
	int				i;
	int				count;
	char			addr_digit64[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char            addr_digit32[9] = {0,0,0,0,0,0,0,0};

	i = 0;
	if (opt & B64)
	{
		if (nbr64 == 0)
		{
			ft_memset(str, '0', 16);
			return;
		}
		while (nbr64)
		{
			to_hex(nbr64, addr_digit64, i);
			++i;
			nbr64 /= 16;
		}
		count = 16 - (int) ft_strlen(addr_digit64);
		for (int j = 0; j < count; j++)
			str[j] = '0';
		while (--i >= 0)
			str[count++] = addr_digit64[i];
	}
	else
	{
		if (nbr32 == 0)
		{
			ft_memset(str, '0', 8);
			return;
		}
		while (nbr32)
		{
			to_hex(nbr32, addr_digit32, i);
			++i;
			nbr32 /= 16;
		}
		count = 8 - (int) ft_strlen(addr_digit32);
		for (int j = 0; j < count; j++)
			str[j] = '0';
		while (--i >= 0)
			str[count++] = addr_digit32[i];
	}
}
