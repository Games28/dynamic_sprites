#ifndef SHAPE_H
#define SHAPE_H
#include "Vec2.h"
#include <vector>

enum ShapeType
{
	CIRCLE,
	POLYGON,
	BOX
};

enum RotateSide
{
	MIDDLE,
	UP,
	BOTTOM,
	LEFT,
	RIGHT,
	UPRIGHT,
	BOTRIGHT,
	UPLEFT,
	BOTLEFT
};

struct Shape
{
	
	virtual  ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
	virtual float GetMomentOfInertia() const = 0;
	virtual void UpdateVertices(float angle, const Vec2f& position) = 0;
	int verticindex = 0;
	int bodyindex = 0;
	bool isObject = false;

};

struct CircleShape : public Shape
{
	float radius;
	int vertexCount;
	std::vector<Vec2f> vertices;
	CircleShape(const float radius,const int VerticesCount);
	virtual ~CircleShape();
	ShapeType GetType() const override; 
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;
	void UpdateVertices(float angle, const Vec2f& position) override;
};

struct PolygonShape : public Shape
{
	std::vector<Vec2f> localvertices;
	std::vector<Vec2f> worldvertices;
	std::vector<Vec2f> offsetverts;
	PolygonShape() = default;
	PolygonShape(const std::vector<Vec2f> vertices);
	virtual ~PolygonShape();
	Vec2f EdgeAt(int index) const;
	float FindMinSeparation(PolygonShape* other, int& indexreferenceedge,Vec2f& supportpoint);
	int FindIncidentEdge(const Vec2f& normal) const;
	int ClipSegmentToLine(const std::vector<Vec2f>& contactsIn, std::vector<Vec2f>& contactsOut,
		const Vec2f& c0, const Vec2f& c1) const;
	ShapeType GetType() const override;
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;
	
	void UpdateVertices(float angle, const Vec2f& position) override;
};

struct BoxShape : public PolygonShape
{
	float width;
	float height;

	BoxShape(float width, float height, RotateSide Side);
	virtual ~BoxShape();
	ShapeType GetType() const override;
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;
	RotateSide Rside = RotateSide::MIDDLE;
};
#endif // !SHAPE_H


