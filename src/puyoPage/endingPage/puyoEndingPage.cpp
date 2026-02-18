#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoEndingPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../puyoLet.hpp"

using namespace std;
using namespace sf;

puyoEndingPage::puyoEndingPage(puyoFileSystem& pfs){}
Page puyoEndingPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    return Page::none;
}