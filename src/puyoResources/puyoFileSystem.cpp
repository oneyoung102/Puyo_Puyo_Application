#include <SFML/Graphics.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>

#include "puyoFileSystem.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace sf;
using namespace std;
namespace fs = std::filesystem;

fs::path puyoFileSystem::getExecutablePath() 
{
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
        throw runtime_error("Unable to get executable path");
    return fs::canonical(path);
}
fs::path puyoFileSystem::getFolderPath(const string& folder)
{
    return getExecutablePath().parent_path().parent_path() / folder;
}

void puyoFileSystem::getAllTexture()
{
    const fs::path imgPath = getFolderPath("Resources/assets")/"img";
    vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(imgPath))
        if (entry.path().extension() == ".png")
            files.push_back(entry.path());
    sort(files.begin(), files.end());
    for (const auto& path : files)
    {
        Texture texture;
        if (!texture.loadFromFile(path.string()))
            throw runtime_error("Unable to load image");
        textures.push_back(texture);
    }
}
void puyoFileSystem::getAllSprite()
{
    for(const auto& texture : textures)
        sprites.push_back(Sprite(texture));
}

void puyoFileSystem::getFont()
{
    const fs::path fontPath = getFolderPath("Resources/assets")/"font/puyo_font.ttf";
    if (!font.openFromFile(fontPath.string()))
        throw runtime_error("Unable to load image");
}

void puyoFileSystem::getAllSound()
{
    const fs::path soundPath = getFolderPath("Resources/assets")/"sound";
    vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(soundPath))
        if (entry.path().extension() == ".mp3")
            files.push_back(entry.path());
    sort(files.begin(), files.end());
    for (const auto& path : files)
    {
        SoundBuffer buffer;
        if (!buffer.loadFromFile(path.string()))
            throw runtime_error("Unable to load sound");
        buffers.push_back(buffer);
    }
}

void puyoFileSystem::getAllMusicPath()
{
    const fs::path soundPath = getFolderPath("Resources/assets")/"music";
    for (const auto& entry : fs::directory_iterator(soundPath))
        if (entry.path().extension() == ".mp3")
            musics.push_back(entry.path());
    sort(musics.begin(), musics.end());
}

puyoFileSystem::puyoFileSystem() : gen(random_device{}())
{
    getAllTexture();//모든 이미지 불러오기
    getAllSprite();
    getFont();
    getAllSound();
    getAllMusicPath();
}
Sprite puyoFileSystem::get_sprite(puyoFileSystem::Image name) const {return sprites[CASTs(name)];}
const Font& puyoFileSystem::get_font() const {return font;}
sf::SoundBuffer& puyoFileSystem::get_buffer(puyoFileSystem::Sound name){return buffers[CASTs(name)];}
const fs::path& puyoFileSystem::get_music(puyoFileSystem::Music name) const {return musics[CASTs(name)];}
const fs::path& puyoFileSystem::get_random_music()
{
    uniform_int_distribution<> dist(CASTi(Music::game_music1), CASTi(Music::game_music11));
    return musics[dist(gen)];
}
