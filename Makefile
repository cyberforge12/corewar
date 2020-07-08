# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/14 22:31:23 by ldonnor-          #+#    #+#              #
#    Updated: 2020/06/21 17:05:19 by ldonnor-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGECTMAIN = corewar
PROGECTSUB = asm
NAME1	= $(PROGECTMAIN)
NAME2	= $(PROGECTSUB)

SRC1		= new_main_vm.c\

ASM_MAKE = asm.mk

HEADERMAIN	= $(INCDIR)$(PROGECTMAIN).h

GREEN = \033[0;32m
RED = \033[0;31m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CHANGE = \033[0;35m
TAB = "\	\	"
FTAB = "\	\	\	"

OBJ1	= $(addprefix $(OBJDIR),$(SRC1:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -g #-Werror

MLX		= ./miniLibX/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/includes
FT_LNK	= -L ./libft -l ft

SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: $(FT_LIB) $(MLX_LIB) $(NAME1) $(NAME2)

$(OBJDIR)%.o:$(SRCDIR)%.c $(HEADERMAIN) $(HEADERSUB)
	@find . -type f -name "obj" -delete
	@mkdir -p obj/
	@echo "$(CHANGE)∰$(RESET)\c"
	@$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

FORCE: ;

$(FT_LIB): FORCE
	make -C $(FT)

$(MLX_LIB): FORCE
	make -C $(MLX)

$(NAME1): $(OBJ1)
	@echo "\n$(NAME1):$(TAB)$(YELLOW)object files$(TAB)$(GREEN)were created.$(RESET)"
	@$(CC) -framework OpenCL $(OBJ1) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME1)
	@echo "$(NAME1):$(TAB)$(YELLOW)$(NAME1)$(FTAB)$(GREEN)was  created.$(RESET)\n"

$(NAME2): FORCE
	make -f $(ASM_MAKE)

clean:
	@rm -rf $(OBJDIR)
	@find . -type f -name "obj" -delete
	@mkdir -p obj
	@rm -Rf obj
	@echo "$(NAME1):$(FTAB)$(YELLOW)object files$(TAB)$(RED)were deleted.$(RESET)\n"
	@make -C $(FT) clean
	@make -C $(MLX) clean
	make -f $(ASM_MAKE) clean

fclean: clean
	@rm -rf $(NAME1)
	@echo "\n$(NAME1):$(TAB)$(YELLOW)$(NAME1)$(FTAB)$(RED)was  deleted.$(RESET)"
	make -f $(ASM_MAKE) fclean
	@echo "$(NAME1):$(TAB)$(YELLOW)$(NAME2)$(FTAB)$(RED)was  deleted.$(RESET)\n"
	@make -C $(FT) fclean

re: fclean all

.PHONY: all clean fclean re FORCE $(NAME1) $(NAME2)
