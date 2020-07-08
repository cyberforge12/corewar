# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/14 22:31:23 by ldonnor-          #+#    #+#              #
#    Updated: 2020/07/04 14:51:47 by ldonnor-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
DISASM = dasm
COREWAR = corewar

SRC1 =		new_main_vm.c\
			check_vm.c\
			find_players_vm.c\
			create_gamer_and_fill_him_vm.c\
			create_gamer_and_fill_him_2_vm.c\
			fill_decor_array_vm.c\
			heat_visual_vm.c\
			send_gamers_vm.c\
			gamer_swap_vm.c\
			init_start_params_vm.c\
			calс_new_pos_vm.c\
			g_dir_usage_vm.c\
			g_arg_quantity_usage_vm.c\
			extermination_serfs.c\
			g_spell_time_usage.c\
			hide_show_run_vm.c\
			execute_cl_vm.c\
			let_the_show_begin_vm.c\
			winner_is_vm.c\
			make_1_vm.c\
			make_2_vm.c\
			make_3_vm.c\
			make_additional_vm.c \

ASM_MAKE = asm.mk
DASM_MAKE = dasm.mk
CW_MAKE = corewar.mk

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

all: $(FT_LIB) $(MLX_LIB) $(NAME1) $(NAME2) $(DISASM)

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

$(DISASM): FORCE
	make -f $(DASM_MAKE)

clean:
	@rm -rf $(OBJDIR)
	@find . -type f -name "obj" -delete
	@echo "$(NAME1):$(FTAB)$(YELLOW)object files$(TAB)$(RED)were deleted.$(RESET)\n"
	@make -C $(FT) clean
	@make -C $(MLX) clean
	make -f $(ASM_MAKE) clean
	make -f $(DASM_MAKE) clean

fclean: clean
	@rm -rf $(NAME1)
	@echo "\n$(NAME1):$(TAB)$(YELLOW)$(NAME1)$(FTAB)$(RED)was  deleted.$(RESET)"
	make -f $(ASM_MAKE) fclean
	@echo "$(NAME1):$(TAB)$(YELLOW)$(NAME2)$(FTAB)$(RED)was  deleted.$(RESET)\n"
	@make -C $(FT) fclean
	make -f $(DASM_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re FORCE $(NAME1) $(NAME2) $(DISASM)
