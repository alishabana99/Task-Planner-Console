#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include<string>
#include"Matrix.h"
#include "ISerializableToString.h"
#include "Utility.h"

#include<iostream>

class User : ISerializableToString<User> {

private:
    std::string username;
    std::string password;
    Matrix tasks_matrix;


public:

    User(std::string username, std::string pass);
    User()= default;

    /*Getters*/
    std::string GetUsername();
    std::string GetPassword();

    /*Matrix Ops*/
    //-------------------
    void AddTask(Task t);
    bool DeleteTask(int task_id);
    bool MarkDoneTask(int task_id);
    void DeleteAllDone();
    void DeleteAllTasks();
    void DisplayMatrix();


    std::string Serialize() override;
    /*
    Note that fields must be de-serialized in the same order they were serialized in.
    */
    User DeSerialize(const std::string& result) override;

};


#endif // USER_H_INCLUDED
