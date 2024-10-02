SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client


	$(CC) -o $@ $< -Llibft -lft
	$(CC) -o $@ $< -Llibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a

bonus: all

re: fclean all

.PHONY: all bonus libft clean fclean re