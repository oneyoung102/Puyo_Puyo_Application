#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeGarden.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoTool/puyoCast.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;

puyoModeGarden::puyoModeGarden()
    : gen(random_device{}())
    , cycle(0)
{}

void puyoModeGarden::proceed_mode(puyoPhase& phase, puyoPlayer& player)
{
    if(seeds.empty())
    {
        uniform_int_distribution<> dist1(MIN_SEED_COUNT,MAX_SEED_COUNT);
        uniform_int_distribution<> dist2(0,1);
        const int seed_count = dist1(gen), water_position = dist2(gen);

        if(water_position == 0)
            seeds.push(Spawn::water);
        for(int i = 0 ; i < seed_count ; ++i)
        {
            uniform_int_distribution<> dist3(0,MAX_SEED_GAP);
            const int between_seed = dist3(gen);
            for(int j = 0 ; j < between_seed ; ++j)
                seeds.push(Spawn::none);
            seeds.push(Spawn::seed);
        }
        if(water_position == 1)
            seeds.push(Spawn::water);

        spawned = vector<bool>(seeds.size(),false);

        if(cycle == 0)
            cycle = SEED_CYCLE/2;
        else
            cycle += SEED_CYCLE + seeds.size() - 1;
    }
    
    auto& new_puyos = phase.get_new_puyos();
    const int idx = CASTi(new_puyos.get_end_point())-cycle;
    if(0 <= idx && idx < CASTi(spawned.size()) && !spawned[idx])
    {
        spawned[idx] = true;
        const auto what = seeds.top();
        seeds.pop();

        uniform_int_distribution<> dist1(0,1);
        const int seed_position = dist1(gen);
        auto& puyo = new_puyos.back()[seed_position];
        switch(what)
        {
            case Spawn::seed :
            {
                uniform_int_distribution<> dist2(CASTi(puyoType::Type::seed_daisy),CASTi(puyoType::Type::flower_daisy)-1);
                const int seed_type = dist2(gen);
                puyo = puyoPuyo(POSs(),make_unique<puyoFlower>(static_cast<puyoType::Type>(seed_type)));
                break;
            }
            case Spawn::water :
                puyo = puyoPuyo(POSs(),P_WATER);
                break;
            case Spawn::none :
                break;
        }
    }
}