#include "Core/main.h"

class TileMakerApp : public TileMaker::Engine
{
public:
	TileMakerApp() {}
	~TileMakerApp() {}

private:

};

TileMaker::Engine* InitTileMaker()
{
     return new TileMakerApp();
}
