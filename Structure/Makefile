#Makefile

main:
	gcc -g main.c move.c board.c piece.c ../Game/game.c

leaks:
	gcc -fsanitize=address -g main.c move.c board.c piece.c ../Game/game.c
clean:
	rm a.out