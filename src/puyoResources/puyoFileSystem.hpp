#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <filesystem>
#include <string>
#include <random>

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

        mt19937 gen;

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
            character_select,
            game_music1, //faeri fire!
            game_music2, //more beautiful more strong
            game_music3, // in the middle of stroll
            game_music4, // i'm the greatest ever
            game_music5, // the twin ghosts are super
            game_music6, // doens't matter who it is 
            game_music7, // let's dancing together

        };
        Sprite get_sprite(Image name);
        Font& get_font();
        sf::SoundBuffer& get_buffer(Sound name);
        fs::path& get_music(Music name);
        fs::path& get_random_music();
};