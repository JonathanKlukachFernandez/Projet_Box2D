#pragma once
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_fixture.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "sfmlUtilities.h"
#include "textureManager.h"
#include "userData.h"

class Missile : public sf::Drawable, public sf::Transformable
{
public:
	Missile(b2World& world_, const sf::Vector2f startPos_, const float angle_);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void setIsDead();
	bool getIsDead();

	long getLocalId();

private:
	sf::Sprite	m_sprite;

	b2Body* m_body = nullptr;
	UserData* m_userData = new UserData(UserDataType::MISSILE);

	bool m_isDead = false;

	static long m_localIdMissile;
	static long getGlobalId();

};
