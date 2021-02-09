#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calendar.h"

void newDate(char* date)
{
    int tokenCount = 0;
    char* token = strtok(date, "/");

    while (token != NULL)
    {
        if(tokenCount == 0)
            date1.day = atoi(token);
        if(tokenCount == 1)
            date1.month = atoi(token);
        if(tokenCount == 2)
            date1.year = atoi(token);
        else
            printf ("ERROR: too many tokens, the input format was incorrect, make sure to use MM/DD/YYYY");
        
        tokenCount++;
    }
}