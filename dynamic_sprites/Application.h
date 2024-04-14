#ifndef APPLICATION_H
#define APPLICAITON_H
#include "olcPixelGameEngine.h"
#include "Body.h"
#include "Force.h"
#include "Graphics.h"
#include "Character.h"
#include "ManipulatedSprite.h"
#include "Segments.h"


class Application
{
public:
	Application() = default;
	~Application() = default;

public:
	std::vector<Body*> bSetting;
	std::vector<Body*> bObjects;
	Kinematics* player;
	Vec2f pushForce = Vec2f(0,0);
	Vec2f* pSelected = nullptr;
	int pIndex = -1;
	float k = 500;
	float restLength = 200.0f;
	const int NUM_PARTICLES = 4;
	bool debug = false;
	Vec2f mousepressedlocation;
	Vec2f mousereleasedlocation;
	olc::Sprite* sprite;
	olc::Decal* Dsprite;
	ManipulatedSprite MS;
	
	int saberindex;
	
	int bodynumber = 0;
	int mousenumber = 0;
	olc::vi2d leadpos0;
	olc::vi2d leadpos1;

	olc::Sprite* mandosprite;
	Segments* mainbody;
	Segments* backbody;

	Vec2f offsets[8];
	Vec2f mandopos = { 500,100 };
	Vec2f resultpos = { 0,0 };
	olc::Sprite* sample;
	int width = 40;
	int height = 40;
	bool changed = false;
	bool index = false;
	std::vector<Segments*> thebody;

	olc::Sprite* result;
	//test
	olc::vi2d Mainpos;
	olc::vi2d Basepos;
	olc::vi2d newpos;
	float testangle = 0;
	
public:

	void Setup(olc::PixelGameEngine* pge);
	void Input(olc::PixelGameEngine* ptr);
	void Update(float deltatime, olc::PixelGameEngine* ptr);
	void Render(olc::PixelGameEngine* ptr);
	void Destroy();
	void DraweWireFrameModel(olc::PixelGameEngine* pge,
		const std::vector<Vec2f> vecmodelcoordinates,
		float x, float y,
		float r = 0.0f, float s = 1.0f,
		olc::Pixel p = olc::WHITE);

	float toRadians(float angle);
	float inrange(float fBase_deg, float fCurA_deg, float fRange_deg);
	float Mod2Pi(float angle);
};



#endif // !APPLICATION_H


