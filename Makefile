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

EXTRAS_DIR		=	EXTRAS/
EXTRAS_F		=	display.c display_2.c rainbow_txt.c

TOOLS_DIR		=	TOOLS/
TOOLS_F			=	err_msg.c lstclear.c cleanup.c garbage_collector_utils.c \
					garbage_collector.c

LISTS_DIR		=	TOOLS/LISTS/
LISTS_F			=	main_lst.c token_dblst.c redir_lst.c exec_lst.c

INIT_DIR		=	INIT/
INIT_F			=	prompt.c init_data.c

ENV_DIR			=	ENVIRONMENT/
ENV_F			=	create_env.c env_utils.c export_env_utils.c

LEXING_DIR		=	LEXING/
LEXING_F		=	check_input.c create_main_lst.c check_main.c \
					tokenization.c create_token_dblst.c

PARSING_DIR		=	PARSING/
PARSING_F		=	handle_quotes.c quotes_utils.c check_sequence.c \
					exec_lst_utils.c create_exec_lst.c redir_lst_utils.c \
					create_redir_lst.c

EXPAND_DIR		=	EXPANSION/
EXPAND_F		=	expand.c expand_utils.c

BUILT_INS_DIR	=	BUILT_INS/
BUILT_INS_F		=	built_ins.c ft_echo.c cd_utils.c ft_cd.c ft_pwd.c \
					ft_unset.c ft_env.c ft_exit.c

SIGNALS_DIR		=	SIGNALS/
SIGNALS_F		=	signals.c

EXEC_DIR		=	EXECUTION/
EXEC_F			=	exec_utils.c while_cmd.c pathfinder.c here_doc.c exec.c

#******************************************************************************#
#	COMBINE FILES AND DIRECTORIES
#******************************************************************************#

SRCS_DIR		=	SRCS/
SRCS_F			=	$(addprefix $(EXTRAS_DIR), $(EXTRAS_F)) \
					$(addprefix $(TOOLS_DIR), $(TOOLS_F)) \
					$(addprefix $(LISTS_DIR), $(LISTS_F)) \
					$(addprefix $(INIT_DIR), $(INIT_F)) \
					$(addprefix $(ENV_DIR), $(ENV_F)) \
					$(addprefix $(LEXING_DIR), $(LEXING_F)) \
					$(addprefix $(TESTS_DIR), $(TESTS_F)) \
					$(addprefix $(PARSING_DIR), $(PARSING_F)) \
					$(addprefix $(EXPAND_DIR), $(EXPAND_F)) \
					$(addprefix $(BUILT_INS_DIR), $(BUILT_INS_F)) \
					$(addprefix $(SIGNALS_DIR), $(SIGNALS_F)) \
					$(addprefix $(EXEC_DIR), $(EXEC_F)) \
					main.c

OBJS_DIR		=	OBJS/
OBJS_F			=	$(patsubst %.c,$(OBJS_DIR)%.o,$(SRCS_F))

DEPS_F			=	$(patsubst %.c,$(OBJS_DIR)%.d,$(SRCS_F))

TOTAL_F			:=	$(words $(SRCS_F))

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
			@printf "\n\n=================$(shell bash rainbow.sh " MINISHELL ")"
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