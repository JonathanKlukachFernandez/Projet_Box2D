#pragma once

#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/b2_world.h"
#include "bouncer.h"
#include "lifeBar.h"
#include "missileManager.h"
#include "ship.h"
#include "enemyShip.h"

class Game {

public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return m_world; };
	Ship& getShip() { return m_ship; };
	EnemyShip& getEnemyShip() { return m_enemyShip; };

	void setDamagesToShip(float damages_);
	void setDamagesToEnemyShip(float damages_);
	//void putAsteroidToDeath(int idAsteroid_);
	void putMissileToDeath(int idMissile_);


private:

	bool m_debugMode;
	bool m_gameOver = false;

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	std::vector<Bouncer> m_windowLimits;
	


	// The game entities --------------------------------------
	Ship m_ship;
	EnemyShip m_enemyShip;
	MissileManager m_missileManager;

	// The ui entities
	LifeBar m_lifeBar = LifeBar(100.0f);
	sf::Sprite m_gameOverTitle;

	sf::Clock clock;
	sf::Time collectedElapsed;

	void update();
	void draw();


};
