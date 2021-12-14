/*
#pragma once

#include "userData.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ship : public sf::Drawable, public sf::Transformable {

public:

	explicit Ship(Game& game_);
	~Ship() {};

	void init(sf::Vector2u winsize);
	void update();

	void move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

	void speedUp(float force);
	void speedDown(float force);
	void ApplyLocalForceWithCheck(float force);

	void speedLeft(float force);
	void speedRight(float force);
	void ApplyTorqueWithCheck(float torque);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// getters
	float getLife();
	void setDamages(float damages_);
	constexpr float lifeMax() { return 100.0f; };

private:
	Game& m_game;

	sf::Sprite m_sprite;

	b2Body* m_body = nullptr;
	UserData* m_userData = new UserData(UserDataType::SHIP);

	float m_life = 100.0f;

};*/
