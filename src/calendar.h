#ifndef CALENDAR_H
#define CALENDAR_H

typedef struct Date 
{
    int day;
    int month;
    int year;
}Date;

extern Date date1;
extern Date date2;

void newDate(char* date);

#endif