//
// Created by tnoulens on 9/28/23.
//

#include "ft_nm.h"

static void lstsort(t_list **begin_list, int (*cmp)(const char *, const char *))
{
	t_list	*ptr;
	void	*temp;
	t_obj   *obj1;
	t_obj   *obj2;

	ptr = *begin_list;
	if (!ptr)
		return ;
	while (ptr->next)
	{
		obj1 = (t_obj *)ptr->content;
		obj2 = (t_obj *)ptr->next->content;
		if (cmp(obj1->name, obj2->name) > 0)
		{
			temp = ptr->content;
			ptr->content = ptr->next->content;
			ptr->next->content = temp;
			ptr = *begin_list;
		}
		else
			ptr = ptr->next;
	}
}

void    add_node_obj(t_file *file, char *value, char *type, char *name)
{
	t_list  *temp = NULL;
	t_obj   *obj_to_add = NULL;

	obj_to_add = malloc(sizeof(t_obj));
	if (!obj_to_add)
	{
		perror("ft_nm: add_node_obj");
		file->hdr_opt |= ERROR;
		return ;
	}
	obj_to_add->value = value;
	obj_to_add->type = type;
	obj_to_add->name = name;
	temp = ft_lstnew((void *)obj_to_add);
	if (!temp)
	{
		free(obj_to_add);
		perror("ft_nm: add_node_obj");
		file->hdr_opt |= ERROR;
		return ;
	}
	ft_lstadd_back(&file->objlst, temp);
}

void    displayLstObj(t_list **begin)
{
	t_obj   *obj;
	t_list  *tmp;

	tmp = *begin;
	while (tmp)
	{
		obj = (t_obj *)tmp->content;
		ft_printf("%s %s %s\n", obj->value, obj->type, obj->name);
		tmp = tmp->next;
	}
}

static int  cmpR(const char *s1, const char *s2)
{
	int res = ft_strcmp(s1, s2);
	if (res > 0)
		return (-1);
	else if (res < 0)
		return (1);
	else
		return (0);
}

void    displayLstObjR(t_list **begin)
{
	lstsort(begin, cmpR);
	displayLstObj(begin);
}

void    displayLstObjS(t_list **begin)
{
	lstsort(begin, ft_strcmp);
	displayLstObj(begin);
}

void    printEhdr32(const t_file *file, const uint8_t *map)
{
	Elf32_Ehdr  *ehdr32 = NULL;

	ehdr32 = (Elf32_Ehdr *)map;
	ft_printf("e_ident (Magic number): ");
	for (int i = 0; i < 16; i++)
	{
		ft_printf("%x ", ehdr32->e_ident[i]);
	}
	ft_printf("\n");
	ft_printf("%s ", "e_type (Object file type):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_type (Object file type):"));
	ft_printf("%d\n", readHalf(ehdr32->e_type, file->hdr_opt));
	ft_printf("%s ", "e_machine (Architecture):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_machine (Architecture):"));
	ft_printf("%d\n", readHalf(ehdr32->e_machine, file->hdr_opt));
	ft_printf("%s ", "e_version (Object file version):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_version (Object file version):"));
	ft_printf("%d\n", readWord(ehdr32->e_version, file->hdr_opt));
	ft_printf("%s ", "e_entry (Entry point virtual address):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_entry (Entry point virtual address):"));
	ft_printf("0x%X\n", readWord((unsigned long)ehdr32->e_entry, file->hdr_opt));
	ft_printf("%s ", "e_phoff (Program header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phoff (Program header table file offset):"));
	ft_printf("%ld\n", readWord((unsigned long)ehdr32->e_phoff, file->hdr_opt));
	ft_printf("%s ", "e_shoff (Section header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shoff (Section header table file offset):"));
	ft_printf("%ld\n", readWord((unsigned long)ehdr32->e_shoff, file->hdr_opt));
	ft_printf("%s ", "e_flags (Processor-specific flags):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_flags (Processor-specific flags):"));
	ft_printf("0x%X\n", readWord(ehdr32->e_flags, file->hdr_opt));
	ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_ehsize (ELF header size in bytes):"));
	ft_printf("%d\n", readHalf(ehdr32->e_ehsize, file->hdr_opt));
	ft_printf("%s ", "e_phentsize (Program header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phentsize (Program header table entry size):"));
	ft_printf("%d\n", readHalf(ehdr32->e_phentsize, file->hdr_opt));
	ft_printf("%s ", "e_phnum (Program header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phnum (Program header table entry count):"));
	ft_printf("%d\n", readHalf(ehdr32->e_phnum, file->hdr_opt));
	ft_printf("%s ", "e_shentsize (Section header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shentsize (Section header table entry size):"));
	ft_printf("%d\n", readHalf(ehdr32->e_shentsize, file->hdr_opt));
	ft_printf("%s ", "e_shnum (Section header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shnum (Section header table entry count):"));
	ft_printf("%d\n", readHalf(ehdr32->e_shnum, file->hdr_opt));
	ft_printf("%s ", "e_shstrndx (Section header string table index):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shstrndx (Section header string table index):"));
	ft_printf("%d\n", readHalf(ehdr32->e_shstrndx, file->hdr_opt));
}

void    printSht32(const t_file *file, const uint8_t *map)
{
	Elf32_Ehdr          *ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr          *sht = (Elf32_Shdr *)&map[readWord(ehdr->e_shoff, file->hdr_opt)];
	const uint8_t       *shstr = &map[readWord(sht[readHalf(ehdr->e_shstrndx, file->hdr_opt)].sh_offset, file->hdr_opt)];
	int                 len;

	ft_printf("\nSection header string tab, first string is  NULL: '%s'\n", shstr);
	write(1, SPACE, PADDING_SHT);
	ft_printf("type\tsize\tflags\taddress\n");
	for (int i = 0; i < readHalf(ehdr->e_shnum, file->hdr_opt); i++)
	{
		len = ft_printf("[%d] %s ", i, &(shstr[readWord(sht[i].sh_name, file->hdr_opt)]));
		write(1, SPACE, PADDING_SHT - (len > 30 ? 0 : len));
		switch (readWord(sht[i].sh_type, file->hdr_opt))
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
		ft_printf("\t0x%x\t", readWord(sht[i].sh_size, file->hdr_opt));
		if (readWord(sht[i].sh_flags, file->hdr_opt) & SHF_WRITE)
			ft_printf("W");
		if (readWord(sht[i].sh_flags, file->hdr_opt) & SHF_ALLOC)
			ft_printf("A");
		if (readWord(sht[i].sh_flags, file->hdr_opt) & SHF_EXECINSTR)
			ft_printf("X");
		if (readWord(sht[i].sh_flags, file->hdr_opt) & SHF_MERGE)
			ft_printf("M");
		else if (readWord(sht[i].sh_flags, file->hdr_opt))
			ft_printf("+");
		else
			ft_printf("nof");
		ft_printf("\t0x%X", readWord(sht[i].sh_addr, file->hdr_opt));
		ft_putchar_fd('\n', 1);
	}
}

void    printPhdr32(t_file *file, uint8_t *map)
{
	Elf32_Ehdr  *ehdr = (Elf32_Ehdr *)map;
	Elf32_Phdr  *phdr = (Elf32_Phdr *)&map[readWord(ehdr->e_phoff, file->hdr_opt)];

	ft_printf("\nProgram Headers\n");
	ft_printf("Type"SPACE_PHDR"Offset\tVirtAd\tPhysAd\tFileSiz\tMemSiz\tAlign\tFlg\n\n");
	for (int i = 0; i < readHalf(ehdr->e_phnum, file->hdr_opt); i++)
	{
		int len;
		switch (readWord(phdr[i].p_type, file->hdr_opt))
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
		          readWord(phdr[i].p_offset, file->hdr_opt), readWord(phdr[i].p_vaddr, file->hdr_opt), readWord(phdr[i].p_paddr, file->hdr_opt),
		          readWord(phdr[i].p_filesz, file->hdr_opt), readWord(phdr[i].p_memsz, file->hdr_opt), readWord(phdr[i].p_align, file->hdr_opt));
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_X)
			ft_printf("%s", "E");
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_W)
			ft_printf("%s", "W");
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_R)
			ft_printf("%s", "R");
		else
			ft_printf("%s", "nof");
		ft_putchar_fd('\n', 1);
	}
	ft_putchar_fd('\n', 1);
}

void    printEhdr64(t_file *file, const uint8_t *map)
{
	Elf64_Ehdr  *ehdr64 = NULL;

	ehdr64 = (Elf64_Ehdr *)map;
	ft_printf("e_ident (Magic number): ");
	for (int i = 0; i < 16; i++)
	{
		ft_printf("%x ", ehdr64->e_ident[i]);
	}
	ft_printf("\n");
	ft_printf("%s ", "e_type (Object file type):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_type (Object file type):"));
	ft_printf("%d\n", readHalf(ehdr64->e_type, file->hdr_opt));
	ft_printf("%s ", "e_machine (Architecture):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_machine (Architecture):"));
	ft_printf("%d\n", readHalf(ehdr64->e_machine, file->hdr_opt));
	ft_printf("%s ", "e_version (Object file version):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_version (Object file version):"));
	ft_printf("%d\n", readWord(ehdr64->e_version, file->hdr_opt));
	ft_printf("%s ", "e_entry (Entry point virtual address):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_entry (Entry point virtual address):"));
	ft_printf("0x%X\n", readWord((unsigned long)ehdr64->e_entry, file->hdr_opt));
	ft_printf("%s ", "e_phoff (Program header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phoff (Program header table file offset):"));
	ft_printf("%ld\n", readWord((unsigned long)ehdr64->e_phoff, file->hdr_opt));
	ft_printf("%s ", "e_shoff (Section header table file offset):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shoff (Section header table file offset):"));
	ft_printf("%ld\n", readWord((unsigned long)ehdr64->e_shoff, file->hdr_opt));
	ft_printf("%s ", "e_flags (Processor-specific flags):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_flags (Processor-specific flags):"));
	ft_printf("0x%X\n", readWord(ehdr64->e_flags, file->hdr_opt));
	ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_ehsize (ELF header size in bytes):"));
	ft_printf("%d\n", readHalf(ehdr64->e_ehsize, file->hdr_opt));
	ft_printf("%s ", "e_phentsize (Program header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phentsize (Program header table entry size):"));
	ft_printf("%d\n", readHalf(ehdr64->e_phentsize, file->hdr_opt));
	ft_printf("%s ", "e_phnum (Program header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_phnum (Program header table entry count):"));
	ft_printf("%d\n", readHalf(ehdr64->e_phnum, file->hdr_opt));
	ft_printf("%s ", "e_shentsize (Section header table entry size):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shentsize (Section header table entry size):"));
	ft_printf("%d\n", readHalf(ehdr64->e_shentsize, file->hdr_opt));
	ft_printf("%s ", "e_shnum (Section header table entry count):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shnum (Section header table entry count):"));
	ft_printf("%d\n", readHalf(ehdr64->e_shnum, file->hdr_opt));
	ft_printf("%s ", "e_shstrndx (Section header string table index):");
	write(1, SPACE, PADDING_EHDR - ft_strlen("e_shstrndx (Section header string table index):"));
	ft_printf("%d\n", readHalf(ehdr64->e_shstrndx, file->hdr_opt));
}

void    printSht64(const t_file *file, const uint8_t *map)
{
	Elf64_Ehdr          *ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr          *sht = (Elf64_Shdr *)&map[readXWord(ehdr->e_shoff, file->hdr_opt)];
	const uint8_t       *shstr = &map[readXWord(sht[readHalf(ehdr->e_shstrndx, file->hdr_opt)].sh_offset, file->hdr_opt)];
	int                 len;

	ft_printf("\nSection header string tab, first string is  NULL: '%s'\n", shstr);
	write(1, SPACE, PADDING_SHT);
	ft_printf("type\tsize\tflags\taddress\n");
	for (int i = 0; i < readHalf(ehdr->e_shnum, file->hdr_opt); i++)
	{
		len = ft_printf("[%d] %s ", i, &(shstr[readWord(sht[i].sh_name, file->hdr_opt)]));
		write(1, SPACE, PADDING_SHT - (len > 30 ? 0 : len));
		switch (readWord(sht[i].sh_type, file->hdr_opt))
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
		ft_printf("\t0x%x\t", readXWord(sht[i].sh_size, file->hdr_opt));
		if (readXWord(sht[i].sh_flags, file->hdr_opt) & SHF_WRITE)
			ft_printf("W");
		if (readXWord(sht[i].sh_flags, file->hdr_opt) & SHF_ALLOC)
			ft_printf("A");
		if (readXWord(sht[i].sh_flags, file->hdr_opt) & SHF_EXECINSTR)
			ft_printf("X");
		if (readXWord(sht[i].sh_flags, file->hdr_opt) & SHF_MERGE)
			ft_printf("M");
		else if (readXWord(sht[i].sh_flags, file->hdr_opt))
			ft_printf("+");
		else
			ft_printf("nof");
		ft_printf("\t0x%X", readXWord(sht[i].sh_addr, file->hdr_opt));
		ft_putchar_fd('\n', 1);
	}
}

void    printPhdr64(t_file *file, uint8_t *map)
{
	Elf64_Ehdr  *ehdr = (Elf64_Ehdr *)map;
	Elf64_Phdr  *phdr = (Elf64_Phdr *)&map[readXWord(ehdr->e_phoff, file->hdr_opt)];

	ft_printf("\nProgram Headers\n");
	ft_printf("Type"SPACE_PHDR"Offset\tVirtAd\tPhysAd\tFileSiz\tMemSiz\tAlign\tFlg\n\n");
	for (int i = 0; i < readHalf(ehdr->e_phnum, file->hdr_opt); i++)
	{
		int len;
		switch (readWord(phdr[i].p_type, file->hdr_opt))
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
		          readXWord(phdr[i].p_offset, file->hdr_opt), readXWord(phdr[i].p_vaddr, file->hdr_opt), readXWord(phdr[i].p_paddr, file->hdr_opt),
		          readXWord(phdr[i].p_filesz, file->hdr_opt), readXWord(phdr[i].p_memsz, file->hdr_opt), readXWord(phdr[i].p_align, file->hdr_opt));
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_X)
			ft_printf("%s", "E");
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_W)
			ft_printf("%s", "W");
		if (readWord(phdr[i].p_flags, file->hdr_opt) & PF_R)
			ft_printf("%s", "R");
		else
			ft_printf("%s", "nof");
		ft_putchar_fd('\n', 1);
	}
	ft_putchar_fd('\n', 1);
}
