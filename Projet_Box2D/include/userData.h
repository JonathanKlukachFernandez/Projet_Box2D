#pragma once

#include <string>

enum class UserDataType : char
{
    NONE,
    SHIP = 's',
    LIMIT = 'l',
    ASTEROID = 'a',
    MISSILE = 'n',
    ENEMYSHIP = 'e',

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
