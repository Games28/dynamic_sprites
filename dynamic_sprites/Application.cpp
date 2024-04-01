#include "Application.h"

void Application::Setup(olc::PixelGameEngine* pge)
{
	Mainpos = { pge->ScreenWidth() / 2, 150 };
	Basepos = Mainpos;
	std::vector<int> mainvectors = { 90,50 };
	std::vector<float> mainangles = { toRadians(110),toRadians(75)};
	mainbody = new Segments(pge->ScreenWidth() / 2, 100, mainangles, mainvectors, 2);
	//mainbody->AddSegment()
	segment seg1 = mainbody->getSegment(0);
	segment seg2 = mainbody->getSegment(1);
	
	Body* Atbody = new Body(BoxShape(100, 100,LEFT), Mainpos.x,Mainpos.y, 0.0, true);
	Atbody->SetTexture("ATbody.png");
	
	Body* Atupleg = new Body(BoxShape(50, 100, UPLEFT),Basepos.x,Basepos.y, 0.0f, true);
	Atupleg->SetTexture("ATupperleg.png");
	Body* Atlowleg = new Body(BoxShape(100, 100, UPLEFT), seg1.a.x,seg1.a.y, 0.0f, true);
	Atlowleg->SetTexture("ATlowerleg.png");
	
	bObjects.push_back(Atbody);
	bObjects.push_back(Atupleg);
	bObjects.push_back(Atlowleg);
	//player->setup(pge);
	//leadpos = { 400,300 };
	//Body* floor = new Body(BoxShape(pge->ScreenWidth() - 50, 50,false), pge->ScreenWidth() / 2.0, pge->ScreenHeight() - 50, 0.0,false);
	//Body* leftWall = new Body(BoxShape(50, pge->ScreenHeight() - 100,false), 50, pge->ScreenHeight() / 2.0 - 25, 0.0,false);
	//Body* rightWall = new Body(BoxShape(50, pge->ScreenHeight() - 100,false), pge->ScreenWidth() - 50, pge->ScreenHeight() / 2.0 - 25, 0.0,false);
	//floor->restitution = 0.5;
	//leftWall->restitution = 0.2;
	//rightWall->restitution = 0.2;
	//bSetting.push_back(floor);
	//bSetting.push_back(leftWall);
	//bSetting.push_back(rightWall);

	MS.Setup(pge);
	
	
}

void Application::Input(olc::PixelGameEngine* ptr)
{
	if (ptr->GetKey(olc::W).bHeld)
	{
		Mainpos.y += -5;
	}
	if (ptr->GetKey(olc::S).bHeld)
	{
		Mainpos.y += 5;
	}
	if (ptr->GetKey(olc::A).bHeld)
	{
		Mainpos.x += -5;
		
	}
	if (ptr->GetKey(olc::D).bHeld)
	{
		Mainpos.x += 5;
	
	}

	if (ptr->GetKey(olc::SPACE).bPressed)
	{
		if (sample != nullptr)
		{
			sample = nullptr;
		}
		sample = new olc::Sprite(result->width, result->height);

		ptr->SetDrawTarget(sample);

		for (auto& object : bObjects)
		{
				MS.Render(ptr, object);
		
		}

		ptr->SetDrawTarget(nullptr);
	
	}
	
	if (ptr->GetKey(olc::I).bHeld)
		leadpos.y = -1;
	
	if (ptr->GetKey(olc::K).bHeld)
		leadpos.y = 1;
	
	if (ptr->GetKey(olc::J).bHeld)
	{
		leadpos.x = -1;
		
	}
	if (ptr->GetKey(olc::L).bHeld)
	{
		leadpos.x = 1;
	}

	if (ptr->GetKey(olc::I).bReleased)
		leadpos.y = 0;

	if (ptr->GetKey(olc::K).bReleased)
		leadpos.y = 0;

	if (ptr->GetKey(olc::J).bReleased)
	{
		leadpos.x = 0;

	}
	if (ptr->GetKey(olc::L).bReleased)
	{
		leadpos.x = 0;
	}
	
	
	if (ptr->GetKey(olc::F1).bPressed) bodynumber = 0;
	if (ptr->GetKey(olc::F2).bPressed) bodynumber = 1;
	if (ptr->GetKey(olc::F3).bPressed) bodynumber = 2;
	if (ptr->GetKey(olc::F4).bPressed) bodynumber = 3;
	if (ptr->GetKey(olc::F5).bPressed) bodynumber = 4;
	if (ptr->GetKey(olc::LEFT).bHeld)  testangle += 0.1f;//pushForce.x = 0;
	if (ptr->GetKey(olc::RIGHT).bHeld)testangle -= 0.1f;//pushForce.x = 0;
	//if (ptr->GetKey(olc::LEFT).bReleased) testangle = 0.0f;//pushForce.x = 0;
	//if (ptr->GetKey(olc::RIGHT).bReleased) testangle = 0.0f;//pushForce.x = 0;
	
}

void Application::Update(float deltatime,olc::PixelGameEngine* ptr) 
{
	if (deltatime > 0.017)
	{
		deltatime = 0.017f;
	}
	// Integrate the acceleration and velocity to estimate the new position
	for (auto body : bSetting) {
		body->Update(deltatime);
	}
	
	for (auto body : bObjects) {
		body->Update(deltatime);
	}
	
	bObjects[0]->position.x = Mainpos.x;
	bObjects[0]->position.y = Mainpos.y;

	Basepos = Mainpos;
	//bObjects[1]->position.x = Basepos.x;
	//bObjects[1]->position.y = Basepos.y;

	segment baseseg = mainbody->getSegment(0);
	bObjects[1]->position.x = Basepos.x;
	bObjects[1]->position.y = Basepos.y;
	bObjects[1]->rotation = inrange(baseseg.baseangle - 1.57,baseseg.angle - 1.57,30);


	segment leadseg = mainbody->getSegment(1);
	bObjects[2]->position.x = leadseg.a.x;
	bObjects[2]->position.y = leadseg.a.y;
	bObjects[2]->rotation = inrange(leadseg.baseangle - 1.57,leadseg.angle - 1.57, 30);
	
	ptr->DrawString(20, 20, "rotation1: " + std::to_string(bObjects[1]->rotation));
	ptr->DrawString(20, 30, "rotation2: " + std::to_string(bObjects[2]->rotation));
	mainbody->addBase(bObjects[0]->position.x, bObjects[0]->position.y);
	mainbody->Update(leadseg.b.x + leadpos.x, leadseg.b.y + leadpos.y, true,0);
	mainbody->UpdateBase();
	//player->update(ptr);
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

			if (body->sprite != nullptr)
			{
				MS.Render(ptr, body);
			}
			//ptr->DrawSprite(body->position.x, body->position.y, body->sprite);
			for (int i = 0; i < boxShape->worldvertices.size(); i++)
			{

				//ptr->FillCircle({ int(boxShape->worldvertices[i].x),int(boxShape->worldvertices[i].y) }, 7, olc::CYAN);
				ptr->FillCircle({ int(body->position.x),int(body->position.y) }, 7, olc::CYAN);
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
			
			if (body->sprite != nullptr)
			{
				MS.Render(ptr, body);
			}
			//ptr->DrawSprite(body->position.x, body->position.y, body->sprite);
			for (int i = 0; i < boxShape->worldvertices.size(); i++)
			{
			
					ptr->FillCircle({ int(boxShape->worldvertices[i].x),int(boxShape->worldvertices[i].y) }, 7, olc::CYAN);
					//ptr->FillCircle({ int(body->position.x),int(body->position.y) }, 7, olc::CYAN);
			}
			
			
			Graphics::DrawPolygon(ptr, body->position.x, body->position.y, boxShape->worldvertices, 0xff00ff00);
			
			
		}
		if (body->shape->GetType() == POLYGON)
		{
			PolygonShape* polygonShape = (PolygonShape*)body->shape;
			Graphics::DrawPolygon(ptr, body->position.x, body->position.y, polygonShape->worldvertices, 0xff00ff00);
		}

		
	}
	//mainbody->Render(ptr);
	//player->render(ptr);
	
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

float Application::inrange(float baseangle, float angle, float range)
{
	float Baseangle = toRadians(baseangle);
	float curangle = toRadians(angle);
	float minrange = Baseangle + -toRadians(range);
	float maxrange = Baseangle + toRadians(range);

	if (curangle < minrange)
	{
		return minrange;
	}
	else if (curangle > maxrange)
	{
		return maxrange;
	}
	else
	{
		return curangle;
	}
	
}
