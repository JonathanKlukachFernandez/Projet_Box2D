#include "userData.h"

UserData::UserData()
{
	m_type = UserDataType::NONE;
}

UserData::UserData(UserDataType type_) : m_type(type_)
{
	m_localId = -1;
}

UserDataType UserData::getUserDataType()
{
	return m_type;
}

void UserData::setLocalId(signed long id_)
{
	m_localId = id_;
}

signed long UserData::getLocalId()
{
	return m_localId;
}

const std::string UserData::UserDataTypeToString(UserDataType type_)
{

	switch (type_)
	{
	case UserDataType::SHIP:
		return "SHIP";
		break;
	case UserDataType::LIMIT:
		return "LIMIT";
		break;
	case UserDataType::ASTEROID:
		return "ASTEROID";
		break;
	case UserDataType::MISSILE:
		return "MISSILE";
		break;
	case UserDataType::NONE:
	default:
		return "NONE";
		break;
	}
}

