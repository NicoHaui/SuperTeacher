#include "View.h"
#include "Logs.h"


View::View(sf::FloatRect PlaySpaceInit)
{
    view.reset(sf::FloatRect(0, 0, SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE));
    PlaySpace = PlaySpaceInit;
}

void View::process(sf::FloatRect CenterObj)
{
    int x, y;
    // x limits
    if (CenterObj.left + CenterObj.width / 2 > PlaySpace.left+SCREEN_X_PXSIZE/2)
    {
        if (CenterObj.left + CenterObj.width / 2 < PlaySpace.left + PlaySpace.width - SCREEN_X_PXSIZE / 2)
        {
            x = CenterObj.left + CenterObj.width/2;
        }
        else
        {
            x = PlaySpace.left + PlaySpace.width - SCREEN_X_PXSIZE / 2;
        }
    }
    else
    {
        x = PlaySpace.left + SCREEN_X_PXSIZE / 2;
    }
     // y limits
    if (CenterObj.top + CenterObj.height / 2 > PlaySpace.top + SCREEN_Y_PXSIZE / 2)
    {
        if (CenterObj.top + CenterObj.height / 2 > PlaySpace.top + PlaySpace.height - SCREEN_Y_PXSIZE / 2)
        {
            y = PlaySpace.top + PlaySpace.height - SCREEN_Y_PXSIZE / 2;
        }
        else
        {
            y = CenterObj.top + CenterObj.height/2;
        }
    }
    else
    {
        y = PlaySpace.top + SCREEN_Y_PXSIZE / 2;
    }
    view.setCenter(x,y);
}