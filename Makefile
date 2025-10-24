NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
INC = -I ./include/

SRC_PATH = source/
OBJ_PATH = object/

SRC = exit.c faucheuse.c init.c main.c mutex_read_or_return_values.c mutex.c parser.c philo.c thread.c utils.c  
OBJS = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
