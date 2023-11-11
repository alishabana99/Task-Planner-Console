#ifndef FILEBASEMANGER_H_INCLUDED
#define FILEBASEMANGER_H_INCLUDED

#include <string>
#include "IAuthenticationProvider.h"
#include "IUserModel.h"
#include "IAuthenticationProvider.h"

#include <fstream>
#include <sstream>

#define DATABASE_PATH ".\\DATABASE\\"
#define APP_DATA_PATH ".\\DATABASE\\NEVER_DELETE\\app_data.txt"


class FileDatabaseManager: public IUserModel, public IAuthenticationProvider {

public:
    /*UserModel Functionalities*/
    void SaveUser(std::string usrname, std::string serialized_user) override;
    void DeleteUser(std::string usrname) override;
    std::string LoadUser(const std::string& usrname)override;
    virtual std::string GetSession() override;
    virtual void UpdateSession(bool update, const std::string& usrname) override;


    /*Authentication Functionalities*/
    bool UsernameExists(const std::string& usrname) override;
    bool CheckLoginData(const std::string& usrname, const std::string& pass) override;

};

#endif // FILEBASEMANGER_H_INCLUDED
