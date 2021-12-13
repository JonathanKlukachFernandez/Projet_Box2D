#pragma once

#include <string>

enum UserDataType : char
{
    SHIP = 's',
    LIMIT = 'l',
    ASTEROID = 'a',
    MISSILE = 'n',
    NONE

};

class UserData
{
public:
    UserData();
    UserData(UserDataType type_);

    static const std::string UserDataTypeToString(UserDataType type_);

    UserDataType getUserDataType();
    signed long getLocalId();
    void setLocalId(signed long id_);

private:
    UserDataType m_type;
    signed long m_localId;

};
