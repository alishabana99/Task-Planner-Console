#ifndef ERRORHANDLER_H_INCLUDED
#define ERRORHANDLER_H_INCLUDED

#include <map>
#include <string>
#include "Error.h"
#include "Date.h"
#include <regex>


/****** Data Acceptable Formats ******/
#define USERNAME_FORMAT     "^[aA-zZ0-9]{1,30}$"
#define PASSWORD_FORMAT     "^.{8,100}$"
#define TASK_NAME_FORMAT    "^([A-Za-z0-9]{1})([A-Za-z0-9]{1}| {0,1}){1,29}$"
#define DUE_DATE_FORMAT     "^(([3][0-1])|([1-2][0-9])|([0]{0,1}[1-9]))\/(([1][0-2])|([0]{0,1}[1-9]))\/(20(([2][3-9])|([3-9][0-9])))$"
#define TASK_WEIGHT_FORMAT  "^[HhMmLl]$"
#define TASK_ID_FORMAT      "^[1-3]{0,1}[0-9]{1,4}$"


class ErrorState{
private:
    static std::map<Error_t,std::string> error_messages;

public:
    

static std::string GetErrorMessage(Error_t state);


/**Data Format Assertions**/


/*
Possible errors states:
    - ERROR_INVALID_USER_NAME_FORMAT
    - OPERATION_SUCCESS
*/
static Error_t AssertUsername(std::string usrname);


/*
Possible errors states:
    - ERROR_INVALID_PASSWORD_FORMAT
    - OPERATION_SUCCESS
*/
static Error_t AssertPassword(std::string pass);


/*
Possible errors states:
    - ERROR_INVALID_TASK_NAME_FORMAT
    - OPERATION_SUCCESS
*/
static Error_t AssertTaskName(std::string tname);


/*
Possible errors states:
    - ERROR_INVALID_DATE_FORMAT
    - ERROR_DATE_IS_BEFORE_TODAT
    - OPERATION_SUCCESS

*/
static Error_t AssertDueDate(std::string due);


/*
Possible errors states:
    - ERROR_INVALID_TASK_WEIGHT_FORMAT
    - OPERATION_SUCCESS
*/
static Error_t AssertWeight(char tweight);


/*
Possible errors states:
    - ERROR_INVALID_TASK_ID_FORMAT
    - OPERATION_SUCCESS
*/
static Error_t AssertID(std::string tid);


};

#endif // ERRORHANDLER_H_INCLUDED
