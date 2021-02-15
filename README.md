# COP 4338
Assignment 2         
Cristian Bencomo

## Description 
this program has two functionalities: 
> It outputsthe weeks of a Gregorian month given a year number and month name.                 
> It counts  the  number of days between two dates;       

## Contents
*   src folder containing main.c file
*   Makefile
*   calendarFunctions built object

## How to use
You may use the command "make" to rebuild the object, "make zip" to zip the contents, and "make clean" to delete the zip file and object files.

### Program input options
> count MM/DD/YYYY mm/dd/yyyy            
> print MM/YYYY”   


## Algorithm details     

### printMonth(int date[])
#### Zeller's rule

Will be used within main.c to determine the day of a date

> F = k + [(13*m-1)/5] +D+ [D/4] +[C/4]-2*C          

Where:    
k is  the day of the month.       
m is the month number.           
D is the last two digits of the year.                   
C is the first two digits of the year.       
          
|Date|  March|April|May|June|July|August|September|October|November|December|January|February|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|Index|1|2|3|4|5|6|7|8|9|10|11|12|
<br />

It is visible that the months start in March for this algorithm.       
Here are the steps followed:

* If wanted month is Jan or Feb subtract one from the year (discard decimal values as well)
* Find F
* then use F%7 and the result is the "Daycode"

|Sun|Mon|Tue|Wed|Thu|Fri|Sat|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|0|1|2|3|4|5|6|

Source:
https://beginnersbook.com/2013/04/calculating-day-given-date/ 
 
<br />
<br />

### countDays(int dateFrom[], char *commands[])
this algorithm is using Rata Die as an epoch date to calculate date differences 

Function:
* if month is feb or jan
	* subtract one year and add 12 to month
* return the result of the formula           
y = year             
m = month                
d = day

> Result = 3658*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306

The result is the days passed since the epoch date, so we simply subtract the result received when plugging in two dates


Source:
https://stackoverflow.com/questions/14218894/number-of-days-between-two-dates-c