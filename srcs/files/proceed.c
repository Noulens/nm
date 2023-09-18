//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static void parseElfHeader (t_file *file, uint8_t *map)
{
	Elf32_Ehdr  *ehdr32 = NULL;
	Elf64_Ehdr  *ehdr64 = NULL;
	if (file->arch == X86)
	{
		ehdr32 = (Elf32_Ehdr *)map;
		for (int i = 0; i < 16; i++)
		{
			ft_fprintf(1, "%x ", ehdr32->e_ident[i]);
		}
	}
	else
	{
		ehdr64 = (Elf64_Ehdr *)map;
		for (int i = 0; i < 16; i++)
		{
			ft_fprintf(1, "%x ", ehdr64->e_ident[i]);
		}
	}
}

static int  check_magic(int fd)
{
	char *ptr = NULL;

	ptr = get_next_line(fd);
	if (ft_strlen(ptr) >= 16 && ft_strncmp(ptr, ELFMAG, 4) == 0)
	{
		switch (ptr[4])
		{
			case 1:
				return (free(ptr), X86);
			case 2:
				return (free(ptr), X86_64);
			default:
				return (free(ptr), -1);
		}
	}
	return (free(ptr), -1);
}

static void mapping(t_file *file, struct stat *sb, uint8_t *map)
{
	int fd = -1;

	fd = open(file->path, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, OPEN_ERR, file->path, strerror(errno));
		return ;
	}
	file->arch = check_magic(fd);
	if ( file->arch == -1)
	{
		ft_fprintf(STDERR_FILENO, NOT_ELF, file->path);
		return ;
	}
	if (fstat(fd, sb) == -1)
	{
		perror("nm: fstat");
		return ;
	}
	map = (uint8_t *)mmap(NULL, (*sb).st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
	{
		perror("nm: mmap");
		return ;
	}
	if (close(fd) == -1)
		perror("nm: close fd mmap");
	parseElfHeader(file, map);
	if (munmap(map, (*sb).st_size) < 0)
	{
		perror("nm: munmap");
		return ;
	}
}

void    proceed(t_args *args)
{
	t_list      *tmp = args->fl;
	t_file      *file = NULL;
	uint8_t     *map = NULL;
	struct stat sb;

	while (tmp)
	{
		file = (t_file *)tmp->content;
		if (args->fds > 1)
			ft_printf("%s:\n", file->path);
		mapping(file, &sb, map);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}
