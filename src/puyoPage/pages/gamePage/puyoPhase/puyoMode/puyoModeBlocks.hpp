#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoTool/puyoPos.hpp"
#include <vector>
#include <random>

class puyoModeBlocks : public puyoMode
{
    private :
        std::mt19937 gen;
        static std::vector<std::pair<unsigned int,std::vector<std::vector<bool>>>> map_datas;
        void loadMapData(const std::string& filename, POSs bsize);
    public :
        puyoModeBlocks(const std::vector<puyoPlayer>& players);
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};