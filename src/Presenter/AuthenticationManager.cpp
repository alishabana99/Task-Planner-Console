#include "AuthenticationManager.h"


AuthenticationManager::AuthenticationManager() {
    this->authenticator = new FileDatabaseManager();
}

AuthenticationManager::~AuthenticationManager() {
    delete(this->authenticator);
}

bool AuthenticationManager::CheckIfUsernameExists(const std::string& usrname){

    return (this->authenticator->UsernameExists(usrname));

}

bool AuthenticationManager::CheckIfLoginDataMatch(const std::string& usrname, const std::string& pass){

    return this->authenticator->CheckLoginData(usrname,pass);

}
