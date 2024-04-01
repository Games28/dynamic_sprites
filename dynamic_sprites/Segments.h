#ifndef SEGMENTS_H
#define SEGMENTS_H
#include "olcPixelGameEngine.h"

class segment
{
public:
	segment(float x, float y, float angle, float length);
	segment(segment* parent, float angle, float length);
	void calculateB(float range);

	void SetA(olc::vf2d pos);

	void update(float range);

	void render(olc::PixelGameEngine* pge);

	void follow(float tx, float ty);

	void follow(segment* child);

public:
	olc::vf2d a;
	olc::vf2d b;
	float angle;
	float baseangle;
	float length;
	segment* parent = nullptr;
	//Segment* child = nullptr;
};



class Segments
{
public:
	Segments(float x, float y, std::vector<float> angle, std::vector<int> lengths, int count);
	Segments(float x, float y, float angle, float length);
	void AddSegment(float x, float y, float angle, float length);
	void addBase(float x, float y);
	void Update(float x, float y, bool basedset, float range);
	void UpdateBase();
	void Render(olc::PixelGameEngine* pge);
	int getTotal();
	segment getSegment(int id);
	void setangle(float ang,int id);
	float GetAngle(int id);
	int getX(int id);
	int getY(int id);

public:

	std::vector<segment*> segments;
	olc::vf2d base;
	float length;
	int count;
};

#endif // !SEGMENTS_H


