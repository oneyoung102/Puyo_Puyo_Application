#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoMenuPage.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../puyoLet.hpp"

using namespace std;
using namespace sf;

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs){}
Page puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    return Page::none;
}