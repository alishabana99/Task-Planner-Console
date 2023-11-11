#include "UserManager.h"


UserManager::UserManager() {
    this->database = new FileDatabaseManager();
}

UserManager::~UserManager() {
    delete(this->database);
}

/* User's data persistence */ 
void UserManager::AddTask(std::string name, std::string due, char w){

    TaskWeight_t tw; 
    //1. getting the task weight out of the parameters
    switch (w) {
    case 'H':
    case 'h':
        tw = HIGH_WEIGHT;
        break;
    case 'M':
    case 'm':
        tw = MID_WEIGHT;
        break;
    case 'L':
    case 'l':
        tw = LOW_WEIGHT;
        break;
    default:
        break;
    }

    //2. building the task
    Task t = Task(name, due, tw);

    //3. adding the task
    this->current_user.AddTask(t);
}


bool UserManager::DeleteTask(int taskid){

    return this->current_user.DeleteTask(taskid);
}


bool UserManager::MarkDoneTask(int taskid){

    return this->current_user.MarkDoneTask(taskid);
}

void UserManager::DeleteAllDoneTasks() {

    this->current_user.DeleteAllDone();

}
void UserManager::DeleteAllTasks(){

    this->current_user.DeleteAllTasks();

}


//Database manipulation
 void UserManager::SaveCurrentUser() {
    std::string usrnme = this->current_user.GetUsername();
    std::string serialized_user = this->current_user.Serialize();

    this->database->SaveUser(usrnme,serialized_user);
 }

 void UserManager::LogoutCurrentUser(){
    this->SaveCurrentUser();
    
    //update session data/ close it
    this->database->UpdateSession(false, "");
 }

 void UserManager::DeleteCurrentUser(){
    std::string usrnme = this->current_user.GetUsername();

    this->database->DeleteUser(usrnme);
 }


 void UserManager::RegisterUser(std::string usrname, std::string pass){
    this->current_user = User(usrname,pass);

    this->SaveCurrentUser();

 }
 void UserManager::LoginUser(const std::string& usrname){

    std::string serialized_user= this->database->LoadUser(usrname);
    if (serialized_user == "")
        return; 

    this->current_user = this->current_user.DeSerialize(serialized_user);

    //update session/ open it
    this->database->UpdateSession(true, usrname);

 }
 

 void UserManager::DisplayCurrentMatrix() {

     this->current_user.DisplayMatrix();

 }



 bool UserManager::InitSession() {

     std::string session_user;
     session_user = this->database->GetSession();
     
     if (session_user != "") {
         this->LoginUser(session_user);
         return true;
     }
     else {
         //there is no open session
         return false;
     }

 }