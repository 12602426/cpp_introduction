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

int main() {    
    int MO;
    MO = monthsOld(2022, 2, 9,
                   1999, 6, 3);

    cout << MO << "\n";
    return 0;
}


// g++ -Wall -Wextra helloworld.cpp
// -O3 is een flag die het compilen lang laat duren maar wel snel laat runnen, gebruik niet voor debuggen
