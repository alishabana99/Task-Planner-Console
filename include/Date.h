#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED


#include <ctime>
#include <string>
#include <sstream>
#include "Utility.h"

#define DAY_FACTOR 1
#define MONTH_FACTOR 30
#define YEAR_FACTOR 365

#define MAX_DATE_INT 37000  /*until 30/12/2099*/
#define MIN_DATE_INT 8500   /*No one will set a date before the day I'm writing this code :D*/

class Date {

private:
    /*Data*/
    std::time_t date_time_t;
    std::string date_string;

    /*private Methods*/
    static time_t DateToTimeT(int day, int month, int year);
    static void ParseStringDate(const std::string& str_date, int& d, int& m, int& y);
    static time_t Today();

public:
    /*public Methods*/
    Date() = default;
    Date(const std::string& str_date);
    int GetRemainingDays();
    unsigned int GetDate_int();
    std::string GetDate_str();

};


#endif // DATE_H_INCLUDED
