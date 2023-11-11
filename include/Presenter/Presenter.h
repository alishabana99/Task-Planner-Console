#ifndef PRESENTER_H_INCLUDED
#define PRESENTER_H_INCLUDED

#include <string>
#include "UserManager.h"
#include "AuthenticationManager.h"
#include "ErrorState.h"


class Presenter{

private:
    /**Private Data**/
    UserManager user_manager;  //accessing all Model Module Functionalities
    AuthenticationManager auth_manager; //accessing all Authentication Functionalities
    
    
    /**Private Methods**/


public:
    /**Public Data**/
    
    /**Public Methods**/
    /*Redirecting all possible user commands to the concerned module*/
    Error_t LoginUser(std::string usr, std::string pass);
    Error_t RegisterUser(std::string usr, std::string pass);
    void AddTask(std::string name, std::string due, char w);
    Error_t DeleteTask(int tid);
    Error_t MarkDoneTask(int tid);
    void DeleteAllDone();
    void DeleteAllTasks();
    void LogoutUser();
    void SaveUser();
    void DisplayUserMatrix();
    bool Init();

};

#endif // PRESENTER_H_INCLUDED
