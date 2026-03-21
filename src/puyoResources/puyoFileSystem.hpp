#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <filesystem>
#include <string>
#include <random>


class puyoFileSystem
{
    private : 
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite> sprites;
        std::vector<sf::SoundBuffer> buffers;
        std::vector<std::filesystem::path> musics;

        std::mt19937 gen;

        sf::Font font;
        std::filesystem::path getExecutablePath();
        std::filesystem::path getResourcesPath(std::string resource);

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
            basic_back,
            button,
            easy_button,//난이도
            normal_button,
            hard_button,
            basic_button,//모드
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
            all_clear,
            ready,
            start,
            victory,
            lose,
            select,
            cancel,
            cursor
        };
        enum class Music{//음악 명
            opening_page = 0,
            menu_page,
            option_page,
            game_music1, //faeri fire!
            game_music2, //more beautiful more strong
            game_music3, // in the middle of stroll
            game_music4, // i'm the greatest ever
            game_music5, // the twin ghosts are super
            game_music6, // doens't matter who it is 
            game_music7, // let's dancing together
            game_music8, // Chearful Puyo
            game_music9, // Rising Comet!
            game_music10, // FEVER! FEVER! FEVER!
            game_music11, // Combat Queen Rulue-sama

            victory,//99번

        };
        sf::Sprite get_sprite(Image name);
        sf::Font& get_font();
        sf::SoundBuffer& get_buffer(Sound name);
        std::filesystem::path& get_music(Music name);
        std::filesystem::path& get_random_music();
};