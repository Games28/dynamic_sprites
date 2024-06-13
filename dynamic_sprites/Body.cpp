#include "Body.h"
#include <iostream>

Body::Body(const Shape& shape,float x, float y, float mass, bool isobject)
{
	this->shape = shape.Clone();
	this->shape->isObject = isobject;
	//linear motion
	this->position = Vec2f(x, y);
	this->old_position = Vec2f(x, y);
	this->velocity = Vec2f(0, 0);
	this->acceleration = Vec2f(0, 0);
	//angular motion
	this->rotation = 0.0f;
	this->angularvelocity = 0.0f;
	this->angularacceleration = 0.0f;
	this->restitution = 1.0f;
	this->friction = 0.7f;
	this->sumForces = Vec2f{ 0,0 };
	this->sumTorque = 0.0f;
	this->mass = mass;
	if (mass != 0.0f)
	{
		this->invMass = 1.0f / mass; 
	}
	else
	{
		this->invMass = 0.0f;
	}

	Inertia = shape.GetMomentOfInertia() * mass;

	if (Inertia != 0.0f)
	{
		this->invInertia = 1.0f / Inertia;
	}
	else
	{
		this->invInertia = 0.0f;
	}
	this->shape->UpdateVertices(rotation, position);
	std::cout << "body constructed!" << std::endl;
}

Body::~Body()
{
	delete shape;
	std::cout << "body destroyed!" << std::endl;
}


void Body::AddForce(const Vec2f& force)
{
	sumForces += force;
}

void Body::AddTorque(float torque)
{
	sumTorque += torque;
}

void Body::AddPosition(Vec2f& pos)
{
	position += pos;
}

void Body::AddRotation(float rotate)
{
	rotation += rotate;
}

void Body::ClearTorgue()
{
	sumTorque = 0;
}

void Body::ClearForces()
{
	sumForces = Vec2f(0.0f, 0.0f);
}

bool Body::IsStatic() const 
{
	const float epsilon = 0.005f;
	bool result = fabs(invMass - 0.0f) < epsilon;
	 
	return result;
}

Vec2f Body::LocalSpaceToWorldSpace(const Vec2f& point) const
{
	Vec2f rotated = point.Rotate(rotation);
	return rotated + position;
}

Vec2f Body::WorldSpaceToLocalSpace(const Vec2f& point) const
{
	float translatedX = point.x - position.x;
	float translatedY = point.y - position.y;
	float rotatedX = cos(-rotation) * translatedX - sin(-rotation) * translatedY;
	float rotatedY = cos(-rotation) * translatedY + sin(-rotation) * translatedX;
	return Vec2f(rotatedX, rotatedY);
}

void Body::ApplyImpulseAngular(const float j)
{
	if (rotationstatic) return;

	angularvelocity += j * invInertia;
}

void Body::ApplyImpulseLinear(const Vec2f& j)
{
	if (movementstatic) return;

	velocity += j * invMass;
}

void Body::ApplyImpulseAtPoint(const Vec2f& j, const Vec2f& r)
{
	if (movementstatic || rotationstatic) return;

	velocity += j * invMass;
	angularvelocity += r.Cross(j) * invInertia;
}

void Body::SetTexture(const char* textureFileName)
{
	sprite = new olc::Sprite(textureFileName);
	decal = new olc::Decal(sprite);
}

void Body::IntegrateForces(const float dt)
{
	
	if (!movementstatic)
	{
		acceleration = sumForces * invMass;

		// Integrate the acceleration to find the new velocity
		velocity += acceleration * dt;

		// Integrate the velocity to find the new position
		position += velocity * dt;
		
	}
	else
	{
		return;
	}

	if (!rotationstatic)
	{
		angularacceleration = sumTorque * invInertia;

		// Integrate the angular acceleration to find the new angular velocity
		angularvelocity += angularacceleration * dt;

		// Integrate the angular velocity to find the new rotation angle
		rotation += angularvelocity * dt;

	}
	else
	{
		return;
	}

	ClearForces();
	ClearTorgue();

}

void Body::IntegrateVelocities(const float dt)
{
	
	
		position += velocity * dt;
	

	
		rotation += angularvelocity * dt;
	


	shape->UpdateVertices(rotation, position);
}

void Body::Update(float dt)
{
	IntegrateForces(dt);
	bool isPolygon = shape->GetType() == POLYGON || shape->GetType() == BOX;
	if (isPolygon) {
		PolygonShape* polygonShape = (PolygonShape*)shape;
		polygonShape->UpdateVertices(rotation, position);
	}
}

