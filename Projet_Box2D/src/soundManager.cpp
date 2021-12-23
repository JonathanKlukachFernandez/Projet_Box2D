#include "soundManager.h"
#include <SFML/Audio.hpp>

SoundManager* SoundManager::SoundManager_ = nullptr;

SoundManager::SoundManager()
{
    if (!soundFxMissile.loadFromFile("data/sounds/missile.wav"))
    {
        std::cerr << "Error loading : " << "data/sounds/missile.wav" << std::endl;
    }
    missile.setBuffer(soundFxMissile);

    missile.setVolume(10);


    /*
        sf::Music music;
    if (!music.openFromFile("data/sounds/turboKiller.wav"))
        return;
    music.play();
    */

}

/**
 * Static methods should be defined outside the class.
 */
SoundManager* SoundManager::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (SoundManager_ == nullptr) {
        SoundManager_ = new SoundManager();
    }
    return SoundManager_;
}

void SoundManager::cleanSounds()
{
    //cleanOneVector(sounds);
}

void SoundManager::cleanOneVector(std::vector<sf::Sound> sounds_)
{
	const auto s = std::remove_if(
        sounds_.begin(),
        sounds_.end(),
        [](sf::Sound& s) {return s.getStatus() == sf::SoundSource::Stopped; });

    if (s != sounds_.end())
    {
        sounds_.erase(s, sounds_.end());
    }

}

void SoundManager::playMissile()
{
	missile.play();
}


void SoundManager::playOnce(sf::SoundBuffer& soundFx_)
{
    sf::Sound soundToAdd;
    soundToAdd.setBuffer(soundFx_);
    soundToAdd.setLoop(false);

    sounds.push_back(soundToAdd);
    sounds.back().play();

}


