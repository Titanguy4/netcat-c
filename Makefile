TARGET = netcatc
SRCS = src/netcat.c src/server.c src/client.c src/utils.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinclude

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

re: clean $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run re