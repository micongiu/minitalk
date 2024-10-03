SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

all: server client

server: server.c ${LIBFT}
	@$(CC) $(CFLAGS) server.c ${LIBFT} -o server

client: client.c ${LIBFT}
	@$(CC) $(CFLAGS) client.c ${LIBFT} -o client

${LIBFT}:
	@make all -C ./libft/
	@make clean -C ./libft/

%.o: %.c
	$(CC) -c $(CFLAGS) $?


clean:
	rm -f $(OBJ)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a

bonus: all

re: fclean all

rebonus: re

.PHONY: all bonus libft clean fclean re