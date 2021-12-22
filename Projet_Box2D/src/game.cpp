#include <random>

#include "game.h"

#include <iostream>

#include "textureManager.h"

Game::Game() :
	m_gravity(0.0f, 0.0f),
	m_world(m_gravity),
	m_ship(*this),
	m_enemyShip(*this),
	m_contacts(*this),
	m_contact_listener_(*this),
	m_missileManager(m_world),
	m_shootTimer(Game::TIME_TO_SHOOT)
{
}

void Game::init() {

	m_world.SetContactListener(&m_contact_listener_);

	TextureManager* texture_manager = TextureManager::Instance();

	m_window.create(sf::VideoMode(720, 1080), "Vertical space shooter");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	m_ship.init(m_window.getSize());
	// Set position of the ship
	m_ship.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.75f * m_window.getSize().y), sf::Vector2f(0, 0));

	m_enemyShip.init(m_window.getSize());

	m_gameOverTitle.setTexture(texture_manager->getGameOverTexture());
	m_gameOverTitle.setOrigin(0.5f * texture_manager->getGameOverTexture().getSize().x, 0.5f * texture_manager->getGameOverTexture().getSize().y);
	m_gameOverTitle.setPosition(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y);

	m_youWinTitle.setTexture(texture_manager->getGameOverTexture());
	m_youWinTitle.setOrigin(0.5f * texture_manager->getGameOverTexture().getSize().x, 0.5f * texture_manager->getGameOverTexture().getSize().y);
	m_youWinTitle.setPosition(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y);

	// Add a bouncer
	// LEFT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(0.0f, 0.0f * m_window.getSize().y),
			sf::Vector2f(0.0F, m_window.getSize().y)
		)
	);
	// RIGHT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		Bouncer(
			*this,
			sf::Vector2f(m_window.getSize().x, 0.0f * m_window.getSize().y),
			sf::Vector2f(0.0f, m_window.getSize().y)
		)
	);

	m_debugMode = false;

	// Register contacts
	m_world.SetContactListener(&m_contacts);

}

void Game::loop()
{


	while (m_window.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = m_window.getView();
				view.setSize(event.size.width, event.size.height);
				m_window.setView(view);
			}

			// Mouse events ---------------------------------------------------------------------------------
			if (event.type == sf::Event::MouseButtonReleased)
			{
			}

			// Keyboard event

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_debugMode = !m_debugMode;
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					const sf::Vector2f shipPosition(m_ship.getPosition());
					m_missileManager.AddMissile(sf::Vector2f(shipPosition.x, shipPosition.y - 50), m_ship.getRotation());
				}

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			m_ship.speedLeft(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			m_ship.speedRight(1.0f);
		}

#pragma endregion


#pragma region Physical process
		if (!m_gameOver)
			update();

#pragma endregion
		draw();

#pragma region Graphics process

#pragma endregion

	}
}

void Game::update()
{
	// Updating the world with a delay
	const float timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
	m_world.Step(timeStep, velocityIterations, positionIterations);

	// Tick every 1.0sec & enemy missile start position
	const sf::Time elapsed = clock.restart();
	collectedElapsed += elapsed;
	m_shootTimer -= elapsed.asSeconds();
	if (m_shootTimer <= 0)
	{
		m_shootTimer += TIME_TO_SHOOT;
		const auto pos = m_enemyShip.getPosition();
		this->m_missileManager.AddMissile(sf::Vector2f(pos.x, pos.y + 75), m_enemyShip.getRotation());
	}
	m_enemyShip.UpdateTimer(elapsed);

	// Update the ships
	m_ship.update();
	m_enemyShip.update();
	// Update Life bar with the life of the ship
	m_lifeBar.setLife(m_ship.getLife());
	m_lifeBar.update();
	if(m_ship.getLife() <= 0)
	{
		// Game over
		m_gameOver = true;
		EXIT_SUCCESS;
	}


	// Update Life bar with the life of the enemy ship
	m_enemyLifeBar.setEnemyLife(m_enemyShip.getEnemyLife());
	m_enemyLifeBar.update();
	if (m_enemyShip.getEnemyLife() <= 0)
	{
		// You win 
		m_youWin = true;
		EXIT_SUCCESS;
	}


	// Udpate stuff
	m_missileManager.update();
	// Update limits
	for (auto& b : m_windowLimits) {
		b.update();
	}


	if (collectedElapsed.asSeconds() > 1.0f) {

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 generator(rd()); // seed the generator
		std::uniform_int_distribution<> rndAngle(0, 360); // define the range
		const std::uniform_int_distribution<> rndX(0, m_window.getSize().x); // define the range
		const std::uniform_int_distribution<> rndY(0, m_window.getSize().y); // define the range

		sf::Vector2f rdnPos(rndX(generator), rndY(generator));

		collectedElapsed = sf::Time::Zero;

	}
}

void Game::draw()
{
	// Clear all background
	m_window.clear();

	// DRWA THINGS ----------------------------------------------------------
	// Draw the ship
	if (!m_gameOver||!m_youWin)
		m_window.draw(m_ship);

	// Draw the enemy ship
	if (!m_gameOver || !m_youWin)
		m_window.draw(m_enemyShip);

	// Draw stuff
	m_window.draw(m_missileManager);

	// Draw limits
	if (m_debugMode)
	{
		for (auto& b : m_windowLimits) {
			m_window.draw(b);
		}
	}
	// Draw the life bars
	m_window.draw(m_lifeBar);
	m_window.draw(m_enemyLifeBar);

	if (m_gameOver)
	{
		m_window.draw(m_gameOverTitle);
	}

	if (m_youWin)
	{
		m_window.draw(m_youWinTitle);
	}

	// Display all elements
	m_window.display();
}

void Game::setDamagesToShip(float damages_)
{
	m_ship.setDamages(damages_);
}

void Game::setDamagesToEnemyShip(float damages_)
{
	m_enemyShip.setDamages(damages_);
}

void Game::putMissileToDeath(int idMissile_)
{
	m_missileManager.putMissileToDeath(idMissile_);
	std::cout << "Missile " << idMissile_ << " sent to death." << std::endl;
}
