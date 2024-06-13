#include "Application.h"

void Application::Setup(olc::PixelGameEngine* pge)
{
	//Kinetic = new Kinematics(pge);
	
	Body* light_saber = new Body(BoxShape(200, 40, MIDDLE), pge->ScreenWidth() / 2, pge->ScreenHeight() / 2, 1.0f, true);
	light_saber->SetTexture("anakinsaber.png");
	light_saber->movementstatic = false;
	light_saber->rotationstatic = false;

	bObjects.push_back(light_saber);
	
	//Kinetic->setup(pge);
	
}

void Application::Input(olc::PixelGameEngine* ptr)
{

	
	if (ptr->GetKey(olc::W).bHeld)
	{
		Mainpos.y = -5;
	}
	if (ptr->GetKey(olc::S).bHeld)
	{
		Mainpos.y = 5;
	}
	if (ptr->GetKey(olc::A).bHeld)
	{
		Mainpos.x = -5;
		
	}
	if (ptr->GetKey(olc::D).bHeld)
	{
		Mainpos.x = 5;
	
	}

	if (ptr->GetKey(olc::W).bReleased)
	{
		Mainpos.y = 0;
	}
	if (ptr->GetKey(olc::S).bReleased)
	{
		Mainpos.y = 0;
	}
	if (ptr->GetKey(olc::A).bReleased)
	{
		Mainpos.x = 0;

	}
	if (ptr->GetKey(olc::D).bReleased)
	{
		Mainpos.x = 0;

	}

	if (ptr->GetKey(olc::LEFT).bHeld)
	{
		newrotation = -1.0f;
	}
	if (ptr->GetKey(olc::RIGHT).bHeld)
	{
		newrotation = 1.0f;
	}
	if (ptr->GetKey(olc::LEFT).bReleased)
	{
		newrotation = 0.0f;
	}
	if (ptr->GetKey(olc::RIGHT).bReleased)
	{
		newrotation = 0.0f;
	}

	if (ptr->GetKey(olc::SPACE).bHeld)
	{
		index = 1;
	}
	if (ptr->GetKey(olc::SPACE).bReleased)
	{
		index = 0;
	}
	
	
	
	
}

void Application::Update(float deltatime,olc::PixelGameEngine* ptr) 
{


	for (auto body : bObjects)
	{
		int count = 0;
		MS.mousecontrol(ptr, body, count);
	}

	// Integrate the acceleration and velocity to estimate the new position
	//for (auto body : bSetting) {
	//	Vec2f movement = 
	//
	//	body->Update(deltatime);
	//}
	
	// commenting this out mouse control position changing works
	for (auto body : bObjects) {
		Vec2f movement(Mainpos.x, Mainpos.y);
		body->AddPosition(movement);
		body->AddRotation(newrotation * deltatime); 
		
		body->Update(deltatime);
	}


	



	//Kinetic->update(ptr);
}

void Application::Render(olc::PixelGameEngine* ptr)
{
	
	

	for (auto& body : bObjects)
	{
	
		if (body->shape->GetType() == CIRCLE)
		{
	
			CircleShape* circleshape = (CircleShape*)body->shape;
			DraweWireFrameModel(ptr, circleshape->vertices, body->position.x, body->position.y, body->rotation, circleshape->radius, 0xff00ff00);
			//ptr->FillCircle(body->position.x, body->position.y, circleshape->radius, color);
		}
		if (body->shape->GetType() == BOX)
		{
	
			BoxShape* boxShape = (BoxShape*)body->shape;
	
			
			//ptr->DrawSprite(body->position.x, body->position.y, body->sprite);
			for (int i = 0; i < boxShape->worldvertices.size(); i++)
			{
	
				ptr->FillCircle({ int(boxShape->worldvertices[i].x),int(boxShape->worldvertices[i].y) }, 7, olc::CYAN);
				ptr->FillCircle({ int(body->position.x),int(body->position.y) }, 7, olc::CYAN);
			}
	
			if (body->sprite != nullptr)
			{
				MS.Render(ptr, body);
			}
			//Graphics::DrawPolygon(ptr, body->position.x, body->position.y, boxShape->worldvertices, 0xff00ff00);
	
	
		}
		if (body->shape->GetType() == POLYGON)
		{
			PolygonShape* polygonShape = (PolygonShape*)body->shape;
			Graphics::DrawPolygon(ptr, body->position.x, body->position.y, polygonShape->worldvertices, 0xff00ff00);
		}
	
	
	}
	
	//envoriment rendering

	for (auto& body : bSetting)
	{
		
		if (body->shape->GetType() == CIRCLE)
		{
			
			CircleShape* circleshape = (CircleShape*)body->shape;
			DraweWireFrameModel(ptr, circleshape->vertices, body->position.x, body->position.y,body->rotation, circleshape->radius, 0xff00ff00);
			//ptr->FillCircle(body->position.x, body->position.y, circleshape->radius, color);
		}
		if(body->shape->GetType() == BOX)
		{
			
			BoxShape* boxShape = (BoxShape*)body->shape;
			
			
			//ptr->DrawSprite(body->position.x, body->position.y, body->sprite);
			for (int i = 0; i < boxShape->worldvertices.size(); i++)
			{
			
					ptr->FillCircle({ int(boxShape->worldvertices[i].x),int(boxShape->worldvertices[i].y) }, 7, olc::CYAN);
					ptr->FillCircle({ int(body->position.x),int(body->position.y) }, 7, olc::CYAN);
			}
			if (body->sprite != nullptr)
			{
				MS.Render(ptr, body);
			}
			
			//Graphics::DrawPolygon(ptr, body->position.x, body->position.y, boxShape->worldvertices, 0xff00ff00);
			
			
		}
		if (body->shape->GetType() == POLYGON)
		{
			PolygonShape* polygonShape = (PolygonShape*)body->shape;
			Graphics::DrawPolygon(ptr, body->position.x, body->position.y, polygonShape->worldvertices, 0xff00ff00);
		}

		
	}
	//for(int i = 0; i < thebody.size() - 1;i++)
	//{ 
	//  thebody[i]->Render(ptr);
	//}
   //Kinetic->render(ptr);
	
}

void Application::Destroy()
{
	for (auto body : bSetting)
	{
		delete body;
	}
}

void Application::DraweWireFrameModel(olc::PixelGameEngine* pge, const std::vector<Vec2f> vecmodelcoordinates, float x, float y, float r, float s, olc::Pixel p)
{
	std::vector<Vec2f> vecTransformedCoordinates;
	int verts = vecmodelcoordinates.size();
	vecTransformedCoordinates.resize(verts);

	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x = vecmodelcoordinates[i].x * cosf(r) - vecmodelcoordinates[i].y * sinf(r);
		vecTransformedCoordinates[i].y = vecmodelcoordinates[i].x * sinf(r) + vecmodelcoordinates[i].y * cosf(r);
	}

	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x = vecTransformedCoordinates[i].x * s;
		vecTransformedCoordinates[i].y = vecTransformedCoordinates[i].y * s;
 	}

	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x = vecTransformedCoordinates[i].x + x;
		vecTransformedCoordinates[i].y = vecTransformedCoordinates[i].y + y;
	}

	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);
		pge->DrawLine(vecTransformedCoordinates[i % verts].x, vecTransformedCoordinates[i % verts].y,
			vecTransformedCoordinates[j % verts].x, vecTransformedCoordinates[j % verts].y, p);
	}

}

float Application::toRadians(float angle)
{
	return angle * (3.14159 / 180);
}

float Application::inrange(float fBase_deg, float fCurA_deg, float fRange_deg)
{
	 float fBaseA_rad = toRadians( fBase_deg );
    float fCurA_rad  = toRadians( fCurA_deg  );
    float minrange = Mod2Pi( fBaseA_rad - toRadians( fRange_deg ));
    float maxrange = Mod2Pi( fBaseA_rad + toRadians( fRange_deg ));

    float fResult = fCurA_rad;

    if (minrange < maxrange) {
        // minrange and maxrange are not flipped around 0 radians
        if (minrange > fCurA_rad || fCurA_rad > maxrange) {
            // angle is not in range, return the boundary that's closest to it
            fResult = (abs( minrange - fCurA_rad ) < abs( maxrange - fCurA_rad )) ? minrange : maxrange;
        }
    } else {
        // minrange and maxrange are flipped around 0 radians
        if (minrange > fCurA_rad && fCurA_rad > maxrange) {
            // angle is not in range, return the boundary that's closest to it
            fResult =  (abs( minrange - fCurA_rad ) < abs( maxrange - fCurA_rad )) ? minrange : maxrange;
        }
    }
    return fResult;
}

float Application::Mod2Pi(float angle)
{
	while (angle < 0.0f)
	{
		angle += 2.0f * 3.1415926535f;
	}

	while (angle >= 2.0f * 3.1415926535f)
	{
		angle -= 2.0f * 3.1415926535f;

	}
	return angle;
}
