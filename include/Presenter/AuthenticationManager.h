#ifndef AUTHENTICATIONMANAGER_H_INCLUDED
#define AUTHENTICATIONMANAGER_H_INCLUDED

#include <string>
#include "FileDatabaseManager.h"


class AuthenticationManager{
    /*Private Data*/
    IAuthenticationProvider* authenticator;
    /*Private Methods*/

public:
    /*Public Data*/
    AuthenticationManager();
    virtual ~AuthenticationManager();

    /*Public Methods*/
    //Authentication
bool CheckIfUsernameExists(const std::string& usrname);
bool CheckIfLoginDataMatch(const std::string& usrname, const std::string& pass);

};

#endif // AUTHENTICATIONMANAGER_H_INCLUDED
