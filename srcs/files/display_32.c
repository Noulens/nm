//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

void    parseSymbols32(t_file *file, uint8_t *map)
{
	Elf32_Ehdr      *ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr      *sht = (Elf32_Shdr *)&map[ehdr->e_shoff];
	const uint8_t   *shstrtab = &map[sht[ehdr->e_shstrndx].sh_offset];
	Elf32_Sym       *symtab = NULL;
	uint32_t        symtab_size = 0;
	char            *symstr = NULL;
	Elf32_Sym       *dynsym = NULL;
	uint32_t        dynsym_size = 0;
	char            *dynstr = NULL;

	ft_printf("Sections containing symbols:\n");
	for (size_t i = 0; i < ehdr->e_shnum; i++)
	{
		const uint8_t   *section_name = &shstrtab[sht[i].sh_name];

		if (!ft_strncmp(".dynsym", (const char *)section_name, 7)
		    && sht[i].sh_type == SHT_DYNSYM)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
			dynsym = (Elf32_Sym *)&map[sht[i].sh_offset];
			dynsym_size = sht[i].sh_size;
		}
		else if (!ft_strncmp(".dynstr", (const char *)section_name, 7)
		         && sht[i].sh_type == SHT_STRTAB)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
			dynstr = (char *)&map[sht[i].sh_offset];
		}
		else if (!ft_strncmp(".symtab", (const char *)section_name, 7)
		         && sht[i].sh_type == SHT_SYMTAB)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
			symtab = (Elf32_Sym *)&map[sht[i].sh_offset];
			symtab_size = sht[i].sh_size;
		}
		else if (!ft_strncmp(".strtab", (const char *)section_name, 7)
		         && sht[i].sh_type == SHT_STRTAB)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
			symstr = (char *)&map[sht[i].sh_offset];
		}
	}
	ft_printf ("\n# .dynsym entries:\n");
	for (uint32_t i = 0; i < (dynsym_size / sizeof(Elf32_Sym)); i++)
	{
		if (dynsym[i].st_value == 0)
		{
			ft_putstr_fd(NULL_PAD, 1);
			ft_putchar_fd(' ', 1);
		}
		else
		{
			char    buffer[16];
			hex(buffer, dynsym[i].st_value);
			write(1, ZERO_PAD, 16 - ft_strlen(buffer));
			ft_printf("%s ", buffer);
		}
		char    *symname = &dynstr[dynsym[i].st_name];
		if (*symname == '\x00')
			ft_printf("NULL\n");
		else
			ft_printf("%s\n", symname);
	}
	ft_printf ("\n# .symtab entries:\n");
	for (uint32_t i = 0; i < (symtab_size / sizeof(Elf32_Sym)); i++)
	{
		if (symtab[i].st_value == 0)
		{
			ft_putstr_fd(NULL_PAD, 1);
			ft_putchar_fd(' ', 1);
		}
		else
		{
			char    buffer[16];
			hex(buffer, symtab[i].st_value);
			write(1, ZERO_PAD, 16 - ft_strlen(buffer));
			ft_printf("%s ", buffer);
		}
		char    *symname = &symstr[symtab[i].st_name];
		if (*symname == '\x00')
			ft_printf("NULL ");
		else
			ft_printf("%s ", symname);
		ft_printf("%c\n", (char)symtab[i].st_info);
	}
	(void)file;
}
