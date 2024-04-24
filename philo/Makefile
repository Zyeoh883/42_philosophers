NAME = philo
BONUS_NAME = 
CC = gcc
RM = rm -rf
MKDIR = mkdir -p
FSAN = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror #${FSAN}

RED = \033[0;91m
GREEN = \033[92m
RESET = \033[0m

SRCS_FILES = main.c \
		init.c \
		thread.c \
		utils.c \
		cleanup.c \

BONUS_FILES_DIR = 

BONUS_FILES = 

SRCS_DIR = srcs/
INC_DIR = inc
OBJS_DIR = objs/
BONUS_OBJS_DIR = bonus_objs/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR), $(BONUS_FILES:.c=.o))

all: $(OBJS_DIR) $(NAME)

bonus: all

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BONUS_OBJS_DIR):
	@$(MKDIR) $(BONUS_OBJS_DIR)

$(BONUS_OBJS_DIR)%.o: $(BONUS_FILES_DIR)%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@$(RM) $(OBJS_DIR) $(BONUS_OBJS_DIR)
	@echo "$(RED)$(NAME) objects cleaned!$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)$(NAME) cleaned!$(RESET)"

re: fclean all

.PHONY: all bonus libft clean fclean re
