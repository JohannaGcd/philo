NAME = philo
CFLAGS = cc -Wall -Wextra -Werror -pthread

SRC_PATH = source/
OBJ_PATH = object/

SRC = main.c parser.c philo.c thread.c utils.c mutex.c init.c faucheuse.c exit.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH, $(OBJ)))

INC = -I ./include/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c #WHAT THIS do?
	@mkdir -p $(OBJ_PATH)
	$(CFLAGS) -c $< -o $@ $(INC) #idem

$(NAME): $(OBJ)
	$(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
