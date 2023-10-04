//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

char    put_symbol32(const Elf32_Sym *symtab)
{
	switch (symtab->st_info)
	{
		case STT_FUNC:
			if ((symtab->st_info & STB_LOCAL))
				return ('t');
			else
				return ('T');
		case STT_FILE:
			return ('a');
	}
	return ('?');
}

void printDymSym32(const Elf32_Sym *dynsym, uint32_t dynsym_size, char *dynstr, char *symname)
{
	ft_printf ("\n# .dynsym entries:\n");
	for (uint32_t i = 0; i < (dynsym_size / sizeof(Elf32_Sym)); i++)
	{
		if (dynsym[i].st_value == 0)
		{
			ft_printf("%s ", NULL_PAD8);
		}
		else
		{
			char    buffer[9] = {0,0,0,0,0,0,0,0, 0};
			hex(buffer, 0, dynsym[i].st_value, B32);
			ft_printf("%s ", buffer);
		}
		symname = &dynstr[dynsym[i].st_name];
		if (*symname == '\x00')
			ft_printf("NULL\n");
		else
			ft_printf("%s\n", symname);
	}
}

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
	char            *value = NULL;
	char            *type = NULL;
	char            *symname = NULL;

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
		else if ((file->hdr_opt & A) && ft_strnstr((const char *)section_name, "debug", ft_strlen((const char *)section_name)))
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
		}
		else if ((file->hdr_opt & A) && ft_strnstr((const char *)section_name, "dbg", ft_strlen((const char *)section_name)))
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
		}
		else if ((file->hdr_opt & A) && ft_strnstr((const char *)section_name, "gdb", ft_strlen((const char *)section_name)))
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
		}
	}
	// TODO: remove printDymSym
	printDymSym32(dynsym, dynsym_size, dynstr, symname);
	ft_printf ("\n# .symtab entries:\n");
	for (uint32_t i = 0; i < (symtab_size / sizeof(Elf32_Sym)); i++)
	{
		if (symtab[i].st_value == '\x00')
		{
			value = ft_strdup(NULL_PAD8);
			if (!value)
			{
				file->hdr_opt |= ERROR;
				ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
				return ;
			}
		}
		else
		{
			char    buffer[9] = {0,0,0,0,0,0,0,0,0};
			hex(buffer, 0, symtab[i].st_value, B32);
			value = ft_strdup(buffer);
			if (!value)
			{
				file->hdr_opt |= ERROR;
				ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
				return ;
			}
		}
		type = ft_strdup(" ");
		if (!type)
		{
			file->hdr_opt |= ERROR;
			ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
			return ;
		}
		type[0] = put_symbol32(&symtab[i]);
		if (symstr[symtab[i].st_name] == '\x00')
			symname = ft_strdup("NULL");
		else
			symname = ft_strdup(&symstr[symtab[i].st_name]);
		if (!symname)
		{
			file->hdr_opt |= ERROR;
			ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
			return ;
		}
		add_node_obj(file, value, type, symname);
		if (file->hdr_opt & ERROR)
		{
			ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
			return ;
		}
	}
	if (file->hdr_opt & P)
		displayLstObj(&file->objlst);
	else if (file->hdr_opt & R)
		displayLstObjR(&file->objlst);
	else
		displayLstObjS(&file->objlst);
}
