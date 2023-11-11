#ifndef USERMANAGER_H_INCLUDED
#define USERMANAGER_H_INCLUDED


#include "FileDatabaseManager.h"
#include "User.h"
#include <string>


class UserManager{
private:
    /*Private Data*/
    IUserModel* database ;
    User current_user;
    /*Private Methods*/

public:
    /*Public Data*/
    UserManager();
    virtual ~UserManager();

    /*Public Methods*/
//User's data persistence
void AddTask(std::string name, std::string due, char w);
bool DeleteTask(int taskid);
bool MarkDoneTask(int taskid);
void DeleteAllDoneTasks();
void DeleteAllTasks();



//Database manipulation
 void SaveCurrentUser();
 void LogoutCurrentUser();
 void DeleteCurrentUser();
 void RegisterUser(std::string usrname, std::string pass);
 void LoginUser(const std::string& usrname);
 void DisplayCurrentMatrix();

 //init Current user, if there's any open session.
 bool InitSession();
};

#endif // USERMANAGER_H_INCLUDED
