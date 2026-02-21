#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        vector<sf::SoundBuffer> buffers;
        vector<fs::path> musics;

        Font font;
        fs::path getExecutablePath();
        fs::path getResourcesPath(string resource);

        void getAllTexture();
        void getAllSprite();
        void getFont();
        void getAllSound();
        void getAllMusicPath();
        
    public :
        puyoFileSystem();
        enum class Image{//이미지 명
            board = 0,
            puyo,
            num,
            sega,
            opening,
            black_back,
            basic_back
        };
        enum class Sound{//사운드 명
            sega_intro = 0,
            puyo_move,
            less_obsp_dropped,//적은 양 방해 뿌요 드롭
            mid_obsp_dropped,//방해 뿌요 드롭
            many_obsp_dropped,//많은 방해 뿌요 드롭
            puyo_dropped,
            puyo_vanished,
            chain1,
            chain2,
            chain3,
            chain4,
            chain5,
            chain6,
            chain7high,
            victory 
        };
        enum class Music{//음악 명
            main_menu = 0,
            game_playing
        };
        Sprite get_sprite(Image name);
        Font& get_font();
        sf::SoundBuffer& get_buffer(Sound name);
        fs::path& get_music(Music name);
};