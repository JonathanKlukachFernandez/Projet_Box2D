#include "missileManager.h"

#include "soundManager.h"

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
	const auto m = std::remove_if(
		m_missiles.begin(),
		m_missiles.end(),
		[](Missile& m) {return m.getIsDead(); });

	m_missiles.erase(m, m_missiles.end());

	for (auto& m : m_missiles) {
		m.update();
	}
}

void MissileManager::AddMissile(sf::Vector2f startPos, float angle)
{
	SoundManager::Instance()->playMissile();
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
	const auto m = std::find_if(
		m_missiles.begin(),
		m_missiles.end(),
		[idMissile_](Missile& m) {return m.getLocalId() == idMissile_; }
	);

	if(m != m_missiles.end())
	{
		m->setIsDead();
	}

}
