all: rot13.c
	gcc -o rot13 rot13.c

clean:
	$(RM) rot13
