#pragma once

#include <SFML/Graphics.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <climits>
#include <filesystem>
#include <string>

using namespace sf;
using namespace std;

namespace fs = std::filesystem;

class puyoFileSystem
{
    private : 
        vector<Texture> textures;
        vector<Sprite> sprites;

        Font font;
        fs::path getExecutablePath();
        fs::path getImgPath(string img);

        void getAllTexture();
        void getAllSprite();
        void getFont();
        
    public :
        puyoFileSystem();
        enum{//이미지 명
            board,
            puyo,
            num,
            sega,
            opening,
            black_back
        };
        Sprite get_sprite(int name);
        Font& get_font();
};