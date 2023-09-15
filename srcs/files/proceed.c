//
// Created by tnoulens on 9/8/23.
//

#include <slcurses.h>
#include "ft_nm.h"

void parseElfHeader (void *map)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) map;

	ft_fprintf (STDOUT_FILENO, "Entry point: %p\n", ehdr->e_entry);
}

bool    checkMagic(const char *str)
{
	return (ft_strlen(str) >= 16
	       && str[0] == ELFMAG0
	       && str[1] == ELFMAG1
	       && str[2] == ELFMAG2
	       && str[3] == ELFMAG3);
}

void    proceed(t_args *args)
{
	t_list  *tmp = args->fl;
	t_file  *file = NULL;
	int     fd = -1;
	struct stat sb;
	void *map;

	while (tmp)
	{
		file = (t_file *)tmp->content;
		if (args->fds > 1)
			ft_printf("%s:\n", file->path);
		fd = open(file->path, O_RDONLY);
		if (fstat(fd, &sb) == -1)
		{
			perror("while fstat'ing target binary");
			exit(-1);
		}
		map = mmap( NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (map == MAP_FAILED)
		{
			perror("while mmap'ing target binary");
			exit(-1);
		}
		parseElfHeader(map);
		if (munmap(map, sb.st_size) < 0)
		{
			perror("while unmmap'ing target binary");
			exit(-1);
		}
		tmp = tmp->next;
		ft_putchar_fd('\n', 1);
	}
}
