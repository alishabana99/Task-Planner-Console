#ifndef ISERIALIZABLE_H_INCLUDED
#define ISERIALIZABLE_H_INCLUDED

template <class SerializableT, class SerilizationForm>
class ISerializable {

private:


public:

    virtual SerilizationForm Serialize() = 0;

    /*
    Note that fields must be de-serialized in the same order they were serialized in.
    */
    virtual SerializableT DeSerialize(const SerilizationForm& result) = 0;

};

#endif // ISERIALIZABLE_H_INCLUDED
