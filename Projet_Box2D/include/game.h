#pragma once

#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/b2_world.h"
#include "bouncer.h"
#include "lifeBar.h"
#include "enemyLifeBar.h"
#include "missileManager.h"
#include "ship.h"
#include "enemyShip.h"
#include "contact_listener.h"






class Game {

public:
	static constexpr float TIME_TO_SHOOT = 1.5f;

	Game();
	void init();
	void loop();

	b2World& getWorld() { return m_world; };
	Ship& getShip() { return m_ship; };
	EnemyShip& getEnemyShip() { return m_enemyShip; };

	void setDamagesToShip(float damages_);
	void setDamagesToEnemyShip(float damages_);
	void putMissileToDeath(int idMissile_);
	void putEnemyShipToDeath(int idEnemyShip_);


private:
	float m_shootTimer;

	MyContactListener m_contact_listener_;

	bool m_debugMode;
	bool m_gameOver = false;
	bool m_youWin = false;

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;
	std::vector<Bouncer> m_windowLimits;
	MyContactListener m_contacts;


	// The game entities --------------------------------------
	Ship m_ship;
	EnemyShip m_enemyShip;
	MissileManager m_missileManager;

	// The ui entities
	LifeBar m_lifeBar = LifeBar(100.0f);
	EnemyLifeBar m_enemyLifeBar = EnemyLifeBar(100.0f);
	sf::Sprite m_gameOverTitle;
	sf::Sprite m_youWinTitle;

	sf::Clock clock;
	sf::Time collectedElapsed;

	void update();
	void draw();


};
