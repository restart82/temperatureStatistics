all: stat.exe
	
stat.exe: main.o sensor.o
	gcc -o ../stat sensor.o main.o
	del *.o

main.o: main.c config.h
	gcc -c -o main.o main.c

sensor.o: sensor.c sensor.h config.h
	gcc -c -o sensor.o sensor.c