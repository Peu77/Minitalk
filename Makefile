SERVER_NAME = server
CLIENT_NAME = client

SERVER_SRCS = server.c
CLIENT_SRCS = client.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

LIB_PRINTF = ft_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ft_printf/libft -I ft_printf/src -fsanitize=address -g

all: $(LIB_PRINTF) $(SERVER_NAME) $(CLIENT_NAME)

$(LIB_PRINTF):
	@make -C ft_printf

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIB_PRINTF) -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIB_PRINTF) -o $(CLIENT_NAME)

clean:
	@make -C ft_printf clean
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	@make -C ft_printf fclean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re