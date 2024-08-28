#******************************************************************************#
#	FEATURES
#******************************************************************************#

RESET		:=	\e[0m
BOLD		:=	\e[1m
ITAL		:=	\e[3m
BLINK		:=	\e[5m

YELLOW		:=	\e[33m
GREEN		:=	\e[32m
BLUE		:=	\e[34m
PURPLE		:=	\e[35m
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
BUILTINS_F		=	builtins.c my_env.c my_pwd.c my_cd_utils.c my_cd.c my_exit.c

ENV_DIR			=	ENV/
ENV_F			=	create_env.c create_export_env.c env_utils.c

EXPAND_DIR		=	EXPAND/
EXPAND_F		=	expansion.c

TOKEN_DIR		=	TOKENIZATION/
TOKEN_F			=

INIT_DIR		=	INIT/
INIT_F			=	structs.c

PARSING_DIR		=	PARSING/
PARSING_F		=	check_if_closed.c dbquote.c join.c squote.c

TOOLS_DIR		=	TOOLS/
TOOLS_F			=	token_utils.c free.c error_msg.c display.c features.c

#******************************************************************************#
#	COMBINE FILES AND DIRECTORIES
#******************************************************************************#

SRCS_DIR		=	SRCS/
SRCS_F			=	$(addprefix $(ENV_DIR), $(ENV_F)) \
					$(addprefix $(PARSING_DIR), $(PARSING_F)) \
					$(addprefix $(BUILTINS_DIR), $(BUILTINS_F)) \
					$(addprefix $(EXPAND_DIR), $(EXPAND_F)) \
					$(addprefix $(INIT_DIR), $(INIT_F)) \
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
		@printf "\n$(BOLD)$(GREEN)[objs]:\t $(RESET)Clean completed\n"

fclean: clean
			@rm -rf $(NAME)
			@make fclean -sC $(LIBFT_PATH)
			@printf "$(BOLD)$(BLUE)[execs]: $(RESET)Full clean completed!\n\n\n"

re:	fclean all
		@printf "\n$(BOLD)$(YELLOW)make re: $(RESET)All files have been rebuilt! ✨\n\n"

norm:
		@clear
		@norminette $(SRC_DIR) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm