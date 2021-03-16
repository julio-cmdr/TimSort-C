all:
	gcc main.c src/inserction.c src/merge.c src/tim.c src/utils.c -g -o exe -lm

comparisons:
	gcc comparisons.c src/inserction.c src/merge.c src/tim.c src/utils.c -g -o exe -lm