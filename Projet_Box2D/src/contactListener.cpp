#include "contact_listener.h"

#include <iostream>

#include "game.h"
#include "userData.h"


MyContactListener::MyContactListener(Game& game) : game_(game)
{

}

void MyContactListener::BeginContact(b2Contact* contact)
{
    std::cout << "Contact Begin!" << std::endl;

	UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    std::cout << "A Fixture : " << UserData::UserDataTypeToString(A_Data->getUserDataType()) << ":[id=" << A_Data->getLocalId() << "]" << std::endl;
    std::cout << "B Fixture : " << UserData::UserDataTypeToString(B_Data->getUserDataType()) << ":[id=" << B_Data->getLocalId() << "]" << std::endl;

    if (A_Data->getUserDataType() == UserDataType::ENEMYSHIP ||
        B_Data->getUserDataType() == UserDataType::ENEMYSHIP ||
        A_Data->getUserDataType() == UserDataType::SHIP      ||
        B_Data->getUserDataType() == UserDataType::SHIP)
    {
    	if (B_Data->getUserDataType() == UserDataType::MISSILE || A_Data->getUserDataType() == UserDataType::MISSILE)
        {
            if (A_Data->getUserDataType() == UserDataType::ENEMYSHIP)
            {
                game_.setDamagesToEnemyShip(10);
                game_.putMissileToDeath(B_Data->getLocalId());
            }
            else if(B_Data->getUserDataType() == UserDataType::ENEMYSHIP)
            {
                game_.setDamagesToEnemyShip(10);
                game_.putMissileToDeath(A_Data->getLocalId());
            }
            else if (A_Data->getUserDataType() == UserDataType::SHIP)
            {
                game_.setDamagesToShip(10);
                game_.putMissileToDeath(B_Data->getLocalId());
            }
            else if (B_Data->getUserDataType() == UserDataType::SHIP)
            {
                game_.setDamagesToShip(10);
                game_.putMissileToDeath(A_Data->getLocalId());
            }
        }
    }

}

void MyContactListener::EndContact(b2Contact* contact)
{
    std::cout << "Contact End!" << std::endl;

    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    std::cout << "A Fixture : " << UserData::UserDataTypeToString(A_Data->getUserDataType()) << ":[id=" << A_Data->getLocalId() << "]" << std::endl;
    std::cout << "B Fixture : " << UserData::UserDataTypeToString(B_Data->getUserDataType()) << ":[id=" << B_Data->getLocalId() << "]" << std::endl;

    if (A_Data->getUserDataType() == UserDataType::ENEMYSHIP || B_Data->getUserDataType() == UserDataType::ENEMYSHIP)
    {
        if (B_Data->getUserDataType() == UserDataType::SHIP || A_Data->getUserDataType() == UserDataType::SHIP)
            game_.setDamagesToShip(100);

    }

}
