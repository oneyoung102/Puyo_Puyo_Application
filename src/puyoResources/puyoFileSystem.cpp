#include <SFML/Graphics.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <climits>
#include <filesystem>
#include <string>

#include "puyoFileSystem.hpp"

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
fs::path puyoFileSystem::getImgPath(string img)// 사용 안 함
{
    return getExecutablePath().parent_path().parent_path() / ("Resources/assets/"+img);
}

void puyoFileSystem::getAllTexture()
{
    const fs::path assetsPath = getExecutablePath().parent_path().parent_path() / "Resources/assets";
    for (const auto& entry : fs::directory_iterator(assetsPath))
        if (entry.path().extension() == ".png")
        {
            string filename = entry.path().string();
            Texture texture;
            if (!texture.loadFromFile(filename))
                throw std::runtime_error("Unable to load image from file"); // 로드 실패 시 종료
            textures.push_back(texture);
        }
}
void puyoFileSystem::getAllSprite()
{
    for(const auto& texture : textures)
        sprites.push_back(Sprite(texture));
}


puyoFileSystem::puyoFileSystem()
{
    getAllTexture();//모든 이미지 불러오기
    getAllSprite();
}
Sprite puyoFileSystem::get_sprite(int name){return sprites[name];}
