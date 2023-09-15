//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

void    proceed(t_args *args)
{
	t_list  *tmp = args->fl;
	t_file  *file = NULL;
	int     fd = -1;

	while (tmp)
	{
		file = (t_file *)tmp->content;
		fd = open(file->path, O_RDONLY);
		if (fd < 0)
			ft_fprintf(2, "ft_nm: %s: %s\n", file->path, strerror(errno));
		tmp = tmp->next;
	}
}