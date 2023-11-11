#ifndef IUSERMODEL_H_INCLUDED
#define IUSERMODEL_H_INCLUDED

#include <string>

class IUserModel {
public:
    virtual void SaveUser(std::string usrname, std::string serialized_user) = 0;
    virtual void DeleteUser(std::string usrname) = 0;
    virtual std::string LoadUser(const std::string& usrname) = 0;
    virtual std::string GetSession() = 0;
    virtual void UpdateSession(bool update, const std::string& usrname) = 0;

};


#endif // IUSERMODEL_H_INCLUDED
