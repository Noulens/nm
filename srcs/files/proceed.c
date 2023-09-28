//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static int check_size(t_file *file, int arch)
{
	if (((arch & B64) && file->size < sizeof(Elf64_Ehdr))
		|| ((arch & B32) && file->size < sizeof(Elf32_Ehdr)))
	{
		return (-1);
	}
	return (0);
}

void parseElfHeader(t_file *file, uint8_t *map)
{
	if (file->hdr_opt & B64)
	{
		printEhdr64(file, map);
	}
	else
	{
		printEhdr32(file, map);
	}
}

void parseElfSection(t_file *file, uint8_t *map)
{
    if (file->hdr_opt & B64)
    {
        printSht64(file, map);
    }
    else
    {
        printSht32(file, map);
    }
}

void parseElfProgram(t_file *file, uint8_t *map)
{
	if (file->hdr_opt & B64)
	{
		printPhdr64(file, map);
	}
	else
	{
		printPhdr32(file, map);
	}
}

static void  check_magic(t_file *file, uint8_t *map)
{
	if (ft_strncmp((char *)map, ELFMAG, 4) == 0)
	{
		switch (map[4])
		{
			case 1:
				file->hdr_opt |= B32;
				break ;
			case 2:
				file->hdr_opt |= B64;
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
		ft_fprintf(STDERR_FILENO, SYS_ERR"\n", file->path, strerror(errno));
		file->hdr_opt |= ERROR;
		return ;
	}
	if (fstat(file->fd, sb) == -1)
	{
		ft_fprintf(STDERR_FILENO, SYS_ERR"\n", "fstat", strerror(errno));
		file->hdr_opt |= ERROR;
		return ;
	}
	switch (sb->st_mode & S_IFMT)
	{
		case S_IFBLK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": block device\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFCHR:
			ft_fprintf(STDERR_FILENO, NOT_ELF": character device\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFDIR:
			ft_fprintf(STDERR_FILENO, NOT_ELF": directory\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFIFO:
			ft_fprintf(STDERR_FILENO, NOT_ELF": FIFO/pipe\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFLNK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": symlink\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFSOCK:
			ft_fprintf(STDERR_FILENO, NOT_ELF": socket\n", file->path);
			file->hdr_opt |= ERROR;
			break ;
		case S_IFREG:
			break;
		default:
			ft_fprintf(STDERR_FILENO, NOT_ELF": unknown?\n", file->path);
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
		file->hdr_opt |= ERROR;
		ft_fprintf(STDERR_FILENO, SYS_ERR"\n", "mmap", strerror(errno));
		return ;
	}
	check_magic(file, *map);
	if (file->hdr_opt & ERROR)
	{
		ft_fprintf(STDERR_FILENO, NOT_ELF"\n", file->path);
		return ;
	}
	parseElfHeader(file, *map);
    parseElfSection(file, *map);
	parseElfProgram(file, *map);
	if (file->hdr_opt & B64)
		parseSymbols64(file, *map);
	else
		parseSymbols32(file, *map);
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
		if (!(file->hdr_opt & ERROR))
		{
			mapping(file, &sb, &map);
			free_list_obj(&file->objlst);
			if (map != MAP_FAILED && munmap(map, sb.st_size) < 0)
				ft_fprintf(STDERR_FILENO, SYS_ERR"\n", "munmap", strerror(errno));
		}
		if (file->fd != -1 && close(file->fd) < 0)
		{
			file->hdr_opt |= ERROR;
			ft_fprintf(STDERR_FILENO, SYS_ERR"\n", file->path, strerror(errno));
		}
		if (!(file->hdr_opt & ERROR))
			ft_putchar_fd(1, '\n');
		else
			args->exit = 1;
		tmp = tmp->next;
	}
}
