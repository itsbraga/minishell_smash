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
LIBFT_PATH	=	LIBFT
LIBFT		=	$(LIBFT_PATH)/libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -IINCLUDES
LFLAGS		=	-L $(LIBFT_PATH) -lft -lreadline
DEPFLAGS	=	-MMD -MP
MAKEFLAGS	+=	--no-print-directory
DEBUG		=	-g -g3

#******************************************************************************#
#	SOURCES, OBJECTS AND DEPENDENCIES
#******************************************************************************#

SRC_DIR		=	$(shell find SRCS -type d)
SRCS		=	$(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
vpath %.c $(SRC_DIR)

OBJ_DIR		=	OBJS/
OBJS		=	$(patsubst SRCS/%.c,$(OBJ_DIR)%.o,$(SRCS))

DEPS		=	$(patsubst SRCS/%.c,$(OBJ_DIR)%.d,$(SRCS))

#******************************************************************************#
#	RULES
#******************************************************************************#

all: $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: %.c
				@mkdir -p $(dir $@)
				@$(CC) $(DEBUG) $(DEPFLAGS) $(CFLAGS) -c $< -o $@
-include $(DEPS)

$(LIBFT):
		@make -sC $(LIBFT_PATH) $(MAKEFLAGS)

$(NAME): $(OBJS) $(LIBFT)
			@printf "$(BOLD)\n================="
			@printf "$(RESET)$(shell bash rainbow.sh " MINISHELL ")"
			@printf "$(BOLD)=================\n\n$(RESET)"
			@printf "$(BLINK)$(BOLD)$(GREEN)\t\t # READY! #$(RESET)\n\n"
			@printf "$(BOLD)=============================================\n\n$(RESET)"
			@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -sC $(LIBFT_PATH)
		@printf "\n$(BOLD)$(GREEN)[objs]:\t $(RESET)Clean completed\n"

fclean: clean
			@rm -rf $(NAME)
			@make fclean -sC $(LIBFT_PATH)
			@printf "$(BOLD)$(BLUE)[execs]: $(RESET)Full clean completed!\n\n"

re:		fclean all
			@printf "$(BOLD)make re: $(RESET)Rebuilding done!\n\n"

norm:
		@clear
		@norminette $(SRC_DIR) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm