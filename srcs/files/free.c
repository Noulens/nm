//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static void clr_struct(void *ptr)
{
	t_file *file = (t_file*)ptr;
	if (file->path)
		free(file->path);
}

void    free_list(t_list **begin)
{
	ft_lstiter(*begin, clr_struct);
	ft_lstclear(*begin);
}
