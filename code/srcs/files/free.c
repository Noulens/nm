//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

static void clr_struct(void *ptr)
{
	t_file *file = (t_file *)ptr;
	if (file->path)
		free(file->path);
}

static void clr_obj_struct(void *ptr)
{
	t_obj   *obj = (t_obj *)ptr;
	if (obj->name)
		free(obj->name);
	if (obj->type)
		free(obj->type);
	if (obj->value)
		free(obj->value);
}

void    free_list(t_list **begin)
{
	ft_lstiter(*begin, clr_struct);
	ft_lstclear(*begin);
}

void    free_list_obj(t_list **begin)
{
	ft_lstiter(*begin, clr_obj_struct);
	ft_lstclear(*begin);
}
