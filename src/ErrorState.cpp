#include "ErrorState.h"
#include <sstream>

std::map<Error_t, std::string> ErrorState::error_messages = {
    /*username rules:
        - isn't empty
        - doesn't include spaces
        - between [1-30] character long
        - doesn't include special characters, only [a-z]or/and[0-9]
        */
    /**View-related Errors**/
    {OPERATION_SUCCESS,
    "Succeeded!!"},

    {ERROR_INVALID_MENU_OPTION,
    "Error: Invalid menu option!! Please choose a valid one." },

    {ERROR_INVALID_USER_NAME_FORMAT,
    "Error: Invalid username format!! Please re-enter username,\n\
It's expected to be [1-30] chars, no special chars, no spaces, and for sure not Empty!!" },

    {ERROR_INVALID_PASSWORD_FORMAT,
    "Error: Invalid password format!! Passwords must be [8-100] chars long!!" },
    
    {ERROR_INVALID_TASK_NAME_FORMAT,    "Error: Invalid task name format!! re-enter another name and don't leave it empty" },
    {ERROR_INVALID_DATE_FORMAT,         "Error: Invalid Date format!! please stick with the DD/MM/YYYY format."},
    {ERROR_INVALID_TASK_WEIGHT_FORMAT,  "Error: Invalid task weight format!! choose a weight from (H, M, L). Select How to decide tasks weight, if you need help."},
    {ERROR_INVALID_TASK_ID_FORMAT,      "Error: Task ID is invalid!! choose an ID from those that are in the matrix."},
    /**Auth/Model-related Errors**/
    {ERROR_USERNAME_ALREADY_EXIST,      "Error: Entered username already exists!! Choose another one."},
    {ERROR_WRONG_PASSWORD_OR_USERNAME,  "Error: Wrong Username or Password!!"},
    {ERROR_TASK_ID_DOESNT_EXIST,        "Error: Task ID is doesn't exist!! choose an ID from those that are in the matrix."}

};






std::string ErrorState::GetErrorMessage(Error_t state) {
    if (ErrorState::error_messages.find(state) != ErrorState::error_messages.end())
        return ErrorState::error_messages[state];
    else
        return "ERROR: INVALID STATE !!!!!!!!!!!!!!!!!!!!";
}


/**Data Format Assertions**/


/*
Possible errors states:
    - ERROR_INVALID_USER_NAME_FORMAT
    - OPERATION_SUCCESS
*/
Error_t ErrorState::AssertUsername(std::string usrname) {
    /*username rules:
        - isn't empty
        - doesn't include spaces
        - between [2-30] character long
        - doesn't include special characters, only [a-z]or/and[0-9]
        */

    std::regex format (USERNAME_FORMAT);

    if (std::regex_match (usrname,format)) {
        return OPERATION_SUCCESS;
    } else {
        return ERROR_INVALID_USER_NAME_FORMAT;
    }
}


/*
Possible errors states:
    - ERROR_INVALID_PASSWORD_FORMAT
    - OPERATION_SUCCESS
*/
Error_t ErrorState::AssertPassword(std::string pass) {
    /*password rules:
    - isn't empty
    - between [8-100] character long
    */
    std::regex format (PASSWORD_FORMAT);

    if (std::regex_match (pass,format)) {
        return OPERATION_SUCCESS;
    } else {
        return ERROR_INVALID_PASSWORD_FORMAT;
    }
}


/*
Possible errors states:
    - ERROR_INVALID_TASK_NAME_FORMAT
    - OPERATION_SUCCESS
*/
Error_t ErrorState::AssertTaskName(std::string tname) {
    /*task name rules:
    - isn't empty
    - between [1-29] character long
    */
    std::regex mregex (TASK_NAME_FORMAT);

        if (std::regex_match (tname,mregex)) {
            return OPERATION_SUCCESS;
        } else {
            return ERROR_INVALID_TASK_NAME_FORMAT;
        }
}


/*
Possible errors states:
    - ERROR_INVALID_DATE_FORMAT
    - ERROR_DATE_IS_BEFORE_TODAT
    - OPERATION_SUCCESS

*/
Error_t ErrorState::AssertDueDate(std::string due){
    /*due date rules:
    - isn't empty
    - in the form of DD/MM/YYYY
    - days can't exceed the number of month days (ex. April cannot be 31 days, so we can't have that date: 31/4/2023)
    - days [1-31]
    - months [1-12]
    - years [2023-2099]
    - date can't be before today
    */
    //1. Check format, days [1-31], months [1-12], years [2023-2099]
    std::regex mregex(DUE_DATE_FORMAT);

    if (!std::regex_match(due, mregex)) {
        return ERROR_INVALID_DATE_FORMAT;
    }


    //2. Check months against their valid days (regarding leap years)
        /*
            -Jan:31  -Feb:28/29   -Mar:31  -Apr:30  -May:31  -Jun:30  -Jul:31  -Aug:31  -Sep:30	-Oct:31  -Nov:30 -Dec:31
        */
        // Separate day, month, and year
    int day, month, year;
    std::stringstream date_stream(due); 
    char slash;

    date_stream >> day >> slash >> month >> slash >> year;

//    sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);

    // Check if the day is valid for the given month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return ERROR_INVALID_DATE_FORMAT;
    }
    else if (month == 2) {
        // Check for leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return ERROR_INVALID_DATE_FORMAT;
        }
    }


    //3. Check if the date isn't after today
    Date due_date(due);
    if (due_date.GetRemainingDays() < 0) {
        return ERROR_DATE_IS_BEFORE_TODAT;
    }

    

    //Now we are good
    return OPERATION_SUCCESS;

}


/*
Possible errors states:
    - ERROR_INVALID_TASK_WEIGHT_FORMAT
    - OPERATION_SUCCESS
*/
Error_t ErrorState::AssertWeight(char tweight){
/*Weight rules:
    - Isn't empty
    - One of the 3 values -> { 'H'/'h', 'M'/'m', 'L'/'l' }
*/
    std::regex mregex(TASK_WEIGHT_FORMAT);

    if (!std::regex_match(std::string(1,tweight), mregex)) {
        return ERROR_INVALID_TASK_WEIGHT_FORMAT;
    }


    return OPERATION_SUCCESS;
}


/*
Possible errors states:
    - ERROR_INVALID_TASK_ID_FORMAT
    - OPERATION_SUCCESS
*/
Error_t ErrorState::AssertID(std::string tid) {
/*ID rules:
    - Isn't empty
    - Only a number
    - Doesn't exceed 5 digits (max date that can 30/12/2099  is a 5-digit number {36,525})
    - Isn't more than 39,999 (the same reason as above)
*/
    std::regex mregex(TASK_ID_FORMAT);

    if (!std::regex_match(tid, mregex)) {
        return ERROR_INVALID_TASK_ID_FORMAT;
    }


    return OPERATION_SUCCESS;
}

