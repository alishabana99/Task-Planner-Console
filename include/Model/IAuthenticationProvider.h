#ifndef IAUTHENTICATIONPROVIDER_H_INCLUDED
#define IAUTHENTICATIONPROVIDER_H_INCLUDED

class IAuthenticationProvider {
public:
    virtual bool UsernameExists(const std::string& usrname) = 0;
    virtual bool CheckLoginData(const std::string& usrname, const std::string& pass) = 0;
};

#endif // IAUTHENTICATIONPROVIDER_H_INCLUDED
