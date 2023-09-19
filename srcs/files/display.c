//
// Created by tnoulens on 9/19/23.
//

#include "ft_nm.h"

void    printEhdr(const t_file *file, const uint8_t *map)
{
	Elf32_Ehdr  *ehdr32 = NULL;
	Elf64_Ehdr  *ehdr64 = NULL;
	char        *space = "                                                    ";

	if (file->hdr_opt & X86)
	{
		ehdr32 = (Elf32_Ehdr *)map;
		ft_printf("e_ident (Magic number): ");
		for (int i = 0; i < 16; i++)
		{
			ft_printf("%x ", ehdr32->e_ident[i]);
		}
		ft_printf("\n");
		ft_printf("%s ", "e_type (Object file type):");
		write(1, space, 52 - ft_strlen("e_type (Object file type):"));
		ft_printf("%d\n", ehdr32->e_type);
		ft_printf("%s ", "e_machine (Architecture):");
		write(1, space, 52 - ft_strlen("e_machine (Architecture):"));
		ft_printf("%d\n", ehdr32->e_machine);
		ft_printf("%s ", "e_version (Object file version):");
		write(1, space, 52 - ft_strlen("e_version (Object file version):"));
		ft_printf("%d\n", ehdr32->e_version);
		ft_printf("%s ", "e_entry (Entry point virtual address):");
		write(1, space, 52 - ft_strlen("e_entry (Entry point virtual address):"));
		ft_printf("0x%X\n", (unsigned long)ehdr32->e_entry);
		ft_printf("%s ", "e_entry (Entry point virtual address):");
		write(1, space, 52 - ft_strlen("e_entry (Entry point virtual address):"));
		ft_printf("%ld\n", (unsigned long)ehdr32->e_phoff);
		ft_printf("%s ", "e_shoff (Section header table file offset):");
		write(1, space, 52 - ft_strlen("e_shoff (Section header table file offset):"));
		ft_printf("%ld\n", (unsigned long)ehdr32->e_shoff);
		ft_printf("%s ", "e_flags (Processor-specific flags):");
		write(1, space, 52 - ft_strlen("e_flags (Processor-specific flags):"));
		ft_printf("0x%X\n", ehdr32->e_flags);
		ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
		write(1, space, 52 - ft_strlen("e_ehsize (ELF header size in bytes):"));
		ft_printf("%d\n", ehdr32->e_ehsize);
		ft_printf("%s ", "e_phentsize (Program header table entry size):");
		write(1, space, 52 - ft_strlen("e_phentsize (Program header table entry size):"));
		ft_printf("%d\n", ehdr32->e_phentsize);
		ft_printf("%s ", "e_phnum (Program header table entry count):");
		write(1, space, 52 - ft_strlen("e_phnum (Program header table entry count):"));
		ft_printf("%d\n", ehdr32->e_phnum);
		ft_printf("%s ", "e_shentsize (Section header table entry size):");
		write(1, space, 52 - ft_strlen("e_shentsize (Section header table entry size):"));
		ft_printf("%d\n", ehdr32->e_shentsize);
		ft_printf("%s ", "e_shnum (Section header table entry count):");
		write(1, space, 52 - ft_strlen("e_shnum (Section header table entry count):"));
		ft_printf("%d\n", ehdr32->e_shnum);
		ft_printf("%s ", "e_shstrndx (Section header string table index):");
		write(1, space, 52 - ft_strlen("e_shstrndx (Section header string table index):"));
		ft_printf("%d\n", ehdr32->e_shstrndx);
	}
	else
	{
		ehdr64 = (Elf64_Ehdr *)map;
		ft_printf("e_ident (Magic number): ");
		for (int i = 0; i < 16; i++)
		{
			ft_printf("%x ", ehdr64->e_ident[i]);
		}
		ft_printf("\n");
		ft_printf("%s ", "e_type (Object file type):");
		write(1, space, 52 - ft_strlen("e_type (Object file type):"));
		ft_printf("%d\n", ehdr64->e_type);
		ft_printf("%s ", "e_machine (Architecture):");
		write(1, space, 52 - ft_strlen("e_machine (Architecture):"));
		ft_printf("%d\n", ehdr64->e_machine);
		ft_printf("%s ", "e_version (Object file version):");
		write(1, space, 52 - ft_strlen("e_version (Object file version):"));
		ft_printf("%d\n", ehdr64->e_version);
		ft_printf("%s ", "e_entry (Entry point virtual address):");
		write(1, space, 52 - ft_strlen("e_entry (Entry point virtual address):"));
		ft_printf("0x%X\n", (unsigned long)ehdr64->e_entry);
		ft_printf("%s ", "e_phoff (Program header table file offset):");
		write(1, space, 52 - ft_strlen("e_phoff (Program header table file offset):"));
		ft_printf("%ld\n", (unsigned long)ehdr64->e_phoff);
		ft_printf("%s ", "e_shoff (Section header table file offset):");
		write(1, space, 52 - ft_strlen("e_shoff (Section header table file offset):"));
		ft_printf("%ld\n", (unsigned long)ehdr64->e_shoff);
		ft_printf("%s ", "e_flags (Processor-specific flags):");
		write(1, space, 52 - ft_strlen("e_flags (Processor-specific flags):"));
		ft_printf("0x%X\n", ehdr64->e_flags);
		ft_printf("%s ", "e_ehsize (ELF header size in bytes):");
		write(1, space, 52 - ft_strlen("e_ehsize (ELF header size in bytes):"));
		ft_printf("%d\n", ehdr64->e_ehsize);
		ft_printf("%s ", "e_phentsize (Program header table entry size):");
		write(1, space, 52 - ft_strlen("e_phentsize (Program header table entry size):"));
		ft_printf("%d\n", ehdr64->e_phentsize);
		ft_printf("%s ", "e_phnum (Program header table entry count):");
		write(1, space, 52 - ft_strlen("e_phnum (Program header table entry count):"));
		ft_printf("%d\n", ehdr64->e_phnum);
		ft_printf("%s ", "e_shentsize (Section header table entry size):");
		write(1, space, 52 - ft_strlen("e_shentsize (Section header table entry size):"));
		ft_printf("%d\n", ehdr64->e_shentsize);
		ft_printf("%s ", "e_shnum (Section header table entry count):");
		write(1, space, 52 - ft_strlen("e_shnum (Section header table entry count):"));
		ft_printf("%d\n", ehdr64->e_shnum);
		ft_printf("%s ", "e_shstrndx (Section header string table index):");
		write(1, space, 52 - ft_strlen("e_shstrndx (Section header string table index):"));
		ft_printf("%d\n", ehdr64->e_shstrndx);
	}
}
