#include "Date.h"

/**
  - Constructs a Date object from a string representation of a date in "dd/mm/yyyy" format..
  - Takes {str_date}, which is user's input in the format of "dd/mm/yyyy"
  - Initializes the {date} member which is of the type time_t
  - time_t is used to simplify the date mathematics operations (EX. getting remaining days)
**/
Date::Date(const std::string& str_date) {

    int day, month, year;

    date_string = str_date;

    ParseStringDate(str_date, day, month, year);
    //Converting the integers to the time_t format to simplify further operations
    this->date_time_t = DateToTimeT(day,month,year);
}

/**
    Parsing String inputs of the format dd/mm/yyyy to corresponding integers
**/
void Date::ParseStringDate(const std::string& str_date, int& d, int& m, int& y) {
    //Getting an input stream out of the {str_date} string
    std::istringstream date_stream(str_date);

    //Parse the date using '/' as the delimiter
    char slash;

    date_stream >> d >> slash >> m >> slash >> y;
}

/**
    Converts a date specified by day, month, and year into a time_t value.
**/
std::time_t Date::DateToTimeT(int day, int month, int year) {
    // Create a tm structure and initialize it with the provided date components
    tm tmp = tm();
    tmp.tm_mday = day;          // Set the day of the month
    tmp.tm_mon = month - 1;     // Set the month (0-based, subtract 1)
    tmp.tm_year = year - 1900;  // Set the year (years since 1900)

    // Convert the tm structure to a time_t value
    // mktime() normalizes the values in the tm structure and returns a time_t
    return std::mktime(&tmp);
}


/**
    Getting the DateToday.
    Ex. It can be subtracted from due dates to get the remaining days.
**/
std::time_t Date::Today() {
    // Get the current time as a time_t value
    std::time_t currentTime = std::time(nullptr);

    // Create a buffer to hold the formatted date
    char buffer[11]; // 11 characters to store "dd/mm/yyyy\0"

    // Format the current date and time
    //localtime(): Uses the value pointed by timer to fill a tm structure
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", std::localtime(&currentTime));

    std::string cppString_buffer(buffer);


    int d,m,y;
    ParseStringDate(cppString_buffer,d,m,y);
    return DateToTimeT(d,m,y);
}


/**
    Get the remaining days: between the today, and the date that the object holds.
    - Ex. Getting the remaining days until the due date of a task.
**/
int Date::GetRemainingDays() {

    //Getting the time difference in seconds
    double sec = difftime(this->date_time_t, Today());

    //Then calculating the days out of the seconds
    unsigned int remaining_days = static_cast<unsigned int>(sec / (60 * 60 * 24));

    return remaining_days;

}

/**
    Returns an integer Equivalent to date based on its {day/month/year}.
**/
unsigned Date::GetDate_int() {

    int day,month,year, equiv_int;
    ParseStringDate(this->date_string,day,month,year);

    equiv_int = (day*DAY_FACTOR) + (month*MONTH_FACTOR) + ((year%100)*YEAR_FACTOR);

    return equiv_int;


}

/**
    Returns date in string format.
**/
std::string Date::GetDate_str() {
    return this->date_string;
}


