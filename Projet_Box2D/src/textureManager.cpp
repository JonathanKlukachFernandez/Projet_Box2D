#include "textureManager.h"

TextureManager* TextureManager::textureManager_ = nullptr;

TextureManager::TextureManager()
{
    m_shipTexture.loadFromFile("./data/mainShip.png");
    m_youWinTexture.loadFromFile("./data/youWin.png");
    m_gameOverTexture.loadFromFile("./data/gameOver.png");
    m_missileTexture.loadFromFile("./data/missile.png");
    m_enemyShipTexture.loadFromFile("./data/enemyShip.png");
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
sf::Texture& TextureManager::getYouWinTexture()
{
    return m_youWinTexture;
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
