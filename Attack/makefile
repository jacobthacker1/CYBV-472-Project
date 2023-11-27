CFLAGS+=-Wall -g

EXECUTABLE=the_game_of_games

OBJECTS=Item.o Location.o ItemList.o

SHARED=Item.so Location.so Game.so ItemList.so

all: $(OBJECTS) lib main.c
	gcc $(CFLAGS) $(OBJECTS) main.c -o $(EXECUTABLE)
	ar rc adventure.a $(OBJECTS)

lib: $(OBJECTS)
#	gcc -shared

slib: $(SHARED) slibrary
	gcc -c -Wall -Werror -fpic $(OBJECTS)

clean:
	rm -f *.o
	rm -f *.so
	rm -f *~
	rm -f $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) -c $<

.c.so:
	$(CC) -c -fPIC -shared %<
