//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static int check_size(t_file *file, int arch)
{
	if (((arch & X86_64) && file->size < sizeof(Elf64_Ehdr))
		|| ((arch & X86) && file->size < sizeof(Elf32_Ehdr)))
	{
		return (-1);
	}
	return (0);
}

static void parseElfHeader(t_file *file, uint8_t *map)
{
	Elf32_Ehdr  *ehdr32 = NULL;
	Elf64_Ehdr  *ehdr64 = NULL;
	if (file->hdr_opt & X86)
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

static void  check_magic(t_file *file, uint8_t *map)
{
	if (ft_strncmp((char *)map, ELFMAG, 4) == 0)
	{
		switch (map[4])
		{
			case 1:
				file->hdr_opt |= X86;
				break ;
			case 2:
				file->hdr_opt |= X86_64;
				break ;
			default:
				file->hdr_opt |= ERROR;
		}
		if (check_size(file, file->hdr_opt))
			file->hdr_opt |= ERROR;
		switch (map[5])
		{
			case 1:
				file->hdr_opt |= LEND;
				break ;
			case 2:
				file->hdr_opt |= BEND;
				break ;
			default:
				file->hdr_opt |= ERROR;
		}
	}
	else
		file->hdr_opt |= ERROR;
}

static void stating(t_file *file, struct stat *sb)
{
	file->fd = open(file->path, O_RDONLY);
	if (file->fd == -1)
	{
		ft_fprintf(STDERR_FILENO, OPEN_ERR, file->path, strerror(errno));
		file->hdr_opt |= ERROR;
		return ;
	}
	if (fstat(file->fd, sb) == -1)
	{
		ft_fprintf(STDERR_FILENO, "ft_nm: fstat: %s", strerror(errno));
		file->hdr_opt |= ERROR;
		return ;
	}
	switch (sb->st_mode & S_IFMT)
	{
		case S_IFBLK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": block device", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFCHR:
			ft_fprintf(STDERR_FILENO, NOT_ELF": character device", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFDIR:
			ft_fprintf(STDERR_FILENO, NOT_ELF": directory", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFIFO:
			ft_fprintf(STDERR_FILENO, NOT_ELF": FIFO/pipe", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFLNK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": symlink", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFSOCK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": socket", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFREG:
			break;
		default:
			ft_fprintf(STDERR_FILENO, NOT_ELF": unknown?", file->path);
			file->hdr_opt |= ERROR;
			break ;
	}
	file->size = sb->st_size;
}

static void mapping(t_file *file, struct stat *sb, uint8_t **map)
{
	if (file->hdr_opt & ERROR)
		return ;
	*map = (uint8_t *)mmap(NULL, (*sb).st_size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (*map == MAP_FAILED)
	{
		ft_fprintf(STDERR_FILENO, "ft_nm: mmap: %s", strerror(errno));
		return ;
	}
	check_magic(file, *map);
	if (file->hdr_opt & ERROR)
	{
		ft_fprintf(STDERR_FILENO, NOT_ELF, file->path);
		return ;
	}
	parseElfHeader(file, *map);
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
		stating(file, &sb);
		mapping(file, &sb, &map);
		if (map != MAP_FAILED && munmap(map, sb.st_size) < 0)
			ft_fprintf(STDERR_FILENO, "ft_nm: munmap: %s", strerror(errno));
		if (file->fd != -1 && close(file->fd) < 0)
			ft_fprintf(STDERR_FILENO, "ft_nm: close fd: %s", strerror(errno));
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}
