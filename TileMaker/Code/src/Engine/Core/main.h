#include "Engine.h"

extern TileMaker::Engine* InitTileMaker();

int main()
{

    auto app = InitTileMaker();

    app->Run();

    delete app;

    return 0;
}