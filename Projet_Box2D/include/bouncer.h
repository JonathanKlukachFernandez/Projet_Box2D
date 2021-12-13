#pragma once

#include "userData.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Bouncer : public sf::Drawable, public sf::Transformable
{
public:
	explicit Bouncer(Game& game_, sf::Vector2f pos, sf::Vector2f size);

	void init(sf::Vector2f, sf::Vector2f);
	void update();

	b2Body* getBody(){ return m_body; };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// Root game
	Game& game;

	// Graphic object
	sf::RectangleShape m_shape;
	UserData* m_userData = new UserData(UserDataType::LIMIT);

	// The box 2D object
	b2Body* m_body = nullptr;

};
