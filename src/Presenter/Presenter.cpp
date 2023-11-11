#include "Presenter.h"




Error_t Presenter::LoginUser(std::string usr, std::string pass) {


    //1. Check user authentcation using the authenticator module. 
    if ( !(this->auth_manager.CheckIfLoginDataMatch(usr, pass)) ) {
        //wrong username or password
        return ERROR_WRONG_PASSWORD_OR_USERNAME;
    }

    //2. Tell The UserManager To login, so it updates its {current_user} by retreing user's data from DB.
    this->user_manager.LoginUser(usr);
    
    return OPERATION_SUCCESS;
}


Error_t Presenter::RegisterUser(std::string usr, std::string pass){
    
    //1. Check username is already exists '
    if ((this->auth_manager.CheckIfUsernameExists(usr))) {
        //username already exists
        return ERROR_USERNAME_ALREADY_EXIST;
    }

    //2. register the new user 
    this->user_manager.RegisterUser(usr, pass);

    return OPERATION_SUCCESS;
}


void Presenter::AddTask(std::string name, std::string due, char w){

    //1. adding task to the user manger that adds it to the {current_user}
    this->user_manager.AddTask(name, due, w);

}


Error_t Presenter::DeleteTask(int tid){

    //1. Check task id is real
    if (!(this->user_manager.DeleteTask(tid))) {
        //task id doesn't exist
        return ERROR_TASK_ID_DOESNT_EXIST;
    }

    //2. Task Deleted
    return OPERATION_SUCCESS;

}


Error_t Presenter::MarkDoneTask(int tid){

    //1. Check task id is real
    if (!(this->user_manager.MarkDoneTask(tid))) {
        //task id doesn't exist
        return ERROR_TASK_ID_DOESNT_EXIST;
    }

    //2. Task Marked done
    return OPERATION_SUCCESS;

}


void Presenter::DeleteAllDone() {

    this->user_manager.DeleteAllDoneTasks();

}
void Presenter::DeleteAllTasks() {

    this->user_manager.DeleteAllTasks();

}




void Presenter::LogoutUser() {
    
    //1. logging out user  -> this saves user data
    this->user_manager.LogoutCurrentUser();
}

void Presenter::SaveUser() {
    
    this->user_manager.SaveCurrentUser();

}


void Presenter::DisplayUserMatrix() {

    this->user_manager.DisplayCurrentMatrix();

}


bool Presenter::Init() {
    return this->user_manager.InitSession();
}
