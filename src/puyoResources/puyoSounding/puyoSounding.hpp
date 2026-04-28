#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

class puyoSounding
{
    private :
        sf::Music music;
        std::vector<std::unique_ptr<sf::Sound>> sounds;
    public :
        puyoSounding();
        void manage_all_sounds();
        void play_sound(sf::SoundBuffer& buffer);
        void play_music(const std::filesystem::path& path);
        bool sounds_empty();
};