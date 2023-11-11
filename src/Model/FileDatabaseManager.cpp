#include "FileDatabaseManager.h"





/*UserModel Functionalities*/

/*Saving user's serialized data to the text file*/
void FileDatabaseManager::SaveUser(std::string usrname, std::string serialized_user) {

    //1. Building up the file path
    std::string file_path = DATABASE_PATH;
    file_path += usrname;
    file_path += ".txt";

    //2. opening the file 
    std::ofstream output_file(file_path);

    //3. writing to the file
    output_file << serialized_user;
}


//Deleting the user by removing its file 
void FileDatabaseManager::DeleteUser(std::string usrname) {
    //1. building up file path
    std::string file_path = DATABASE_PATH;
    file_path += usrname;
    file_path += ".txt";

    //2. deleting file 
    std::remove(file_path.c_str());
}


/*Loading user's serialized data from the text file*/
std::string FileDatabaseManager::LoadUser(const std::string& usrname) {

    std::string line;
    std::string result;

    //1. building up file path
    std::string file_path = DATABASE_PATH;
    file_path += usrname;
    file_path += ".txt";

    //2. openning the file for reading 
    std::ifstream input_file(file_path);
    if (!input_file.good())
        return "";

    //3. reading the file line by line
    while(getline(input_file,line)) {
        result += line;
        result += '\n';
    }
    input_file.close();
    
    //4. updating app_data.txt to handle an opened session
    this->UpdateSession(1, usrname);

    return result;

}


/*Getting the current session*/
std::string FileDatabaseManager::GetSession() {
    //1. openning app_data file for reading
    std::ifstream input_file(APP_DATA_PATH);
    std::string session;

    //2.reading the first line in the file (enough) 
    getline(input_file, session);


    return session;

}


/*Updating sessions state either by setting the session owener's username (openning session)  OR deleting it (closing session)*/
void FileDatabaseManager::UpdateSession(bool update, const std::string& usrname) {
    
    //1. openning app_data file for writing
    std::ofstream output_file(APP_DATA_PATH);

    if (update)
    {
        //2.saving that this user has logged in, to be well-handled in the next startup, if he don't logout
        output_file << usrname;
    }
    else {

        //2. deleting user session
        //no user is logged in
        output_file.clear();

    }

    output_file.close();
}

/*Authentication Functionalities*/
/*Checking if the username exists in the database*/
bool FileDatabaseManager::UsernameExists(const std::string& usrname) {
    //1. building up the file path
    std::string file_path = DATABASE_PATH;
    file_path += usrname;
    file_path += ".txt";

    //2. openning the file for reading
    std::ifstream file(file_path);
    //3. if the file is good -> it already exists -> username exists 
    return file.good();

}

/*Checking matching credentials*/
bool FileDatabaseManager::CheckLoginData(const std::string& usrname, const std::string& pass) {

    std::string line;
    std::string loaded_username;
    std::string loaded_password;
    char _;  //comma placeholder

    //1. building up the file path
    std::string file_path = DATABASE_PATH;
    file_path += usrname;
    file_path += ".txt";

   //2. openning file for reading 
    std::ifstream input_file(file_path);
    if(!input_file.good())
        return false;

    //3. reading the file's 1st line
    getline(input_file,line);
    std::istringstream iss(line);
    iss.ignore(10,':'); //ignoring any thing untill the ':' included.
    iss >> loaded_username >> _ >> loaded_password;

    //4. checking matching username
    if (loaded_username != usrname) {
        return false;
    }
    
    //5. checking matching password
    if (loaded_password != pass) {
        return false;
    }

    return true;
}
