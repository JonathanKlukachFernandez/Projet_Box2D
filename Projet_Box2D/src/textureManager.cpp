#include "textureManager.h"

TextureManager* TextureManager::textureManager_ = nullptr;

TextureManager::TextureManager()
{
    m_shipTexture.loadFromFile("./data/modular_ships_2.png");
    //m_youWinTexture.loadFromFile("./data/GameOver.png");
    m_gameOverTexture.loadFromFile("./data/GameOver.png");
    m_missileTexture.loadFromFile("./data/missile.png");
    m_enemyShipTexture.loadFromFile("./data/Ship.png");
}


/**
 * Static methods should be defined outside the class.
 */
TextureManager* TextureManager::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (textureManager_ == nullptr) {
        textureManager_ = new TextureManager();
    }
    return textureManager_;
}

sf::Texture& TextureManager::getShipTexture()
{
    return m_shipTexture;
}
sf::Texture& TextureManager::getGameOverTexture()
{
    return m_gameOverTexture;
}
sf::Texture& TextureManager::getMissileTexture()
{
    return m_missileTexture;
}

sf::Texture& TextureManager::getEnemyShipTexture()
{
    return m_enemyShipTexture;
}
