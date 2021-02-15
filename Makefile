CC = gcc
CFLAGS = -g -Wall -c
LFLAGS = -g -Wall 
TARGETS = objects/main.o

calendarFunctions : src/main.c
	$(CC) $(LFLAGS) src/main.c -o calendarFunctions

clean :
	\rm BencomoCalendarFunctions.zip calendarFunctions

zip : 
	zip BencomoCalendarFunctions.zip src/* *