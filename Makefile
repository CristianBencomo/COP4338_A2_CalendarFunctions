CC = gcc
CFLAGS = -g -Wall -c
LFLAGS = -g -Wall 
TARGETS = objects/main.o objects/calendar.o
HEADERS = Calendar.h
vpath %.c src
vpath %.h src


calendarFunctions : $(TARGETS)
	$(CC) $(LFLAGS) $(TARGETS) -o calendarFunctions

objects/main.o : main.c calendar.c calendar.h 
	$(CC) $(CFLAGS) src/main.c -o objects/main.o

objects/calendar.o : calendar.c calendar.h 
	$(CC) $(CFLAGS) src/calendar.c -o objects/calendar.o

clean :
	\rm -r BencomoCalendarFunctions.zip objects/* calendarFunctions

zip : 
	zip BencomoCalendarFunctions.zip objects src calendarFunctions