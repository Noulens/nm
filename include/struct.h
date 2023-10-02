//
// Created by tnoulens on 9/8/23.
//

#ifndef STRUCT_H
# define STRUCT_H

typedef union u_check_endian
{
	int     i;
	char    bytes[4];
}   t_check_endian;

typedef enum e_options
{
	A = 0b00001,
	G = 0b00010,
	P = 0b00100,
	R = 0b01000,
	U = 0b10000,
    V = 0b10000000000
}   t_opt;

typedef enum e_objs
{
	o_A,
	o_a,
	o_B,
	o_C,
	o_D,
	o_G,
	o_i,
	o_I,
	o_n,
	o_N,
	o_P,
	o_R,
	o_S,
	o_T,
	o_U,
	o_u,
	o_V,
	o_W,
	o_stabs,
	o_un
}   t_objs;

typedef enum e_hdr
{
	LEND =      0b100000,
	BEND =      0b1000000,
	B32 =       0b10000000,
	B64 =    0b100000000,
	ERROR =     0b1000000000
}   t_hdr;

typedef struct s_file
{
	char    *path;
	int     fd;
	int     hdr_opt;
	size_t  size;
	t_list  *objlst;
}   t_file;

typedef struct s_args
{
	int         flags;
	int         endianness;
	int         fds;
	t_list      *fl;
	int         exit;
}   t_args;

typedef struct s_obj
{
	char    *value;
	char    *type;
	char    *name;
}   t_obj;

#endif //STRUCT_H
