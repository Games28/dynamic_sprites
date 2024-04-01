#include "Shape.h"
#include <iostream>

CircleShape::CircleShape(const float radius, const int VerticesCount)
{
	this->radius = radius;
	this->vertexCount = VerticesCount;
	vertices.push_back(Vec2f(0.0f, 0.0f));
	for (int i = 0; i < vertexCount; i++)
	{
		vertices.push_back({ cosf(i / (float)(vertexCount - 1) * 2.0f * 3.14159f), sinf(i / (float)(vertexCount - 1) * 2.0f * 3.14159f) });

	}

	
	std::cout << "circleshape constructor called" << std::endl;

}

CircleShape::~CircleShape()
{
	std::cout << "circleshape destructor called" << std::endl;
}

ShapeType CircleShape::GetType() const
{
	return CIRCLE;
}

Shape* CircleShape::Clone() const
{
	return new CircleShape(radius, vertexCount);
}

float CircleShape::GetMomentOfInertia() const
{
	return 0.5f * ( radius * radius);
}

void CircleShape::UpdateVertices(float angle, const Vec2f& position)
{
	return;
}

PolygonShape::PolygonShape(const std::vector<Vec2f> vertices)
{
	for (auto vertex : vertices)
	{
		localvertices.push_back(vertex);
		worldvertices.push_back(vertex);
		
	}
}

PolygonShape::~PolygonShape()
{

	std::cout << "polygoneshape destructor called" << std::endl;
}

Vec2f PolygonShape::EdgeAt(int index) const
{
	int currVertex = index;
	int nextVertex = (index + 1) % worldvertices.size();

	return worldvertices[nextVertex] - worldvertices[currVertex];
}

float PolygonShape::FindMinSeparation(PolygonShape* other, int& indexreferenceedge, Vec2f& supportpoint)
{
	float separation = std::numeric_limits<float>::lowest();

	for (int i = 0; i < worldvertices.size(); i++)
	{
		Vec2f va = this->worldvertices[i];
		Vec2f normal = this->EdgeAt(i).Normal();

		float minSep = std::numeric_limits<float>::max();
		Vec2f minVertex;
		for (int j = 0; j < other->worldvertices.size(); j++)
		{
			Vec2f vb = other->worldvertices[j];
			float proj = (vb - va).Dot(normal);
			if (proj < minSep)
			{
				minSep = proj;
				minVertex = vb;
			}
			


		}
		if (minSep > separation)
		{
			separation = minSep;
			indexreferenceedge = i;
			supportpoint = minVertex;
		}
	}

	return separation;
}

int PolygonShape::FindIncidentEdge(const Vec2f& normal) const
{
	int indexIncidentEdge;
	float minProj = std::numeric_limits<float>::max();
	for (int i = 0; i < this->worldvertices.size(); i++)
	{
		auto edgeNormal = this->EdgeAt(i).Normal();
		auto proj = edgeNormal.Dot(normal);
		if (proj < minProj)
		{
			minProj = proj;
			indexIncidentEdge = i;
		}
	}
	

	return indexIncidentEdge;
}

int PolygonShape::ClipSegmentToLine(const std::vector<Vec2f>& contactsIn, std::vector<Vec2f>& contactsOut, const Vec2f& c0, const Vec2f& c1) const
{
	int numOut = 0;

	Vec2f normal = (c1 - c0).Normalize();
	float dist0 = (contactsIn[0] - c0).Cross(normal);
	float dist1 = (contactsIn[1] - c0).Cross(normal);

	if (dist0 <= 0)
		contactsOut[numOut++] = contactsIn[0];
	if (dist1 <= 0)
		contactsOut[numOut++] = contactsIn[1];

	if (dist0 * dist1 < 0)
	{
		float totalDist = dist0 - dist1;

		float t = dist0 / (totalDist);
		Vec2f contact = contactsIn[0] + (contactsIn[1] - contactsIn[0]) * t;
		contactsOut[numOut] = contact;
		numOut++;
	}
	return numOut;
}



ShapeType PolygonShape::GetType() const
{
	return POLYGON;
}

Shape* PolygonShape::Clone() const
{
	return new PolygonShape(localvertices );
}

float PolygonShape::GetMomentOfInertia() const
{
	return 5000;
}



void PolygonShape::UpdateVertices(float angle, const Vec2f& position)
{
	for (int i = 0; i < localvertices.size(); i++)
	{

		worldvertices[i] = localvertices[i].Rotate(angle);


		worldvertices[i] += position;

	}
}

BoxShape::BoxShape(float width, float height, RotateSide Side)
{
	Rside = Side;
	this->width = width;
	this->height = height; 

	switch (Rside)
	{
	case MIDDLE:
	{
		localvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));

		worldvertices.push_back(Vec2f(-width / 2.0f, -height / 2.0f));
		worldvertices.push_back(Vec2f(+width / 2.0f, -height / 2.0f));
		worldvertices.push_back(Vec2f(+width / 2.0f, +height / 2.0f));
		worldvertices.push_back(Vec2f(-width / 2.0f, +height / 2.0f));
	}break;

	case UP:
	{
		localvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f) + (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case BOTTOM:
	{
		localvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f) - (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case LEFT:
	{
		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (+height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (+height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case RIGHT:
	{
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (-height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (+height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (+height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case UPLEFT:
	{
		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (+height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (+height / 2.0f) + (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));

	}break;

	case UPRIGHT:
	{
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (-height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (+height / 2.0f) + (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (+height / 2.0f) + (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case BOTLEFT:
	{

		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) + (width / 2.0f), (+height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) + (width / 2.0f), (+height / 2.0f) - (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;

	case BOTRIGHT:
	{
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (-height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((+width / 2.0f) - (width / 2.0f), (+height / 2.0f) - (height / 2.0f)));
		localvertices.push_back(Vec2f((-width / 2.0f) - (width / 2.0f), (+height / 2.0f) - (height / 2.0f)));

		worldvertices.push_back(Vec2f((-width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (-height / 2.0f)));
		worldvertices.push_back(Vec2f((+width / 2.0f), (+height / 2.0f)));
		worldvertices.push_back(Vec2f((-width / 2.0f), (+height / 2.0f)));
	}break;
	}
	
	
	
	offsetverts.push_back(Vec2f(0.0f,0.0f));
	offsetverts.push_back(Vec2f(0.0f, 0.0f));
	offsetverts.push_back(Vec2f(0.0f, 0.0f));
	offsetverts.push_back(Vec2f(0.0f, 0.0f));
	
}

BoxShape::~BoxShape()
{
}

ShapeType BoxShape::GetType() const
{
	return BOX;
}

Shape* BoxShape::Clone() const
{
	return new BoxShape(width,height, Rside);
}

float BoxShape::GetMomentOfInertia() const
{
	return (0.083333) * (width * width + height * height);
}

