#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBlocks.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoResources/puyoFileSystem.hpp"

#include <stdexcept>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

std::vector<std::pair<unsigned int, std::vector<std::vector<bool>>>> puyoModeBlocks::map_datas;

void puyoModeBlocks::loadMapData(const string& filename, POSs bsize)
{
    if(!map_datas.empty())
        throw runtime_error("MapData was already loaded");

    ifstream ifs(filename);
    if(!ifs.is_open())
        throw runtime_error(filename+" doesn't exist");
    size_t count;
    ifs >> count;

    unsigned int weight_sum = 0;
    decltype(map_datas) temp_map_datas;
    for(size_t i = 0 ; i < count ; ++i)
    {
        unsigned int weight;
        ifs >> weight;
        vector<vector<bool>> map_data;
        for(size_t j = 0 ; j < bsize.r ; ++j)
        {
            map_data.push_back(vector<bool>());  
            for(size_t k = 0 ; k < bsize.c ; ++k)
            {
                int element;
                ifs >> element;
                if(element != 0 and element != 1)
                    throw runtime_error("the element of MapData is neither 0 or 1");
                map_data.back().push_back(static_cast<bool>(element));
            }
            if(map_data.back().size() != bsize.c)
                throw runtime_error("the size of MapData is not correct");    
        }
        if(map_data.size() != bsize.r)
            throw runtime_error("the size of MapData is not correct");
        temp_map_datas.push_back(make_pair(weight+weight_sum,std::move(map_data)));
        weight_sum += weight;
    }
    ifs.close();
    map_datas = std::move(temp_map_datas);
}
puyoModeBlocks::puyoModeBlocks(const std::vector<puyoPlayer>& players)
    : gen(random_device()())
{
    if(map_datas.empty())
        loadMapData(puyoFileSystem::getFolderPath("Data")/"puyoBlocksModeMapData.txt", players.front().refer_board().get_size());
    if(map_datas.empty())
        throw runtime_error("After loading, MapData is empty.");

    uniform_int_distribution<> dist(0,map_datas.back().first);
    const int randint = dist(gen);
    const size_t map_data_idx = distance(map_datas.begin(),lower_bound(map_datas.begin(), map_datas.end(), randint,
    [](const auto& element, unsigned int value) {
            return element.first < value;
        }));

    for(const auto& player : players)
    {
        auto& board = player.refer_board();
        const auto& map_data = map_datas[map_data_idx].second;
        for(size_t r = 0 ; r < map_data.size() ; ++r)
            for(size_t c = 0 ; c < map_data[0].size() ; ++c)
                if(map_data[r][c])
                    board.insert(puyoPuyo(POSi(c,r),P_WALL));
    }
}
void puyoModeBlocks::proceed_mode(puyoPhase& phase, puyoPlayer& player){}