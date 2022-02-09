SOURCE 	:= $(shell find ./ -name '*.c')
LIBS 	:= -lSDL2 -lSDL2_ttf -lSDL2_image

OUTPUT := ./$(notdir $(CURDIR))

all: $(SOURCE) 
	gcc $(SOURCE) $(sdl2-config --cflags) -Wall -Wextra -fsanitize=address -static-libasan -Og -ggdb3 $(LIBS) -o $(OUTPUT)
