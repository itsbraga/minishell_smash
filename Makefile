#******************************************************************************#
#	FEATURES
#******************************************************************************#

RESET		:=	\e[0m
BOLD		:=	\e[1m
ITAL		:=	\e[3m
BLINK		:=	\e[5m

GREEN		:=	\e[32m
YELLOW		:=	\e[33m
BLUE		:=	\e[34m
CYAN		:=	\e[36m
PINK		:=	\e[38;2;255;182;193m

#******************************************************************************#
#	BASICS
#******************************************************************************#

NAME		=	minishell

LIBFT_PATH	=	./LIBFT
LIBFT		=	$(LIBFT_PATH)/libft.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -IINCLUDES
LFLAGS		=	-L $(LIBFT_PATH) -lft -lreadline
DEPFLAGS	=	-MMD -MP
MAKEFLAGS	+=	--no-print-directory

DEBUG		=	-g -g3

#******************************************************************************#
#	SOURCES
#******************************************************************************#

BUILTINS_DIR	=	BUILTINS/
BUILTINS_F		=	builtins.c my_env.c my_pwd.c my_cd_utils.c my_cd.c \
					my_exit.c my_unset.c

ENV_DIR			=	ENVIRONMENT/
ENV_F			=	create_env.c create_export_env.c env_utils.c

EXPAND_DIR		=	EXPAND/
EXPAND_F		=	expand.c expand_utils.c

INIT_DIR		=	INIT/
INIT_F			=	init_global.c create_main_lst.c main_lst_utils.c

PARSING_DIR		=	PARSING/
PARSING_F		=	handle_quotes.c quotes_utils.c del_quotes.c

TOKEN_DIR		=	TOKENIZATION/
TOKEN_F			=	token_utils.c

TOOLS_DIR		=	TOOLS/
TOOLS_F			=	cleanup.c err_msg.c clean_exit_shell.c display.c features.c

#******************************************************************************#
#	COMBINE FILES AND DIRECTORIES
#******************************************************************************#

SRCS_DIR		=	SRCS/
SRCS_F			=	$(addprefix $(ENV_DIR), $(ENV_F)) \
					$(addprefix $(PARSING_DIR), $(PARSING_F)) \
					$(addprefix $(BUILTINS_DIR), $(BUILTINS_F)) \
					$(addprefix $(EXPAND_DIR), $(EXPAND_F)) \
					$(addprefix $(INIT_DIR), $(INIT_F)) \
					$(addprefix $(TOKEN_DIR), $(TOKEN_F)) \
					$(addprefix $(TOOLS_DIR), $(TOOLS_F)) \
					main.c

OBJS_DIR		=	OBJS/
OBJS_F			=	$(patsubst %.c,$(OBJS_DIR)%.o,$(SRCS_F))

DEPS_F			=	$(patsubst %.c,$(OBJS_DIR)%.d,$(SRCS_F))

#******************************************************************************#
#	RULES
#******************************************************************************#

all: $(LIBFT) $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@mkdir -p $(dir $@)
				@printf "$(BOLD)$(ITAL)$(GREEN)Compiled: $(RESET)$(ITAL)$<                                  \n"
				@$(CC) $(DEBUG) $(DEPFLAGS) $(CFLAGS) -c $< -o $@
-include $(DEPS_F)

$(LIBFT):
		@make -sC $(LIBFT_PATH) $(MAKEFLAGS)

$(NAME): $(OBJS_F) $(LIBFT)
			@printf "$(RESET)$(BOLD)\n\n\t\t ⸜(｡˃ ᵕ ˂ )⸝♡\n\n"
			@printf "=================$(shell bash rainbow.sh " MINISHELL ")"
			@printf "$(BOLD)=================\n\n"
			@printf "$(BLINK)$(PINK)\t\t   READY!$(RESET)\n\n"
			@printf "$(BOLD)=============================================\n\n$(RESET)"
			@$(CC) $(CFLAGS) $(DEBUG) $(OBJS_F) $(LFLAGS) -o $(NAME)

clean:
		@rm -rf $(OBJS_DIR)
		@make clean -sC $(LIBFT_PATH)
		@printf "\n$(BOLD)$(BLUE)[objs]:\t $(RESET)Clean completed\n"

fclean: clean
			@rm -rf $(NAME)
			@make fclean -sC $(LIBFT_PATH)
			@printf "$(BOLD)$(CYAN)[execs]: $(RESET)Full clean completed!\n\n\n"

re:	fclean all
		@printf "\n$(BOLD)$(YELLOW)make re: $(RESET)All files have been rebuilt! ✨\n\n"

norm:
		@clear
		@norminette $(SRC_DIR) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm