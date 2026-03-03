#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoReadyPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../puyoLet.hpp"

using namespace std;
using namespace sf;

puyoReadyPage::puyoReadyPage(puyoFileSystem& pfs){}
puyoPageSignal puyoReadyPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    return signal;
}