//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

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
	*file_to_add = (t_file){ptr, -1};
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

void    check_args(int ac, char **av, t_args *args) {
	++av;
	size_t len;
	if (ac == 1)
	{
		args->fds = open("./a.out", O_RDONLY);
		if (args->fds < 0) {
			perror("ft_nm: 'a.out'");
			exit(1);
		}
		return ;
	}
	len = ft_ptrlen((const char **) av);
	while (len--)
	{
		if (**av == '-')
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
						ft_fprintf(2, "nm: invalid option -- %c", **av);
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

int main(int ac, char **av)
{
	t_args  args = {0, 0, NULL};

	check_args(ac, av, &args);
	free_list(&args.fl);
	return (0);
}
