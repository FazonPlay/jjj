CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2_image  # Link both SDL2 and SDL2_image

SOURCES = main.c snake.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = snake_game

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)



fclean: 
	rm -f $(OBJECTS) $(EXEC)

re: fclean all