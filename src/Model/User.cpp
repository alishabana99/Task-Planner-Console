#include "User.h"

User::User(std::string username, std::string pass) {
    this->username = username;
    this->password = pass;


}


void User::AddTask(Task t) {
    this->tasks_matrix.AddTaskToMatrix(t);
}

bool User::DeleteTask(int task_id) {
    return this->tasks_matrix.DeleteTaskFromMatrix(task_id);
}

bool User::MarkDoneTask(int task_id) {
    return this->tasks_matrix.MarkDoneTask(task_id);
}

void User::DeleteAllDone() {
    this->tasks_matrix.DeleteAllDone();
}

void User::DeleteAllTasks(){
    this->tasks_matrix.DeleteAllTasks();
}


void User::DisplayMatrix() {
    std::cout<<this->tasks_matrix;
}


/*Getters*/
std::string User::GetUsername(){
    return this->username;
}


std::string User::GetPassword(){
    return this->password;
}


std::string User::Serialize() {

    std::string result = "";
    result += "U: ";

    result += this->username;
    result += " ,";
    result += this->password;
    result += '\n';

    result += (this->tasks_matrix).Serialize();

    return result;
}


/*
Note that fields must be de-serialized in the same order they were serialized in.
*/
User User::DeSerialize(const std::string& result) {
    /*
        Note that fields must be de-serialized in the same order they were serialized in.
    */
    std::string usr;
    std::string pass;
    std::string matrix_substring;
    Matrix m;
    std::istringstream iss(result);
    char _; // To discard commas



    iss.ignore(100, ':'); // Discard "U: ", by ignoring any thing until the ':'

    iss>> usr >> _ >> pass;

    //Extracting the matrix serialization as a substring
    size_t matrix_string_start_position = result.find("M: ");
    if(matrix_string_start_position != std::string::npos) {
        matrix_substring = result.substr(matrix_string_start_position);
    } else {
        //ERROR
    }

    //Reading matrix
    m = m.DeSerialize(matrix_substring);


    User user(usr,pass);
    user.tasks_matrix = m;

    return user;
}
