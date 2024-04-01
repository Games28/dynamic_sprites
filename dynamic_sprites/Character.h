#ifndef CHARACTER_H
#define CHARACTER_H
#include "olcPixelGameEngine.h"

class Limb
{
public:
	Limb(olc::vf2d origin, float l1, float l2, bool inverseJoint);

	Limb() {}

public:
	olc::vf2d p1 = { 0.0f,0.0f };
	olc::vf2d p2 = { 0.0f,0.0f };
	olc::vf2d p3 = { 0.0f,0.0f };
	float l1 = 10.0f;
	float l2 = 10.0f;
	float a1 = 0.0f;
	float a2 = 0.0f;
	bool inverseJoint;

};

class Human_Skeleton
{
public:
	Human_Skeleton(olc::vf2d p);
	void NormalStance(olc::vf2d p);

public:
	std::vector<olc::vf2d> skeleton;

	olc::vf2d head;
	olc::vf2d neck;
	olc::vf2d left_shoulder;
	olc::vf2d right_shoulder;
	olc::vf2d left_hand;
	olc::vf2d right_hand;
	olc::vf2d hip_bone;
	olc::vf2d left_hip;
	olc::vf2d right_hip;
	olc::vf2d left_foot;
	olc::vf2d right_foot;
};

class Character
{
public:
	Character(olc::vf2d p);

public:
	olc::vf2d p;
	Human_Skeleton skeleton = Human_Skeleton(p);
	Limb left_arm;
	Limb right_arm;
	Limb left_leg;
	Limb right_leg;
	int viewDir = 1;


};


class Kinematics
{
public:
	Kinematics() = default;

	void FKAL(Limb& limb, olc::vf2d target);
	olc::vf2d polarToCartesian(float angle, float distance);
	
	void DrawCharacter(Character* c, olc::PixelGameEngine* pge);

	void setup(olc::PixelGameEngine* pge);
	void update(olc::PixelGameEngine* pge);
	void render(olc::PixelGameEngine* pge);

public:
	Character* player = nullptr;
	
	olc::vf2d selectionpos = { 0.0f,0.0f };
};
#endif // !CHARACTER_H


