#include "missileManager.h"

MissileManager::MissileManager(b2World& world_) : m_world(world_)
{
}

void MissileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : m_missiles) {
		target.draw(m, states);
	}
}

void MissileManager::update()
{
	auto m = std::remove_if(
		m_missiles.begin(),
		m_missiles.end(),
		[](Missile& m) {return m.getIsDead(); });

	m_missiles.erase(m, m_missiles.end());

	for (auto& m : m_missiles) {
		m.update();
	}
}

void MissileManager::AddMissile(Ship& ship_)
{

	sf::Vector2f startPos = ship_.getPosition();
	float angle = ship_.getRotation();

	m_missiles.emplace_back(
		Missile(
			m_world,
			startPos,
			angle)
	);
}

void MissileManager::putMissileToDeath(int idMissile_)
{
	// Check id, then put isDead to true
	auto m = std::find_if(
		m_missiles.begin(),
		m_missiles.end(),
		[idMissile_](Missile& m) {return m.getLocalId() == idMissile_; }
	);

	if(m != m_missiles.end())
	{
		m->setIsDead();
	}

}
