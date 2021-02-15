#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


const char* dayString[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}; //Stores the days of the week in its respective location
const char* monthString[] = {NULL, "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; //Stores the months in its respective locations
const int monthLength[] = {0, 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31}; //Stores the amount of day per month location

// Stores the string date_str as separate integers for month/day/year
void newFullDate(char* date_str, int date[])
{
    int tokenCount = 0;
    char* token = strtok(date_str, "/");

    while (token != NULL)
    {
        //Storing tokens inside the date array
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
        else //Too many tokens
        {
            printf ("ERROR: too many tokens, the input format was incorrect, make sure to use MM/DD/YYYY\n");
            return;
        }

        tokenCount++;
        token = strtok(NULL,"/");
    }
    if(tokenCount < 2) //Not enough tokens
    {
        printf("ERROR: Not enough tokens, the input format was incorrect, make sure to use MM/DD/YYYY\n");
        exit(0);
    }

    if(date[1] > 12) //Incorrect month input
    {
        printf("ERROR: month cannot be higher than 12\n");
        exit(0);
    }
    if(date[0] > monthLength[date[1]]) //Incorrect day input
    {
        printf("ERROR: this month does not have this many days\n");
        exit(0);
    }
}

// Stores the string date_str as separate integers for month/year
void newSmallDate(char* date_str, int date[])
{
    int tokenCount = 0;
    char* token = strtok(date_str, "/");
    date[0] = 1;

    //Assigning tokens to date array
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
        else // too many tokens
        {
            printf ("ERROR: too many tokens, the input format was incorrect, make sure to use MM/YYYY\n");
            exit(0);
        }


        tokenCount++;
        token = strtok(NULL,"/");
    }
    if(tokenCount < 1) // not enough tokens
    {
        printf("ERROR: Not enough tokens, the input format was incorrect, make sure to use MM/YYYY\n");
        exit(0);
    }

    if(date[1] > 12) //Incorrect month input
    {
        printf("ERROR: month cannot be higher than 12\n");
        exit(0);
    }
}

/*
 * This function prints out the selected month
 * 
 * To calculate this we use the formula:
 * F = k + [(13*m-1)/5] +D+ [D/4] +[C/4]-2*C
 * for further information on the algorithm, read README.md
 */
void printMonth(int date[])
{
    int year_part1, year_part2, F_value, dayCode, monthCode, monthSize;
    year_part1 = date[2]/100; // first two digits of the year
    year_part2 = date[2]%100; // last two digits of the year

    //setting up month and year to match formula input
    if(date[1] < 3)
    {
        year_part2--;
        monthCode = date[1] + 10;
    }
    else
    {
        monthCode = date[1] - 2;
    }

    // Formula
    F_value = date[0] + ((13*monthCode-1)/5) + year_part2 + (year_part2/4) + (year_part1/4) - 2*year_part1;
    dayCode = F_value % 7;

    monthSize = monthLength[date[1]];
    //Addidng 1 to monthSize if its a leap february
    if(date[1] == 2 && ((date[2]%4 == 0 && date[2]%100 != 0) || date[2]%400 == 0))
    {
        monthSize++;
    }

    //Printing
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

/*
 * This function counts the days since the Rada Die epoch date
 * for further information on the algorithm, read README.md
 */
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

/*
 * This function uses the difference between the daysSinceEpoch results
 * for further information on the algorithm, read README.md
 */
void countDays(int dateFrom[], int dateTo[])
{
    int difference = daysSinceEpoch(dateTo) - daysSinceEpoch(dateFrom);
    printf("The day difference between %d/%d/%d", dateFrom[1], dateFrom[0],dateFrom[2]);
    printf(" and %d/%d/%d is: %d days\n", dateTo[1], dateTo[0], dateTo[2], difference);
}

//Main Function
int main(int commandCount, char *commands[])
{
    //Print command
    if(strcasecmp(commands[1], "print") == 0)
    {
        if(commandCount == 3)
        {
            int date[3];
            newSmallDate(commands[2], date);
            printMonth(date);
        }
        else //Error in input
        {
            printf("ERROR: Command line argument number does not match format\n");
            printf("Please use the following format when using the command \"Print\"\n");
            printf("./calendarFunctions print MM/YYYY\n");
        }
    }
    // Count Command
    else if(strcasecmp(commands[1], "count") == 0)
    {
        if(commandCount == 4)
        {
            int date1[3], date2[3];
            newFullDate(commands[2],date1);
            newFullDate(commands[3],date2);
            countDays(date1, date2);
        }
        else // Error in input
        {
            printf("ERROR: Command line argument number does not match format\n");
            printf("Please use the following format when using the command \"Print\"\n");
            printf("./calendarFunctions count MM/DD/YYYY MM/DD/YYYY\n");
        }
    }
    else // No command selected
    {
        printf("ERROR: Command not recognized\n");
        printf("Please use the the commands \"print\" and \"count\"\n");
    }

    return 0;
}
