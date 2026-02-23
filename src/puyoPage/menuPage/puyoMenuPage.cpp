#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "puyoMenuPage.hpp"
#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs)
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),0,0,-1));
}
puyoPageSignal puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    signal.next_page = Page::none;
    return signal;
}