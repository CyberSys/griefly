#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Audio.hpp>

#include "core/Constheader.h"

#ifdef PlaySound
#undef PlaySound
#endif // PlaySound

class SoundManager
{
public:
    void InitSound(sf::Sound* sound, const std::string& name);
    void LoadSound(const std::string& name);
private:
    const sf::SoundBuffer* GetBuffer(const std::string& name);
    std::unordered_map<std::string, sf::SoundBuffer*> holder_;
};

SoundManager& GetSoundManager();

class SoundPlayer
{
public:
    SoundPlayer();
    sf::Sound* PlaySound(const std::string& name);
    void PlayMusic(const std::string& name, float volume = 100.0f);
    void StopMusic();
private:
    sf::Music music_;
    std::vector<sf::Sound> sounds_;
};

SoundPlayer& GetSoundPlayer();
