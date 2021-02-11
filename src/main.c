#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

const char* dayString[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
const char* monthString[] = {NULL, "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int monthLength[] = {0, 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};

// This function adds the values to a new date array
void newFullDate(char* date_str, int date[])
{
    int tokenCount = 0;
    char* token = strtok(date_str, "/");

    while (token != NULL)
    {
        if(tokenCount == 0)
        {
            date[1] = atoi(token);
        }
        else if(tokenCount == 1)
        {
            date[0] = atoi(token);
        }
        else if(tokenCount == 2)
        {
            date[2] = atoi(token);
        }
        else
        {
            printf ("ERROR: too many tokens, the input format was incorrect, make sure to use MM/DD/YYYY\n");
            return;
        }

        tokenCount++;
        token = strtok(NULL,"/");
    }
    if(tokenCount < 2)
    {
        printf("ERROR: Not enough tokens, the input format was incorrect, make sure to use MM/DD/YYYY\n");
        exit(0);
    }

    if(date[1] > 12)
    {
        printf("ERROR: month cannot be higher than 12\n");
        exit(0);
    }
    if(date[0] > monthLength[date[1]])
    {
        printf("ERROR: this month does not have this many days\n");
        exit(0);
    }
}

void newSmallDate(char* date_str, int date[])
{
    int tokenCount = 0;
    char* token = strtok(date_str, "/");
    date[0] = 1;

    while (token != NULL)
    {
        if(tokenCount == 0)
        {
            date[1] = atoi(token);
        }
        else if(tokenCount == 1)
        {
            date[2] = atoi(token);
        }
        else
        {
            printf ("ERROR: too many tokens, the input format was incorrect, make sure to use MM/YYYY\n");
            exit(0);
        }


        tokenCount++;
        token = strtok(NULL,"/");
    }
    if(tokenCount < 1)
    {
        printf("ERROR: Not enough tokens, the input format was incorrect, make sure to use MM/YYYY\n");
        exit(0);
    }

    if(date[1] > 12)
    {
        printf("ERROR: month cannot be higher than 12\n");
        exit(0);
    }
}

// This function prints out the a selected month
void printMonth(int date[])
{
    int year_part1, year_part2, F_value, dayCode, monthCode, monthSize;
    year_part1 = date[2]/100;
    year_part2 = date[2]%100;

    if(date[1] < 3)
    {
        year_part2--;
        monthCode = date[1] + 10;
    }
    else
    {
        monthCode = date[1] - 2;
    }

    F_value = date[0] + ((13*monthCode-1)/5) + year_part2 + (year_part2/4) + (year_part1/4) - 2*year_part1;
    dayCode = F_value % 7;

    monthSize = monthLength[date[1]];
    if(date[1] == 2 && ((date[2]%4 == 0 && date[2]%100 != 0) || date[2]%400 == 0))
    {
        monthSize++;
    }

    printf("\n\n");
    printf("\t\t%s, %d\n", monthString[date[1]], date[2]);
    for(int day = 0; day < 7; day++ )
    {
        printf("%s\t", dayString[day]);
    }

    printf("\n");
    
    
    for(int day = 1; day <= monthSize; day++)
    {
        if (day == 1)
        {
            for(int i = 0; i < dayCode; i++)
            {
                printf("\t");
            }
        }
        
        if(dayCode > 6)
        {
            dayCode = 0;
            printf("\n");
        }

        printf("%d\t", day);
        dayCode++;
    }
    printf("\n\n");
}

int daysSinceEpoch(int date[])
{
    int y = date [2];
    int m = date [1];
    int d = date [0];
    if(m < 3)
    {
        y--;
        m += 12;
    }

    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}

void countDays(int dateFrom[], int dateTo[])
{
    int difference = daysSinceEpoch(dateTo) - daysSinceEpoch(dateFrom);
    printf("The day difference between %d/%d/%d", dateFrom[1], dateFrom[0],dateFrom[2]);
    printf(" and %d/%d/%d is: %d days\n", dateTo[1], dateTo[0], dateTo[2], difference);
}



int main(int commandCount, char *commands[])
{
    if(strcasecmp(commands[1], "print") == 0)
    {
        if(commandCount == 3)
        {
            int date[3];
            newSmallDate(commands[2], date);
            printMonth(date);
        }
        else
        {
            printf("ERROR: Command line argument number does not match format\n");
            printf("Please use the following format when using the command \"Print\"\n");
            printf("./calendarFunctions print MM/YYYY\n");
        }
    }
    else if(strcasecmp(commands[1], "count") == 0)
    {
        if(commandCount == 4)
        {
            int date1[3], date2[3];
            newFullDate(commands[2],date1);
            newFullDate(commands[3],date2);
            countDays(date1, date2);
        }
        else
        {
            printf("ERROR: Command line argument number does not match format\n");
            printf("Please use the following format when using the command \"Print\"\n");
            printf("./calendarFunctions count MM/DD/YYYY MM/DD/YYYY\n");
        }
    }
    else
    {
        printf("ERROR: Command not recognized\n");
        printf("Please use the the commands \"print\" and \"count\"\n");
    }

    return 0;
}
