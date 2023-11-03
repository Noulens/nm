//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

char	put_symbol32(const Elf32_Sym *symtab, const Elf32_Shdr *sht, int opt)
{
	char	ret = '\0';
	uint8_t	c = symtab->st_info;

	if (ELF32_ST_BIND(c) == STB_GNU_UNIQUE)
		ret = 'u';
	else if (ELF32_ST_BIND(c) == STB_WEAK && ELF32_ST_TYPE(c) == STT_OBJECT)
		ret = readHalf(symtab->st_shndx, opt) == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(c) == STB_WEAK)
		ret = readHalf(symtab->st_shndx, opt) == SHN_UNDEF ? 'w' : 'W';
	else if (readHalf(symtab->st_shndx, opt) == SHN_UNDEF)
		ret = 'U';
	else if (readHalf(symtab->st_shndx, opt) == SHN_ABS)
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'a';
		else
			ret = 'A';
	}
	else if (readHalf(symtab->st_shndx, opt) == SHN_COMMON)
		ret = 'C';
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_NOBITS
	         && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'b';
		else
			ret = 'B';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_PROGBITS
	         && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'd';
		else
			ret = 'D';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_DYNAMIC
			&& ((readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & (SHF_ALLOC))
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) == (SHF_ALLOC | SHF_WRITE)))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'd';
		else
			ret = 'D';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_PROGBITS
	         && ((readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_ALLOC)
			 && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_EXECINSTR)))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 't';
		else
			ret = 'T';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_NOTE
			&& (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_ALLOC))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'r';
		else
			ret = 'R';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_PROGBITS
	         && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_ALLOC))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'r';
		else
			ret = 'R';
	}
	else if ((readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_DYNSYM
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_STRTAB
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_GNU_HASH
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_GNU_verneed
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_GNU_versym
			|| readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_REL)
	         && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_ALLOC))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'r';
		else
			ret = 'R';
	}
	else if (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_PROGBITS
	         && (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) == 0
			 || (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) & SHF_MERGE)))
	{
		ret = 'N';
	}
	else if ((readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_INIT_ARRAY
			&& readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) == (SHF_WRITE | SHF_ALLOC))
			|| (readWord(sht[readHalf(symtab->st_shndx, opt)].sh_type, opt) == SHT_FINI_ARRAY
			&& readWord(sht[readHalf(symtab->st_shndx, opt)].sh_flags, opt) == (SHF_WRITE | SHF_ALLOC)))
	{
		if (ELF32_ST_BIND(c) == STB_LOCAL)
			ret = 'd';
		else
			ret = 'D';
	}
	else if (ELF32_ST_TYPE(c) == STT_NOTYPE)
	{
		ret = 'n';
	}
	else
		ret = '?';
	return (ret);
}

void	parseSymbols32(t_file *file, uint8_t *map)
{
	int				opt = file->hdr_opt;
	Elf32_Ehdr		*ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr		*sht = (Elf32_Shdr *)&map[readXWord(ehdr->e_shoff, opt)];
	const uint8_t	*shstrtab = &map[readXWord(sht[readHalf(ehdr->e_shstrndx, opt)].sh_offset, opt)];
	Elf32_Sym		*symtab = NULL;
	uint32_t		symtab_size = 0;
	char			*symstr = NULL;
	char			*value = NULL;
	char			*type = NULL;
	char			*symname = NULL;

	(void)((opt & V) && ft_printf("Sections containing symbols:\n"));
	for (size_t i = 0; i < readHalf(ehdr->e_shnum, opt); i++)
	{
		const uint8_t *section_name = &shstrtab[readWord(sht[i].sh_name, opt)];
		// I removed the code snippet for displaying dynamic objects, it is at the end of the file
		if (!ft_strncmp(".symtab", (const char *) section_name, 7)
			&& readWord(sht[i].sh_type, opt) == SHT_SYMTAB)
		{
			(void)((opt & V) && ft_printf("%s shdr @ 0x%x\n", section_name, readXWord(sht[i].sh_offset, opt)));
			symtab = (Elf32_Sym *) &map[readXWord(sht[i].sh_offset, opt)];
			symtab_size = readXWord(sht[i].sh_size, opt);
		}
		else if (!ft_strncmp(".strtab", (const char *) section_name, 7)
			&& readWord(sht[i].sh_type, opt) == SHT_STRTAB)
		{
			(void)((opt & V) && ft_printf("%s shdr @ 0x%x\n", section_name, readXWord(sht[i].sh_offset, opt)));
			symstr = (char *) &map[readXWord(sht[i].sh_offset, opt)];
		}
		else if ((file->hdr_opt & A) && (file->hdr_opt & V)
			&& ft_strnstr((const char *) section_name, "debug", ft_strlen((const char *) section_name)))
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, readXWord(sht[i].sh_offset, opt));
		}
	}
	(void)((opt & V) && ft_printf ("\n# .symtab entries:\n"));
	for (uint32_t i = 0; i < (symtab_size / sizeof(Elf32_Sym)); i++)
	{
		char c = put_symbol32(&symtab[i], sht, opt);
		// Manuel adjustments, look for other symbols from section name
		if (c== '?')
		{
			if (!ft_strncmp(".eh_frame", nameFromSymbol32(ehdr, sht, shstrtab,symtab, i, opt), 9))
				c = 'p';
		}
		if (c == 'N')
		{
			if (!ft_strncmp(".comment", nameFromSymbol32(ehdr, sht, shstrtab,symtab, i, opt), 9)
				|| !ft_strncmp(".note.GNU-stack", nameFromSymbol32(ehdr, sht, shstrtab,symtab, i, opt), 15))
				c = 'n';
		}
		if ((opt & U) && isUndefined(c))
			continue ;
		if ((opt & G) && isGlobal(c))
			continue ;
		if (!(opt & A) && isDebug(c))
			continue ;
		// Undefined symbols with no name are skipped (except if -a is specified and the symbol is not U)
		if (symstr[readWord(symtab[i].st_name, opt)] == '\x00'
			&& (c == 'U' || (!(opt & A))))
			continue ;
		// Undefined symbols with no address have a blank padding
		if (isNoAddress(c) && readXWord(symtab[i].st_value, opt) == '\x00')
		{
			value = ft_strdup(NULL_PAD8);
			if (!value)
				return (file->hdr_opt |= ERROR, ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno)), (void)0);
		}
		else
		{
			char	buffer[9] = "\0\0\0\0\0\0\0\0\0";
			hex(buffer, 0, symtab[i].st_value, B32);
			value = ft_strdup(buffer);
			if (!value)
				return (file->hdr_opt |= ERROR, ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno)), (void)0);
		}
		type = ft_strdup(" ");
		if (!type)
			return (file->hdr_opt |= ERROR, ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno)), (void)0);
		type[0] = c;
		if (symstr[readWord(symtab[i].st_name, opt)] == '\x00')
			symname = ft_strdup((const char *)nameFromSymbol32(ehdr, sht, shstrtab, symtab, i, opt));
		else
			symname = ft_strdup(&symstr[readWord(symtab[i].st_name, opt)]);
		if (!symname)
			return (file->hdr_opt |= ERROR, ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno)), (void)0);
		add_node_obj(file, value, type, symname);
		if (file->hdr_opt & ERROR)
			return (ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno)), (void)0);
	}
	if (!ft_lstsize(file->objlst))
		ft_fprintf(2,"ft_nm: %s: no symbols\n", file->path);
	if (file->hdr_opt & P)
		displayLstObj(&file->objlst);
	else if (file->hdr_opt & R)
		displayLstObjR(&file->objlst);
	else
		displayLstObjS(&file->objlst);
}

/*
 * Insert this code snippet and call the function printDyn to print dynamic symbols
 * */
/*
	Elf32_Sym		*dynsym = NULL;
	uint32_t		dynsym_size = 0;
	char			*dynstr = NULL;

	if (!ft_strncmp(".dynsym", (const char *) section_name, 7)
		    && readWord(sht[i].sh_type, opt) == SHT_DYNSYM)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, readXWord(sht[i].sh_offset, opt));
			dynsym = (Elf32_Sym *) &map[readXWord(sht[i].sh_offset, opt)];
			dynsym_size = readXWord(sht[i].sh_size, opt);
		}
		else if (!ft_strncmp(".dynstr", (const char *) section_name, 7)
		         && readWord(sht[i].sh_type, opt) == SHT_STRTAB)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, readXWord(sht[i].sh_offset, opt));
			dynstr = (char *) &map[readXWord(sht[i].sh_offset, opt)];
		}
		printDymSym32(dynsym, dynsym_size, dynstr, symname, opt);
*/
