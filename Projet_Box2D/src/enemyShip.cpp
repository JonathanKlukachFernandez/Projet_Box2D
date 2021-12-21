#include "game.h"
#include "enemyShip.h"

#include "SFML_Utilities.h"
#include <iostream>

#include "textureManager.h"
#include "userData.h"

EnemyShip::EnemyShip(Game& game_) : m_game(game_)
{
}
float EnemyShip::getEnemyLife() {
    return m_enemyLife;
}

void EnemyShip::setDamages(float damages_)
{
    m_enemyLife -= damages_;
}


void EnemyShip::init(sf::Vector2u winsize) {

    // Defining the shape
    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getEnemyShipTexture());
    m_sprite.setOrigin(texManager->getEnemyShipTexture().getSize().x * 0.5f, texManager->getEnemyShipTexture().getSize().y * 0.5f);

    // Defining the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = pixelsToMeters(winsize);
    bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 4.0f);
    bodyDef.angularDamping = 0.75f;
    bodyDef.linearDamping = 0.75f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
    // Defining body angle
    bodyDef.angle = degToRad(180); // the body's angle in radians.


    m_body = this->m_game.getWorld().CreateBody(&bodyDef);
    //m_body->SetUserData(reinterpret_cast<void*>(&m_userData));

    // Shape of the physical (A box)
    b2PolygonShape hitBox;
    hitBox.SetAsBox(
        0.5f * pixelsToMeters(texManager->getEnemyShipTexture().getSize().x),
        0.5f * pixelsToMeters(texManager->getEnemyShipTexture().getSize().y)
    );

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userData);
    m_body->CreateFixture(&playerFixtureDef);

}

void EnemyShip::update() {

    // Set speed -------------------------------------------------------------------
    //body->SetLinearVelocity(linVelocity);

    // Get the position of the body
    b2Vec2 bodyPos = m_body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = m_body->GetAngle();
    setRotation(radToDeg(-1.0f * angle));

}

void EnemyShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void EnemyShip::move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity) {

    b2Vec2 pos = pixelsToMeters(_pixelsPosition);
    b2Vec2 vel = pixelsToMeters(_velocity);

    m_body->SetTransform(pos, 0.0f);

}

/*void EnemyShip::speedUp(float forceValue) {
    ApplyLocalForceWithCheck(1.0f * forceValue);
}

void EnemyShip::speedDown(float forceValue) {
    ApplyLocalForceWithCheck(-1.0f * forceValue);
}

void EnemyShip::ApplyLocalForceWithCheck(float forceValue) {

    b2Vec2 force(0.0, forceValue);
    b2Vec2 localForce = m_body->GetLocalVector(force);

    if (b2Abs(m_body->GetLinearVelocity().Length()) < 5.0f) {
        m_body->ApplyForceToCenter(localForce, true);

        if (b2Abs(m_body->GetLinearVelocity().Length()) < epsilon) {
            m_body->SetLinearVelocity(b2Vec2_zero);
        }
    }

}
void EnemyShip::speedLeft(float forceValue) {
    ApplyTorqueWithCheck(-1.0f * forceValue);
}

void EnemyShip::speedRight(float forceValue) {
    ApplyTorqueWithCheck(1.0f * forceValue);
}

void EnemyShip::ApplyTorqueWithCheck(float torque) {

    if (b2Abs(m_body->GetAngularVelocity()) < 0.5f) {

        m_body->ApplyTorque(torque, true);

        if (b2Abs(m_body->GetAngularVelocity()) < epsilon) {
            m_body->SetAngularVelocity(0.0f);
        }

    }*/


