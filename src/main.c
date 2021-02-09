#include "calendar.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>



int main(int commandCount, char *commands[])
{
    printf("command is %s\n", commands[1]);
    char *date1_str = commands[1];

    printf("date1 is %s\n", date1_str);
    
    newDate(date1_str);

    printf("The day selected is %d ", date1.day);

    return 0;
}
