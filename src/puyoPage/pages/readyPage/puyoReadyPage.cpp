#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoReadyPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoPage/puyoLet.hpp"

using namespace std;
using namespace sf;

puyoReadyPage::puyoReadyPage(puyoFileSystem& pfs){}
puyoPageSignal puyoReadyPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    return signal;
}