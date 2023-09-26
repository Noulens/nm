//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

void    printEhdr64(const t_file *file, const uint8_t *map)
{
	Elf64_Ehdr  *ehdr64 = NULL;

	(void)file;
	ehdr64 = (Elf64_Ehdr *)map;
	ft_printf("e_ident (Magic number): ");
	for (int i = 0; i < 16; i++)
	{
		ft_printf("%x ", ehdr64->e_ident[i]);
	}
	ft_printf("\n");
	ft_printf("%s ", "e_type (Object file type):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_type (Object file type):"));
	ft_printf("%d\n", ehdr64->e_type);
	ft_printf("%s ", "e_machine (Architecture):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_machine (Architecture):"));
	ft_printf("%d\n", ehdr64->e_machine);
	ft_printf("%s ", "e_version (Object file version):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_version (Object file version):"));
	ft_printf("%d\n", ehdr64->e_version);
	ft_printf("%s ", "e_entry (Entry point virtual address):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_entry (Entry point virtual address):"));
	ft_printf("0x%X\n", (unsigned long)ehdr64->e_entry);
	ft_printf("%s ", "e_phoff (Program header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phoff (Program header table file offset):"));
	ft_printf("%ld\n", (unsigned long)ehdr64->e_phoff);
	ft_printf("%s ", "e_shoff (Section header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shoff (Section header table file offset):"));
	ft_printf("%ld\n", (unsigned long)ehdr64->e_shoff);
	ft_printf("%s ", "e_flags (Processor-specific flags):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_flags (Processor-specific flags):"));
	ft_printf("0x%X\n", ehdr64->e_flags);
	ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_ehsize (ELF header size in bytes):"));
	ft_printf("%d\n", ehdr64->e_ehsize);
	ft_printf("%s ", "e_phentsize (Program header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phentsize (Program header table entry size):"));
	ft_printf("%d\n", ehdr64->e_phentsize);
	ft_printf("%s ", "e_phnum (Program header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phnum (Program header table entry count):"));
	ft_printf("%d\n", ehdr64->e_phnum);
	ft_printf("%s ", "e_shentsize (Section header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shentsize (Section header table entry size):"));
	ft_printf("%d\n", ehdr64->e_shentsize);
	ft_printf("%s ", "e_shnum (Section header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shnum (Section header table entry count):"));
	ft_printf("%d\n", ehdr64->e_shnum);
	ft_printf("%s ", "e_shstrndx (Section header string table index):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shstrndx (Section header string table index):"));
	ft_printf("%d\n", ehdr64->e_shstrndx);
}

void    printSht64(const t_file *file, const uint8_t *map)
{
	Elf64_Ehdr          *ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr          *sht = (Elf64_Shdr *)&map[ehdr->e_shoff];
	const uint8_t       *shstr = &map[sht[ehdr->e_shstrndx].sh_offset];
	int                 len;

	ft_printf("\nSection header string tab, first string is  NULL: '%s'\n", shstr);
	write(1, SPACE, PADDING_SHT);
	ft_printf("type\tsize\tflags\taddress\n");
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		len = ft_printf("[%d] %s ", i, &shstr[sht[i].sh_name]);
		write(1, SPACE, PADDING_SHT - (len > 30 ? 0 : len));
		switch (sht[i].sh_type)
		{
			case SHT_NULL: 		ft_printf("NULL");
				break;
			case SHT_PROGBITS:	ft_printf("PROGBITS");
				break;
			case SHT_SYMTAB:	ft_printf("SYMTAB");
				break;
			case SHT_STRTAB: 	ft_printf("STRTAB");
				break;
			case SHT_RELA:		ft_printf("RELA");
				break;
			case SHT_GNU_HASH:  ft_printf("GNU HASH");
				break;
			case SHT_DYNAMIC:   ft_printf("DYNAMIC");
				break;
			case SHT_NOTE:      ft_printf("NOTE");
				break;
			case SHT_NOBITS:    ft_printf("NOBITS");
				break;
			case SHT_REL:       ft_printf("REL");
				break;
			case SHT_SHLIB:     ft_printf("SHLIB");
				break;
			case SHT_DYNSYM:    ft_printf("DYNSYM");
				break;
			case SHT_LOPROC:    ft_printf("LOPROC");
				break;
			case SHT_HIPROC:    ft_printf("HIPROC");
				break;
			case SHT_LOUSER:    ft_printf("LOUSER");
				break;
			case SHT_HIUSER:    ft_printf("HIUSER");
				break;
			case SHT_GNU_verneed:   ft_printf("VERNEED");
				break;
			case SHT_INIT_ARRAY:   ft_printf("INIT_ARR.");
				break;
			case SHT_FINI_ARRAY:   ft_printf("FINI_ARR.");
				break;
			case SHT_GNU_versym:   ft_printf("VERSYM");
				break;
			default:			ft_printf("Unknown");
				break;
		}
		ft_printf("\t0x%x\t", sht[i].sh_size);
		if (sht[i].sh_flags & SHF_WRITE)
			ft_printf("W");
		if (sht[i].sh_flags & SHF_ALLOC)
			ft_printf("A");
		if (sht[i].sh_flags & SHF_EXECINSTR)
			ft_printf("X");
		if (sht[i].sh_flags & SHF_MERGE)
			ft_printf("M");
		else if (sht[i].sh_flags)
			ft_printf("+");
		else
			ft_printf("nof");
		ft_printf("\t0x%X", sht[i].sh_addr);
		ft_putchar_fd('\n', 1);
	}
	(void)file;
}

void    printPhdr64(t_file *file, uint8_t *map)
{
	Elf64_Ehdr  *ehdr = (Elf64_Ehdr *)map;
	Elf64_Phdr  *phdr = (Elf64_Phdr *)&map[ehdr->e_phoff];

	ft_printf("\nProgram Headers\n");
	ft_printf("Type"SPACE_PHDR"Offset\tVirtAd\tPhysAd\tFileSiz\tMemSiz\tAlign\tFlg\n\n");
	for (int i = 0; i < ehdr->e_phnum; i++)
	{
		int len;
		switch (phdr[i].p_type)
		{
			case PT_NULL:
				len = ft_printf("NULL");
				break;
			case PT_LOAD:
				len = ft_printf("LOAD");
				break;
			case PT_DYNAMIC:
				len = ft_printf("DYNAMIC");
				break;
			case PT_INTERP:
				len = ft_printf("INTERP");
				break;
			case PT_NOTE:
				len = ft_printf("NOTE");
				break;
			case PT_SHLIB:
				len = ft_printf("SHLIB");
				break;
			case PT_PHDR:
				len = ft_printf("PHDR");
				break;
			case PT_TLS:
				len = ft_printf("TLS");
				break;
			case PT_GNU_EH_FRAME:
				len = ft_printf("GNU_EH_FRAME");
				break;
			case PT_GNU_STACK:
				len = ft_printf("GNU_STACK");
				break;
			case PT_NUM :
				len = ft_printf("NUM");
				break;
			case PT_LOOS :
				len = ft_printf("LOOS");
				break;
			case PT_GNU_RELRO:
				len = ft_printf("GNU_RELRO");
				break;
			case PT_GNU_PROPERTY:
				len = ft_printf("GNU_PROPERTY");
				break;
			case PT_HIOS:
				len = ft_printf("HIOS");
				break;
			case PT_LOPROC:
				len = ft_printf("LOPROC");
				break;
			case PT_HIPROC:
				len = ft_printf("HIPROC");
				break;
		}
		write(1, SPACE, PADDING_PHDR - (len > 30 ? 0 : len));
		ft_printf("\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t",
		          phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr,
		          phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_align);
		if (phdr[i].p_flags & PF_X)
			ft_printf("%s", "E");
		if (phdr[i].p_flags & PF_W)
			ft_printf("%s", "W");
		if (phdr[i].p_flags & PF_R)
			ft_printf("%s", "R");
		else
			ft_printf("%s", "nof");
		ft_putchar_fd('\n', 1);
	}
	ft_putchar_fd('\n', 1);
	(void)file;
}

void    parseSymbols64(t_file *file, uint8_t *map)
{
	Elf64_Ehdr      *ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr      *sht = (Elf64_Shdr *)&map[ehdr->e_shoff];
	const uint8_t   *shstrtab = &map[sht[ehdr->e_shstrndx].sh_offset];
	Elf64_Sym       *symtab = NULL;
	uint64_t        symtab_size = 0;
	char            *symstr = NULL;
	Elf64_Sym       *dynsym = NULL;
	uint64_t        dynsym_size = 0;
	char            *dynstr = NULL;

	ft_printf("Sections containing symbols:\n");
	for (size_t i = 0; i < ehdr->e_shnum; i++)
	{
		const uint8_t   *section_name = &shstrtab[sht[i].sh_name];

		if (!ft_strncmp(".dynsym", (const char *)section_name, 7)
			&& sht[i].sh_type == SHT_DYNSYM)
		{
			ft_printf("%s shdr @ 0x%x\n", section_name, sht[i].sh_offset);
			dynsym = (Elf64_Sym *)&map[sht[i].sh_offset];
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
			symtab = (Elf64_Sym *)&map[sht[i].sh_offset];
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
	for (uint64_t i = 0; i < (dynsym_size / sizeof(Elf64_Sym)); i++)
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
	for (uint64_t i = 0; i < (symtab_size / sizeof(Elf64_Sym)); i++)
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
