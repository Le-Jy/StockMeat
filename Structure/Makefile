#Makefile

main:
	gcc -g main.c move.c board.c piece.c

leaks:
	gcc -fsanitize=address -g main.c move.c board.c piece.c
clean:
	rm a.out