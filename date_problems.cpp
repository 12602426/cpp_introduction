// Your First C++ Program

#include <iostream>
#include <map>
#include <time.h>

using namespace std;

string birthInput();
int yearsOld(int currentYear, int currentMonth, int currentDay,
             int birthYear, int birthMonth, int birthDay);
int monthsOld(int currentYear, int currentMonth, int currentDay,
              int birthYear, int birthMonth, int birthDay);
int dayOfTheWeek(int birthYear,int birthMonth,int birthDay);


void main() {
    int birthDay, birthMonth, birthYear, YO, MO;
    string birth;
    birth = birthInput();

    birthDay = stoi(birth.substr(0, 2));
    birthMonth = stoi(birth.substr(3, 2)); // waarom werkt dit op deze manier?
    birthYear = stoi(birth.substr(6, 10));

    time_t currentTime;
    time(&currentTime);
    tm* timePtr = localtime(&currentTime);
    int cDay, cMonth, cYear;
    cDay =timePtr->tm_year+1900;
    cMonth = timePtr->tm_mon+1;
    cYear = timePtr->tm_mday;

    YO = yearsOld(cYear, cMonth, cDay, birthYear, birthMonth, birthDay);
    MO = monthsOld(cYear, cMonth, cDay, birthYear, birthMonth, birthDay);

}

string birthInput() {
    string birth;
    int birthDay, birthMonth, birthYear;
    bool correctInput{false};
    do {
        cout << "Can you tell me your birth date (e.g. 01-01-2001)" << "\n";
        cin >> birth;
        try
        {
            birthDay = stoi(birth.substr(0, 2));
            birthMonth = stoi(birth.substr(3, 2)); // waarom werkt dit op deze manier?
            birthYear = stoi(birth.substr(6, 10));
            correctInput = true;

            if (birthYear < 1900 or birthYear > 2100 ) {
                cout << "Incorrent age!" << "\n";
                correctInput = false;
            }
        
            int daysInMonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (birthDay > daysInMonth[birthMonth - 1]) {
                if (birthMonth == 2 and birthYear % 4 == 0 and birthYear % 100 != 0) {
                    cout << "Not many people were born on this day!";
                }
                else {
                    cout << "Are there that many days in this month?" << "\n";
                    correctInput = false;
                }
                
            }

            if (birthDay < 1 or birthMonth < 1) {
                cout << "incorrect input" << "\n";
                correctInput = false;
            }

        }
        catch(const std::exception& e)
        {

            cout << "Your input is incorrect, make sure to get it right! \n";
        }

    }
    while (!correctInput);

    return birth;
}

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
    cout << YearsOld << "\n";
    
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

