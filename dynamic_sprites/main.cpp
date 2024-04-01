#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Application.h"

class dynamic_sprites : public olc::PixelGameEngine
{
public:
	dynamic_sprites()
	{
		sAppName = "dynamic_sprites";
	}

public:
	
	Application app;

public:


	bool OnUserCreate() override
	{
		
		
		app.Setup(this);
		
		return true;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		app.Input(this);
		app.Update(fElapsedTime, this);
		app.Render(this);

		
		return true;
	}
};


int main()
{
	dynamic_sprites demo;
	if (demo.Construct(1200, 800, 1, 1))
		demo.Start();

	return 0;
}