// Your First C++ Program

#include <iostream>
#include <map>
#include <time.h>
#include <vector>

using namespace std;

string birthInput();
int yearsOld(int currentYear, int currentMonth, int currentDay,
             int birthYear, int birthMonth, int birthDay);
int monthsOld(int currentYear, int currentMonth, int currentDay,
              int birthYear, int birthMonth, int birthDay);
int dayOfTheWeek(int birthYear,int birthMonth,int birthDay);


int main() {
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
    cYear =timePtr->tm_year+1900;
    cMonth = timePtr->tm_mon+1;
    cDay= timePtr->tm_mday;

    YO = yearsOld(cYear, cMonth, cDay, birthYear, birthMonth, birthDay);
    cout << "You are " << YO << " years old." << "\n";

    MO = monthsOld(cYear, cMonth, cDay, birthYear, birthMonth, birthDay);
    cout << "You are " << MO << " months old." << "\n";

    cout << "Do you know what day you were born on? Select a number (e.g. 1) \n";
    vector<string> dayInWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (size_t i = 0; i < dayInWeek.size(); i++)
    {
        cout << i + 1 << ": " << dayInWeek[i] << "\n";
    }

    int guess;
    cin >> guess;
    int trueDay = dayOfTheWeek(birthYear, birthMonth, birthDay);
    if (trueDay == guess) {
        cout << "That is correct! \n";
    }
    else {
        cout << "Nope you were born on " << dayInWeek[trueDay - 1] << "\n";
    }

    return 0;
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

    return YearsOld;
}

int monthsOld(int currentYear, int currentMonth, int currentDay,
             int birthYear, int birthMonth, int birthDay) {

    return (currentYear - birthYear) * 12 + currentMonth - birthMonth - (currentDay <= birthDay);
}

int dayOfTheWeek(int birthYear,int birthMonth,int birthDay) {
    // lowest birthday can be 01-01-1900, which is a monday

    // calc leapyears
    int leapYear = 0;
    for (size_t i = 1900; i < birthYear; i++)
    {
      if (i % 4 == 0 and (i % 100 != 0 or i % 400 == 0)) {
        leapYear++;
      }
    }

    if (birthYear % 4 == 0 and (birthYear % 100 != 0 or birthYear % 400 == 0)) {
      if (birthMonth > 2) {
        leapYear++;
      }
    }


    
    int years = birthYear - 1900;
    int days_since_1900 = (years* 365 + leapYear);

    // count days from 01-01-year born to 01-monthborn-yearborn
    const int daysInMonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (size_t i = 0; i < (birthMonth - 1); i++)
    {
        days_since_1900 += daysInMonth[i];
    }

    // count days from 01-monthborn-yearborn to birthday-monthborn-yearborn
    days_since_1900 += birthDay;

    // We dont have to subtract a 1 since, monday is already day 1
    return (days_since_1900 - 1) % 7 + 1;

}
