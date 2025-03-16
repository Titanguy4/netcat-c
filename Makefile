TARGET = exec
SRCS = src/netcat.c src/server.c src/client.c src/utils.c
CC = gcc
GFLAGS = -Wall -Wextra -Werror -g

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm $(TARGET)

run:
	./$(TARGET)