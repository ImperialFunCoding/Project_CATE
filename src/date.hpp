#include <iostream>

using namespace std;

int inMonth(int month, int year);

int dayOfYear(int date) {
    int month = (date/100) % 100;
    int day = date % 100;
    int currentDays = 0;
    int year = date/10000;
    for (int i = 1; i < month; i++) {
        currentDays += inMonth(i, year);
    }
    return currentDays += day;
}

int inMonth(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2:
            if (year % 400 == 0 || (year % 4 == 0 && !(year % 100 == 0))) {
                return 29;
            } else return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
    return 0;
}

int dateDiff(int d1, int d2) {
    int dayofYearDiff = dayOfYear(d2) - dayOfYear(d1);
    int yearDiff = d2/10000 - d1/10000;
    return dayofYearDiff + yearDiff*365;  
}










