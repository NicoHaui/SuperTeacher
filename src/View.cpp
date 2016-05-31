#include "View.h"


View::View(void)
{
    view.reset(sf::FloatRect(0, 0, SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE));
}
View::View(sf::FloatRect init)
{
    view.reset(init);
}

void View::process(void)
{
    view.setCenter(SCREEN_X_PXSIZE / 2, SCREEN_Y_PXSIZE / 2);
}