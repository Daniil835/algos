proga2 : main.o lodepng.o
	gcc main.o lodepng.o -o proga2

main.o : main.c
	gcc -c main.c -o main.o

lodepng.o : lodepng.c
	gcc -c lodepng.c -o lodepng.o

clean : 
	rm proga2 *.o

