#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED


/****** All Possible Errors that my application may produce ******/
typedef enum{
    OPERATION_SUCCESS = 0,
/**View-related Errors**/
/*Improper option selection*/
    ERROR_INVALID_MENU_OPTION,

/*Improper data format*/
    //Username format errors
    ERROR_INVALID_USER_NAME_FORMAT,

    //Password format errors
    ERROR_INVALID_PASSWORD_FORMAT,

    //TaskName format errors
    ERROR_INVALID_TASK_NAME_FORMAT,

    //DueDate format errors
    ERROR_INVALID_DATE_FORMAT,
    ERROR_DATE_IS_BEFORE_TODAT,

    //TaskWeight format errors
    ERROR_INVALID_TASK_WEIGHT_FORMAT,

    //TaskID format errors
    ERROR_INVALID_TASK_ID_FORMAT,


/**Auth/Model-related Errors**/
    //Username
    ERROR_USERNAME_ALREADY_EXIST, //(REGISTER)

    //Username-Password     
    ERROR_WRONG_PASSWORD_OR_USERNAME,   //(LOGIN)

    //Task ID
    ERROR_TASK_ID_DOESNT_EXIST,
}Error_t;

#endif // ERROR_H_INCLUDED
