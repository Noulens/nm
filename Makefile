NAME		=	ft_nm

NAME_B		=	b_ft_nm

VPATH		=	srcs

INCLDIR		=	$(addsuffix /include, .) $(LIBS)

LIBS		=	libft/

BUILDIR		=	build

BUILDIR_B	=	build_b

SRCS_DIR	=	$(sort $(dir $(wildcard ./srcs/*/)))

SRCS		=	$(addprefix srcs/,					\
										main.c		\
					$(addprefix files/,	free.c		\
										proceed.c	\
					)								\
				)

SRCS_B		=	$(addprefix srcs/,					\
                						main.c		\
                	$(addprefix files,	free.c		\
										proceed.c	\
                	)								\
                )

OBJ			=	$(SRCS:%.c=$(BUILDIR)/%.o)

OBJ_B		=	$(SRCS_B:%.c=$(BUILDIR_B)/%.o)

CFLAGS		=	-Wall -Wextra -Werror -g

LDFLAGS		=	$(LIBS)libft.a

CC			=	gcc

INCFLAGS	=	$(addprefix -I , $(INCLDIR))

RM			=	/bin/rm -rf

# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# DISPLAY
HEAD_SIZE	=	32
NAME_SIZE	=	$(shell NAME='$(NAME)'; printf "$${\#NAME}")
PAD_WIDTH	=	$(shell printf "$$((($(HEAD_SIZE) - $(NAME_SIZE)) / 2))")
PAD_PREC	=	$(shell printf "$$(($(PAD_WIDTH) / 2))")
PAD_CHAR	=	\*
PAD_STR		=	$(shell printf '$(PAD_CHAR)%.0s' {1..$(PAD_WIDTH)})
LEFT_PAD	=	$(shell printf '%-*.*s' $(PAD_WIDTH) $(PAD_PREC) $(PAD_STR))
RIGHT_PAD	=	$(shell printf '%*.*s' $$(($(PAD_WIDTH) + $(NAME_SIZE) % 2)) $(PAD_PREC) $(PAD_STR))
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")

#######
#Rules#
#######

ifeq (bonus, $(filter bonus,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else ifeq (rebonus, $(filter rebonus,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else ifeq (lcb, $(filter lcb,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else
	DEFINE	=	-D BONUS=0
endif

.PHONY:	all bonus clean fclean re

##.SILENT:

all:			change subsystem $(NAME)

bonus:			subsystem $(NAME_B)

subsystem: # Make the libft
				@make -C $(LIBS) all

$(BUILDIR)/%.o:	%.c
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(BUILDIR_B)/%.o:	%.c
				@mkdir -p build_b/ $(addprefix build_b/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME_B):		$(OBJ_B)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

$(NAME):		$(OBJ)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

clean:
				@printf "$(YELLOW)Deleting object files...$(DEFAULT)\n"
				@$(RM) $(OBJ) $(OBJ_B)
				@make -C $(LIBS) clean
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME) $(BUILDIR_B) $(NAME_B) ./change_byte
				@make -C $(LIBS) fclean
				@printf "$(DELPREV)Build directory and binary deleted\n"

re:				fclean
				@$(MAKE) -s all

rebonus:		fclean
				$(MAKE) -s bonus

change:
	 			$(CC) $(CFLAGS) ./test/changedata.c -o change_byte
