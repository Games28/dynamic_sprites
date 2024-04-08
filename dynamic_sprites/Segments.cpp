#include "Segments.h"

segment::segment(float x, float y, float angle, float length)
{
	a = { x,y };
	this->angle = angle;
	this->length = length;
	this->baseangle = angle;
	calculateB(0);
}

segment::segment(segment* parent, float angle, float length)
{
	this->parent = parent;
	a = parent->b;
	this->length = length;
	this->angle = angle;
	this->baseangle = angle;
	calculateB(0);
}

void segment::calculateB(float range)
{
	float dx = length * cos(angle);
	float dy = length * sin(angle);
	b = { a.x + dx, a.y + dy };
}

void segment::SetA(olc::vf2d pos)
{
	a = pos;
	calculateB(0);
}

void segment::update(float range)
{
	calculateB(0);
}

void segment::render(olc::PixelGameEngine* pge)
{
	pge->DrawLine(a.x, a.y, b.x, b.y);
	pge->FillCircle(a.x, a.y, 5, olc::CYAN);
}

void segment::follow(float tx, float ty)
{
	olc::vf2d target = { tx,ty };
	olc::vf2d dir = { target.x - a.x, target.y - a.y };
	angle = atan2f(dir.y, dir.x);
	
	float dx = length * cos(angle);
	float dy = length * sin(angle);
	a = { target.x - dx,target.y - dy };
}

void segment::follow(segment* child)
{
	float targetx = child->a.x;
	float targety = child->a.y;
	follow(targetx, targety);
}

Segments::Segments(float x, float y, std::vector<float> angle, std::vector<int> lengths, int count)
{
	this->count = count;
    this->length = lengths[0];
	int Len = lengths[0];
	
	segment* start = new segment(x, y, angle[0], Len);
	
	segments.push_back(start);

	segment* current = start;
	for (int i = 1; i < count; i++)
	{

		segment* next = new segment(segments[i - 1], angle[i], lengths[i]);
		segments.push_back(next);

	}

	
}

Segments::Segments(float x, float y, float angle, float length)
{
	segment* start = new segment(x, y, angle, length);

	segments.push_back(start);
}

void Segments::AddSegment(float x, float y, float angle, float length)
{
	int i = segments.size();
	segment* next = new segment(segments[i - 1], angle, length);
	segments.push_back(next);
}

void Segments::addBase(float x, float y)
{
	base = { x, y };
}

void Segments::Update(float x, float y, bool basedset, float range)
{
	int lead = segments.size() - 1;


	segments[lead]->follow(x, y);
	segments[lead]->update(0);


	for (int i = segments.size() - 2; i >= 0; i--)
	{
		segment* current = segments[i];
		current->follow(segments[i + 1]);
		current->update(range);



	}


	//base setting start
	//if (basedset)
	//{
	//	segments[0]->SetA(base);
	//
	//	for (int i = 1; i < segments.size(); i++)
	//	{
	//		segments[i]->SetA(segments[i - 1]->b);
	//	}
	//}
	//base setting end

}

void Segments::UpdateBase()
{
	segments[0]->SetA(base);

	for (int i = 1; i < segments.size(); i++)
	{
		segments[i]->SetA(segments[i - 1]->b);
	}
}

void Segments::Render(olc::PixelGameEngine* pge)
{
	for (int i = 0; i < segments.size(); i++)
	{
		segments[i]->render(pge);
	}
}

int Segments::getTotal()
{

	return segments.size();
}

segment Segments::getSegment(int id)
{
	
	return *segments[id];
}

void Segments::setangle(float ang,int id)
{
	segments[id]->angle = ang;
}

float Segments::GetAngle(int id)
{
	float angle = segments[id]->angle;
	return angle;
}

int Segments::getX(int id)
{
	return segments[id]->a.x;
}

int Segments::getY(int id)
{
	return segments[id]->a.y;
}
