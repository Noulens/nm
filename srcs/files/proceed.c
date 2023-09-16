//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static void parseElfHeader (uint8_t *map)
{
	Elf32_Ehdr  *ehdr = (Elf32_Ehdr *)map;

	ft_fprintf (STDOUT_FILENO, "Entry point: %p\n", ehdr->e_entry);
}

static int  check_magic(int fd)
{
	char *ptr = NULL;

	ptr = get_next_line(fd);
	if (ft_strlen(ptr) >= 4 && ft_strncmp(ptr, ELFMAG, 4) == 0)
		return (free(ptr), 0);
	else
		return (free(ptr), -1);
}

static void mapping(const char *path, struct stat *sb, uint8_t *map)
{
	int fd = -1;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, OPEN_ERR, path, strerror(errno));
		return ;
	}
	if (check_magic(fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, NOT_ELF, path);
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
	parseElfHeader(map);
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
		mapping(file->path, &sb, map);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}
