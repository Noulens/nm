//
// Created by tnoulens on 9/8/23.
//

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_options
{
	A = 0b00001,
	G = 0b00010,
	P = 0b00100,
	R = 0b01000,
	U = 0b10000,
}   t_opt;

typedef struct s_file
{
	char    *path;
	int     fd;
}   t_file;

typedef struct s_args
{
	u_int8_t   flags;
	int         fds;
	t_list      *fl;
}   t_args;

#endif //STRUCT_H
