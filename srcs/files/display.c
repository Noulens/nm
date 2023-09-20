//
// Created by tnoulens on 9/19/23.
//

#include "ft_nm.h"

void    printEhdr32(const t_file *file, const uint8_t *map)
{
	Elf32_Ehdr  *ehdr32 = NULL;

	(void)file;
	ehdr32 = (Elf32_Ehdr *)map;
	ft_printf("e_ident (Magic number): ");
	for (int i = 0; i < 16; i++)
	{
		ft_printf("%x ", ehdr32->e_ident[i]);
	}
	ft_printf("\n");
	ft_printf("%s ", "e_type (Object file type):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_type (Object file type):"));
	ft_printf("%d\n", ehdr32->e_type);
	ft_printf("%s ", "e_machine (Architecture):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_machine (Architecture):"));
	ft_printf("%d\n", ehdr32->e_machine);
	ft_printf("%s ", "e_version (Object file version):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_version (Object file version):"));
	ft_printf("%d\n", ehdr32->e_version);
	ft_printf("%s ", "e_entry (Entry point virtual address):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_entry (Entry point virtual address):"));
	ft_printf("0x%X\n", (unsigned long)ehdr32->e_entry);
	ft_printf("%s ", "e_entry (Entry point virtual address):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_entry (Entry point virtual address):"));
	ft_printf("%ld\n", (unsigned long)ehdr32->e_phoff);
	ft_printf("%s ", "e_shoff (Section header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shoff (Section header table file offset):"));
	ft_printf("%ld\n", (unsigned long)ehdr32->e_shoff);
	ft_printf("%s ", "e_flags (Processor-specific flags):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_flags (Processor-specific flags):"));
	ft_printf("0x%X\n", ehdr32->e_flags);
	ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_ehsize (ELF header size in bytes):"));
	ft_printf("%d\n", ehdr32->e_ehsize);
	ft_printf("%s ", "e_phentsize (Program header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phentsize (Program header table entry size):"));
	ft_printf("%d\n", ehdr32->e_phentsize);
	ft_printf("%s ", "e_phnum (Program header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phnum (Program header table entry count):"));
	ft_printf("%d\n", ehdr32->e_phnum);
	ft_printf("%s ", "e_shentsize (Section header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shentsize (Section header table entry size):"));
	ft_printf("%d\n", ehdr32->e_shentsize);
	ft_printf("%s ", "e_shnum (Section header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shnum (Section header table entry count):"));
	ft_printf("%d\n", ehdr32->e_shnum);
	ft_printf("%s ", "e_shstrndx (Section header string table index):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shstrndx (Section header string table index):"));
	ft_printf("%d\n", ehdr32->e_shstrndx);
}

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
	ft_printf("type\tsize\tflags\n");
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
			ft_printf("+others");
		else
			ft_printf("no flags");
		ft_putchar_fd('\n', 1);
	}
	(void)file;
}

//#define SHF_WRITE	     (1 << 0)	/* Writable */
//#define SHF_ALLOC	     (1 << 1)	/* Occupies memory during execution */
//#define SHF_EXECINSTR	     (1 << 2)	/* Executable */
//#define SHF_MERGE	     (1 << 4)	/* Might be merged */
//#define SHF_STRINGS	     (1 << 5)	/* Contains nul-terminated strings */
//#define SHF_INFO_LINK	     (1 << 6)	/* `sh_info' contains SHT index */
//#define SHF_LINK_ORDER	     (1 << 7)	/* Preserve order after combining */
//#define SHF_OS_NONCONFORMING (1 << 8)	/* Non-standard OS specific handling
//					   required */
//#define SHF_GROUP	     (1 << 9)	/* Section is member of a group.  */
//#define SHF_TLS		     (1 << 10)	/* Section hold thread-local data.  */
//#define SHF_COMPRESSED	     (1 << 11)	/* Section with compressed data. */
//#define SHF_MASKOS	     0x0ff00000	/* OS-specific.  */
//#define SHF_MASKPROC	     0xf0000000	/* Processor-specific */
//#define SHF_GNU_RETAIN	     (1 << 21)  /* Not to be GCed by linker.  */
//#define SHF_ORDERED	     (1 << 30)	/* Special ordering requirement
//					   (Solaris).  */
//#define SHF_EXCLUDE	     (1U << 31)	/* Section is excluded unless
//					   referenced or allocated (Solaris).*/

void    printSht32(const t_file *file, const uint8_t *map)
{
	Elf32_Ehdr          *ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr          *sht = (Elf32_Shdr *)&map[ehdr->e_shoff];
	const uint8_t       *shstr = &map[sht[ehdr->e_shstrndx].sh_offset];

	int                 len;

	ft_printf("\nSection header string tab, first string is  NULL: '%s'\n", shstr);
	write(1, SPACE, PADDING_SHT);
	ft_printf("type\tsize\tflags\n");
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
			ft_printf(" other flags");
		else
			ft_printf("no flags");
		ft_putchar_fd('\n', 1);
	}
	(void)file;
}
