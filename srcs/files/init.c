//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

t_args  init_args()
{
	t_check_endian   data;

	data.i = 0x01020304;
	if (data.bytes[0] == 0x01)
		return ((t_args){0, BEND,0, NULL, 0});
	else if (data.bytes[0] == 0x04)
		return ((t_args){0, LEND,0, NULL, 0});
	else
	{
		ft_fprintf(2, "ft_nm: init_args: Unknown endianness\n");
		exit(1);
	}
}

t_file  init_file(char *ptr)
{
	return ((t_file){ptr, -1, 0, 0, NULL});
}

static void    add_node(t_args *args, const char *path)
{
	char    *ptr = NULL;
	t_list  *temp = NULL;
	t_file  *file_to_add = NULL;

	file_to_add = malloc(sizeof(t_file));
	if (!file_to_add)
	{
		free_list(&args->fl);
		perror("ft_nm: add_node");
		exit(1);
	}
	ptr = ft_strdup(path);
	if (!ptr)
	{
		free(file_to_add);
		free_list(&args->fl);
		perror("ft_nm: add_node");
		exit(1);
	}
	*file_to_add = init_file(ptr);
	temp = ft_lstnew((void *)file_to_add);
	if (!temp)
	{
		free(ptr);
		free(file_to_add);
		free_list(&args->fl);
		perror("ft_nm: add_node");
		exit(1);
	}
	ft_lstadd_back(&args->fl, temp);
	args->fds++;
}

void    check_args(int ac, char **av, t_args *args)
{
	size_t  len = 0;

	++av;
	if (ac == 1)
	{
		add_node(args, "./a.out");
		return ;
	}
	len = ft_ptrlen((const char **) av);
	while (len--)
	{
        if (!ft_strncmp(*av, "--verbose", 10))
        {
            args->flags |= V;
        }
        else if (**av == '-')
		{
			++*av;
			while (**av)
			{
				switch (**av)
				{
					case 'a':
						args->flags |= A;
						break;
					case 'g':
						args->flags |= G;
						break;
					case 'p':
						args->flags |= P;
						break;
					case 'r':
						args->flags |= R;
						break;
					case 'u':
						args->flags |= U;
						break;
					default:
                            ft_fprintf(2, INVALID_OPT, **av);
                            free_list(&args->fl);
                            exit(1);
				}
				++*av;
			}
		}
        else
			add_node(args, *av);
		++av;
	}
	if (!args->fds)
		add_node(args, "./a.out");
}
