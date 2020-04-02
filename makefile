assembler: main.o analize.o func1.o func2.o mem_map.o util_func.o uti1.h mainLab.h func1Lab.h stat_tables.h
	gcc -g -ansi -Wall main.o analize.o func1.o func2.o mem_map.o util_func.o -o assembler

main.o: main.c uti1.h mainLab.h stat_tables.h
	gcc -c -ansi -Wall main.c -o main.o
analize.o: analize.c uti1.h
	gcc -c -ansi -Wall analize.c -o analize.o
func1.o: func1.c uti1.h func1Lab.h stat_tables.h
	gcc -c -ansi -Wall func1.c -o func1.o
func2.o: func2.c uti1.h func1Lab.h stat_tables.h
	gcc -c -ansi -Wall func2.c -o func2.o
mem_map.o: mem_map.c
	gcc -c -ansi -Wall mem_map.c -o mem_map.o 
util_func.o: util_func.c uti1.h stat_tables.h
	gcc -c -ansi -Wall util_func.c -o util_func.o
