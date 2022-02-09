// Your First C++ Program

#include <iostream>
#include <map>
#include <time.h>

using namespace std;

int yearsOld(int currentYear, int currentMonth, int currentDay,
             int birthYear, int birthMonth, int birthDay) {

    int YearsOld;

    // previous birthdays, ecept for (maybe) latest
    YearsOld = currentYear - birthYear - 1;

    // Check if birthday was this year
    if (birthMonth < currentMonth) {
        YearsOld += 1;
    }
    // Check if birthday was this month
    if (birthMonth  == currentMonth and birthDay < currentDay) {
        YearsOld += 1;
    }
    
    return YearsOld;
}

int monthsOld(int currentYear, int currentMonth, int currentDay,
             int birthYear, int birthMonth, int birthDay) {

    return (currentYear - birthYear) * 12 + currentMonth - birthMonth - (currentDay < birthDay);
}

int dayOfTheWeek(int birthYear,int birthMonth,int birthDay) {
    int years = birthYear - 1900;
    cout << years << "\n";
    int leapYears = years / 4 - years / 100;
    cout << leapYears << "\n";
    int days_since_1900 = (years* 365 + leapYears);

    const int daysInMonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (size_t i = 0; i < (birthMonth - 1); i++)
    {
        days_since_1900 += daysInMonth[i];
    }

    days_since_1900 += birthDay;

    cout << days_since_1900 << "\n";
    cout << days_since_1900 % 7 << "\n";
    return days_since_1900 % 7;
    
}

int main() {    
    dayOfTheWeek(1999, 6, 3);
    return 0;
}


// g++ -Wall -Wextra helloworld.cpp
// -O3 is een flag die het compilen lang laat duren maar wel snel laat runnen, gebruik niet voor debuggen
