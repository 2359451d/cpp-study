/* 
    SP Exercise 1A
    Name: Yao Du
    GUID: 2359451D

    This is my own work as defined in the Academic Ethics agreement I have signed.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "date.h"

struct date{
    int year;
    int month;
    int day;
};

// prototype
Date *date_create(char *datestr);
Date *date_duplicate(Date *d);
int date_compare(Date *date1, Date *date2);
void date_destroy(Date *d);


Date *date_create(char* datestr)
{
    Date* date = (Date*)malloc(sizeof(Date));
    if(!date) return NULL;

    sscanf(datestr, "%d/%d/%d", &date->day, &date->month, &date->year);
    //pitfalls
    if ((date->year <= 0)||(date->day<1 || date->day>31) || (date->month<1 || date->month>12)) {
      return NULL;
    }
  return date;
}

Date *date_duplicate(Date *d)
{
    Date* date_copy = (Date*)malloc(sizeof(Date));
    if(!date_copy) return NULL;
    *date_copy = *d;
    return date_copy;
};

/* 
    compares 2 dates
    return:
        <0 - date1<date2
        =0 - date1=date2
        >0 - date1>date2
 */
int date_compare(Date *date1, Date *date2)
{
    int diff = 0;
    if (date1 != NULL && date2 == NULL)
        return 1;
    if (date1 == NULL && date2 != NULL)
        return -1;

    diff = date1->year - date2->year;
    if (diff == 0) {
        diff = date1->month - date2->month;
        if (diff == 0) {
            diff = date1->day - date2->day;
        }
    }
    return diff;
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d)
{
    free(d);
    d=NULL;
};
