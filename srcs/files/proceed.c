//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static int check_size32(t_file *file, int arch, Elf32_Ehdr *ehdr32)
{
	if ( ((arch & B32) && file->size < sizeof(Elf32_Ehdr))
	    || readWord(ehdr32->e_shoff, file->hdr_opt) + (readHalf(ehdr32->e_shentsize, file->hdr_opt) * readHalf(ehdr32->e_shnum, file->hdr_opt)) > file->size)
	{
		ft_fprintf(2, "ft_nm: %s: file too short\n", file->path);
		return (-1);
	}
	return (0);
}

static int check_size64(t_file *file, int arch, Elf64_Ehdr *ehdr64)
{
	if (((arch & B64) && file->size < sizeof(Elf64_Ehdr))
        || readXWord(ehdr64->e_shoff, file->hdr_opt) + (readHalf(ehdr64->e_shentsize, file->hdr_opt) * readHalf(ehdr64->e_shnum, file->hdr_opt)) > file->size)
	{
        ft_fprintf(2, "ft_nm: %s: file too short\n", file->path);
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

static void check64(t_file *file, Elf64_Ehdr *ehdr64)
{
	int data_encoding = ehdr64->e_ident[EI_DATA];
	if (data_encoding == ELFDATA2LSB)
	{
		file->hdr_opt |= LEND;
	}
	else if (data_encoding == ELFDATA2MSB)
	{
		file->hdr_opt |= BEND;
	}
	else
	{
		file->hdr_opt |= ERROR;
		return ;
	}
	if (check_size64(file, file->hdr_opt, ehdr64))
	{
		file->hdr_opt |= ERROR;
		return ;
	}
	if (ehdr64->e_ident[EI_CLASS] != ELFCLASS64
		|| ehdr64->e_ident[EI_VERSION] != EV_CURRENT)
	{
		file->hdr_opt |= ERROR;
		return ;
	}
}

static void check32(t_file *file, Elf32_Ehdr *ehdr32)
{
	int data_encoding = ehdr32->e_ident[EI_DATA];
	if (data_encoding == ELFDATA2LSB)
	{
		file->hdr_opt |= LEND;
	}
	else if (data_encoding == ELFDATA2MSB)
	{
		file->hdr_opt |= BEND;
	}
	else
	{
		file->hdr_opt |= ERROR;
		return ;
	}
	if (check_size32(file, file->hdr_opt, ehdr32))
	{
		file->hdr_opt |= ERROR;
		return ;
	}
	if (ehdr32->e_ident[EI_CLASS] != ELFCLASS32
	    || ehdr32->e_ident[EI_VERSION] != EV_CURRENT)
	{
		file->hdr_opt |= ERROR;
		return ;
	}
}

static void  check_magic(t_file *file, uint8_t *map)
{
    Elf64_Ehdr      *ehdr64 = NULL;
	Elf32_Ehdr      *ehdr32 = NULL;

	switch (map[EI_CLASS])
	{
		case ELFCLASS32:
			file->hdr_opt |= B32;
			ehdr32 = (Elf32_Ehdr *)map;
			break ;
		case ELFCLASS64:
			file->hdr_opt |= B64;
			ehdr64 = (Elf64_Ehdr *)map;
			break ;
		default:
			file->hdr_opt |= ERROR;
	}
	if (ft_strncmp((char *)map, ELFMAG, 4) == 0)
	{
		if (file->hdr_opt & B32)
			check32(file, ehdr32);
		else if (file->hdr_opt & B64)
			check64(file, ehdr64);
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
    if (file->hdr_opt & V)
    {
        parseElfHeader(file, *map);
        parseElfSection(file, *map);
        parseElfProgram(file, *map);
    }
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
        file->hdr_opt |= args->flags;
        file->hdr_opt |= args->endianness;
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
