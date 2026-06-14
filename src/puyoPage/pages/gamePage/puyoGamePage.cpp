#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoGamePage.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreenhead.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreenbar.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintVanishPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintGravityPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintFuturePuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintBoard.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintSpawnspot.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintNextPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScore.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintObstructViewer.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintEnergyPuyo.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintText.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoPage/puyoKeyBoard/puyoLet.hpp"
#include "puyoTool/puyoCast.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoGameConstant;
using namespace puyoImageConstant;

void puyoGamePage::let_skip(){skip = true;}

puyoGamePage::puyoGamePage(puyoFileSystem& pfs, Arcade arcade, Diff diff, Mode mode) 
    : PUYO_SPRITE(pfs.get_sprite(puyoFileSystem::Image::puyo))
    , NUM_SPRITE(pfs.get_sprite(puyoFileSystem::Image::num))
    , BOARD_SPRITE(pfs.get_sprite(puyoFileSystem::Image::board))
    , NOTICE_SPRITE(pfs.get_sprite(puyoFileSystem::Image::notice))
    , COUNT_DOWN_BACK_SPRITE(pfs.get_sprite(puyoFileSystem::Image::black_back))
    , skip(false)
    , status(Status::init)
{

////////Arcade
    // auto bot = make_unique<puyoPlayer>(0, make_unique<puyoBoard>(),true,1,NORMAL_BOT_INIT_ACT_TICK);
    // phase.add_player(std::move(bot));
    phase.add_player(puyoPlayer(0, make_unique<puyoBoard>()));
    const auto& player0 = phase.get_players().back();
    pl.allot_key(Keyboard::Key::A,player0.get_let_left());
    pl.allot_key(Keyboard::Key::S,player0.get_let_down());
    pl.allot_key(Keyboard::Key::D,player0.get_let_right());
    pl.allot_key(Keyboard::Key::W,player0.get_let_turn());
    pl.allot_key(Keyboard::Key::LShift,player0.get_let_drop());
    switch(arcade)
    {   
        case Arcade::duel :
        {
            phase.add_player(puyoPlayer(1, make_unique<puyoBoard>()));
            const auto& player1 = phase.get_players().back();
            pl.allot_key(Keyboard::Key::Left,player1.get_let_left());
            pl.allot_key(Keyboard::Key::Down,player1.get_let_down());
            pl.allot_key(Keyboard::Key::Right,player1.get_let_right());
            pl.allot_key(Keyboard::Key::Up,player1.get_let_turn());
            pl.allot_key(Keyboard::Key::RShift,player1.get_let_drop());
            
            break;
        }
        case Arcade::bot :
        {
            unsigned int init_act_tick = 0;
            switch(diff)
            {
                case Diff::easy : 
                    init_act_tick = EASY_BOT_INIT_ACT_TICK;
                    break;
                case Diff::normal :
                    init_act_tick = NORMAL_BOT_INIT_ACT_TICK;
                    break;
                case Diff::hard :
                    init_act_tick = HARD_BOT_INIT_ACT_TICK;
                    break;
                default : 
                    break;
            }
            phase.add_player(puyoPlayer(1, make_unique<puyoBoard>(),true,2,init_act_tick));
            break;
        }
        default :
            break;
    };
    phase.set_game(diff,mode);

////////////////////////////////////////////////출력 객체
    pp.add_print_object(make_unique<puyoPrintScreen>(phase.get_player_count(),BOARD_SPRITE));
    for(const auto& player : phase.get_players())
    {
        auto& board = player.get_board();
        const int player_num = player.get_player_num();
        const POSf board_print_pos = PLAYER_BOARD_POS[player_num]+POSf(0,PUYO_SIZE*(BOARD_HEIGHT - board.get_size().y));

        pp.add_print_object(make_unique<puyoPrintSpawnspot>(player_num,PUYO_SPRITE,board.get_spawn_pos()));
        pp.add_print_object(make_unique<puyoPrintBoard>(board,PUYO_SPRITE,board_print_pos));
        pp.add_print_object(make_unique<puyoPrintFuturePuyo>(player.controll_future().get(),PUYO_SPRITE,board_print_pos));
        pp.add_print_object(make_unique<puyoPrintVanishPuyo>(player.controll_vanish().get(),PUYO_SPRITE,board_print_pos));
        pp.add_print_object(make_unique<puyoPrintGravityPuyo>(player.controll_gravity().get(),PUYO_SPRITE,board_print_pos));
        pp.add_print_object(make_unique<puyoPrintEnergyPuyo>(player.controll_energy().get(),PUYO_SPRITE));
        pp.add_print_object(make_unique<puyoPrintPlayPuyo>(player,PUYO_SPRITE,board_print_pos));

        pp.add_print_object(make_unique<puyoPrintNextPuyo>(player_num,player.get_new_puyo_count(),phase.get_new_types(),PUYO_SPRITE,NEXT_PUYO_VIEWER_POS[player_num]));
        pp.add_print_object(make_unique<puyoPrintScore>(player_num,player.get_score(),NUM_SPRITE,SCORE_POS[player_num]));
    }
    pp.add_print_object(make_unique<puyoPrintScreenhead>(BOARD_SPRITE));
    pp.add_print_object(make_unique<puyoPrintScreenbar>(phase.get_player_count(),BOARD_SPRITE));
    for(const auto& player : phase.get_players())
    {
        const int player_num = player.get_player_num();
        pp.add_print_object(make_unique<puyoPrintObstructViewer>(player.controll_obstuct().get(),PUYO_SPRITE,OBSTRUCT_VIEWER_POS[player_num]));
    }
/////////////////////////////////////////////////신호 수신기 함수 매칭
    //보드
    boardSignalReceiver.add_execute(puyoBoardSignal::chain, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        const int player_num = player.get_player_num(), chain_count = player.controll_score().get_chain_count();
        pp.add_print_text(make_unique<puyoPrintText>(TEXT_CHAIN_POS[player_num],to_string(chain_count)+" chain",pfs.get_font(),TEXT_CHAIN_SIZE,Color::Red,Text::Style::Bold,TEXT_CHAIN_TICK));
        
        const int sound_number = min(CASTi(puyoFileSystem::Sound::chain1)+chain_count-1,CASTi(puyoFileSystem::Sound::chain7high));
        ps.play_sound(pfs.get_buffer((puyoFileSystem::Sound)sound_number));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::all_cleared, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        const int player_num = player.get_player_num();
        pp.add_print_text(make_unique<puyoPrintText>(TEXT_ALL_CLEAR_POS[player_num],"All Clear!",pfs.get_font(),TEXT_ALL_CLEAR_SIZE,Color::Red,Text::Style::Bold,TEXT_ALL_CLEAR_TICK));
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::all_clear));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::many_obsp_dropped, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::many_obsp_dropped));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::mid_obsp_dropped, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::mid_obsp_dropped));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::less_obsp_dropped, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::less_obsp_dropped));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::unfreeze, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::unfreeze));
    });
    boardSignalReceiver.add_execute(puyoBoardSignal::vanished, [this](puyoFileSystem& pfs, const puyoPlayer& player){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_vanished));
    });
    //플레이뿌요
    puyoSignalReceiver.add_execute(puyoPlayPuyoSignal::puyo_move, [this](puyoFileSystem& pfs){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_move));
    });
    //플레이어
    playerSignalReceiver.add_execute(puyoPlayerSignal::puyo_dropped, [this](puyoFileSystem& pfs){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_dropped));
    });
    //모드
    modeSignalReceiver.add_execute(puyoModeSignal::speed_up, [this](puyoFileSystem& pfs){
        pp.add_print_text(make_unique<puyoPrintText>(TEXT_SPEED_UP_POS,"Speed Up!!!",pfs.get_font(),TEXT_SPEED_UP_SIZE,Color::Yellow,Text::Style::Bold,TEXT_SPEED_UP_TICK));
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::speed_up));
    });
    modeSignalReceiver.add_execute(puyoModeSignal::bomb_fused, [this](puyoFileSystem& pfs){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::bomb_fused));
    });
    modeSignalReceiver.add_execute(puyoModeSignal::bomb_explode, [this](puyoFileSystem& pfs){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::bomb_explode));
    });
    modeSignalReceiver.add_execute(puyoModeSignal::freeze, [this](puyoFileSystem& pfs){
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::freeze));
    });
}

void puyoGamePage::receive_signals(puyoFileSystem& pfs)
{

    for(auto& player : phase.get_players())
    {
        boardSignalReceiver.execute(player.get_board(),pfs,player);
        puyoSignalReceiver.execute(player.get_puyo(),pfs);
        playerSignalReceiver.execute(player,pfs);
    }
    modeSignalReceiver.execute(phase,pfs);
}

puyoPageSignal puyoGamePage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    switch(status)
    {
        case Status::init :
            pp.add_print_object(make_unique<puyoPrintScreen>(phase.get_player_count(),NOTICE_SPRITE,NOTICE_TICK));
            status = Status::notice;
            pl.allot_key(sf::Keyboard::Key::Enter,FUNCFY(let_skip));
            break;
        case Status::notice :
            if(!pp.object_back_alive() || skip)
            {
                if(skip && pp.object_back_alive())
                    pp.clear_object_back();
                pp.add_print_object(make_unique<puyoPrintObject>(COUNT_DOWN_BACK_SPRITE,BLACK_BACK_TICK)); //검은색 반투명 배경
                pp.add_print_text(make_unique<puyoPrintText>(SCREEN_CENTER,"Ready?",pfs.get_font(),TEXT_READY_SIZE,Color::White,Text::Style::Bold,TEXT_READY_TICK));
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::ready));
                status = Status::ready;
                skip = false;
                pl.clear(sf::Keyboard::Key::Enter);
            }
            break;
        case Status::ready :
            if(!pp.text_back_alive())
            {
                pp.add_print_text(make_unique<puyoPrintText>(SCREEN_CENTER,"Start!",pfs.get_font(),60,Color::White,Text::Style::Bold,TEXT_START_TICK));
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::start));
                ps.play_music(pfs.get_random_music());
                status = Status::start;
            }
            break;
        case Status::start :   
            if(!pp.text_back_alive())
                status = Status::play;
            break;
        case Status::play :
//////////////게임 진행
            receive_signals(pfs);
            phase.proceed_game();
            convert_page = phase.game_ended();
            break;
    };
    if(convert_page)
    {
        signal.win_player_num = phase.get_win_player_num();
        signal.request_capture = true;
        signal.next_page = Page::ending;
    }
    return signal;
}