
#include <iostream>

#include "bouncer.h"
#include "game.h"
#include "SFML_Utilities.h"

Bouncer::Bouncer(Game& game_, sf::Vector2f pos_ ,sf::Vector2f size_) : game(game_)
{
    init(pos_, size_);
}

void Bouncer::init(sf::Vector2f pos_, sf::Vector2f size_) {

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    bodyDef.position.Set(pixelsToMeters(pos_).x, pixelsToMeters(pos_).y);
    bodyDef.angle = 0.0f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    m_body = this->game.getWorld().CreateBody(&bodyDef);
    //m_body->SetUserData(reinterpret_cast<void*>(&m_userData));

    //set this Ball object in the body's user data

    // Shape of the physical (A box)
    b2PolygonShape bouncerBox;
    //bouncerBox.SetAsBox(physicalSize.x, physicalSize.y);
    bouncerBox.SetAsBox(
        pixelsToMeters(size_.x),
        pixelsToMeters(size_.y),
        b2Vec2_zero,
        degToRad(.0f));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &bouncerBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.2f;
    playerFixtureDef.restitution = 0.01f; // Make it bounce a little bit

    m_body->CreateFixture(&playerFixtureDef);

    // Defining the shape
    m_shape.setSize(size_);
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOrigin(0.5f * size_.x, 0.5f * size_.y);

}

void Bouncer::update() {

    const auto& b2Position = m_body->GetPosition();
    m_shape.setPosition(metersToPixels(b2Position));
    const auto b2rotation = m_body->GetAngle();
    m_shape.setRotation(-1.0f * radToDeg(b2rotation));
    
}

void Bouncer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_shape, states);
}

