#include "puyoSounding.hpp"

#include <SFML/Audio.hpp>
#include <vector>

using namespace std;
using namespace sf;

puyoSounding::puyoSounding(){}
void puyoSounding::manage_all_sounds()
{
    for(int i = 0 ; i < sounds.size() ; )
        if(sounds[i]->getStatus() == Sound::Status::Stopped)
        {
            std::swap(sounds[i], sounds.back());
            sounds.pop_back();
        }
        else
            ++i;
}
void puyoSounding::play_sound(SoundBuffer& buffer)
{
    sounds.push_back(make_unique<Sound>(buffer));
    sounds.back()->play();
}

void puyoSounding::play_music(filesystem::path& path)
{
    music = Music(path);
    music.setLooping(true);
    music.play();
}