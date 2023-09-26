//
// Created by tnoulens on 9/8/23.
//

#include "ft_nm.h"

int main(int ac, char **av)
{
	t_args  args = init_args();

	check_args(ac, av, &args);
	proceed(&args);
	free_list(&args.fl);
	return (args.exit);
}

/*
 * constructor function are run before the main and destructor after exit
 */
/*__attribute__((constructor)) void func()
{
	ft_printf("DEBUT: %s\n", __FUNCTION__ );
}

__attribute__((destructor(101))) void func2()
{
	ft_printf("FIN: %s\n", __FUNCTION__ );
}*/
