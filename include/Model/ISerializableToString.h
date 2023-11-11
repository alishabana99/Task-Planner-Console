#ifndef ISERIALIZABLETOSTRING_H_INCLUDED
#define ISERIALIZABLETOSTRING_H_INCLUDED

#include "ISerializable.h"
#include <string>

template <class T>
class ISerializableToString: public ISerializable<T, std::string> {

public:
    virtual std::string Serialize() = 0;


    /*
    Note that fields must be de-serialized in the same order they were serialized in.
    */
    virtual T DeSerialize(const std::string& result) = 0;
};

#endif // ISERIALIZABLETOSTRING_H_INCLUDED
