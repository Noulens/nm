//
// Created by tnoulens on 9/8/23.
//

#ifndef FT_NM_H
# define FT_NM_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <elf.h>
#include "libft.h"
#include "struct.h"

void    free_list(t_list **begin);
void    proceed(t_args *args);

#endif //FT_NM_H
