#pragma once

#include <vector>
#include <box2d/b2_world.h>
#include <SFML/Graphics/Drawable.hpp>

#include "sfmlUtilities.h"

#include "missile.h"
#include "ship.h"

class MissileManager : public sf::Drawable {

private:
	std::vector<Missile> m_missiles;
	b2World& m_world;

public:
	MissileManager(b2World& world_);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	void AddMissile(sf::Vector2f startPos, float angle);
	void putMissileToDeath(int idMissile_);

};
