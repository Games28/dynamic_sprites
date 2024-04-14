#include "Application.h"

void Application::Setup(olc::PixelGameEngine* pge)
{
	Mainpos = { pge->ScreenWidth() / 2, 150 };
	Basepos = Mainpos;
	std::vector<int> mainvectors = { 90,100 };
	std::vector<float> mainangles = { toRadians(130),toRadians(90)};
	//mainbody = new Segments(pge->ScreenWidth() / 2, 100, mainangles, mainvectors, 2);
	//mainbody->AddSegment()
	
	for (int i = 0; i < 2; i++)
	{
		Segments* mainbody = new Segments(pge->ScreenWidth() / 2, 100, mainangles, mainvectors, 2);
		thebody.push_back(mainbody);
	}
	
	
	

	//bObjects.push_back(BackAtupleg); //0
	//bObjects.push_back(BackAtlowleg); //1
	//bObjects.push_back(BackAtfoot); // 2
 
	segment seg1 = thebody[0]->getSegment(0);
	segment seg2 = thebody[0]->getSegment(1);
	segment backseg1 = thebody[1]->getSegment(0);
	segment backseg2 = thebody[1]->getSegment(1);
	newpos = { Mainpos.x , Mainpos.y + 180 };

	//back leg

	Body* backAtupleg = new Body(BoxShape(50, 100, UPLEFT), Basepos.x, Basepos.y, 0.0f, true);
	backAtupleg->SetTexture("ATupperleg.png");
	Body* backAtlowleg = new Body(BoxShape(50, 100, UPLEFT), backseg1.a.x, backseg1.a.y, 0.0f, true);
	backAtlowleg->SetTexture("ATlowerleg.png");

	Body* backAtfoot = new Body(BoxShape(100, 50, UPLEFT), backseg1.b.x, backseg1.b.y, 0.0f, true);
	backAtfoot->SetTexture("ATfoot.png");

	//main body
	Body* Atbody = new Body(BoxShape(150, 150,LEFT), Mainpos.x,Mainpos.y, 0.0, true);
	Atbody->SetTexture("ATbody.png");
	
	//front leg
	Body* Atupleg = new Body(BoxShape(50, 100, UPLEFT),Basepos.x,Basepos.y, 0.0f, true);
	Atupleg->SetTexture("ATupperleg.png");
	Body* Atlowleg = new Body(BoxShape(50, 100, UPLEFT), seg1.a.x,seg1.a.y, 0.0f, true);
	Atlowleg->SetTexture("ATlowerleg.png");
	
	Body* Atfoot = new Body(BoxShape(100, 50, UPLEFT), seg1.b.x, seg1.b.y, 0.0f, true);
	Atfoot->SetTexture("ATfoot.png");


	bObjects.push_back(backAtupleg); //4
	bObjects.push_back(backAtlowleg); //5
	bObjects.push_back(backAtfoot); // 6
	bObjects.push_back(Atbody); //0
	bObjects.push_back(Atupleg); //1
	bObjects.push_back(Atlowleg); //2
	bObjects.push_back(Atfoot); // 3

	
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

	if (ptr->GetKey(olc::SPACE).bHeld)
	{
		index = 1;
	}
	if (ptr->GetKey(olc::SPACE).bReleased)
	{
		index = 0;
	}
	
	
	if (ptr->GetKey(olc::I).bHeld)
	{
		if(index == 0) leadpos0.y += -1;
		if (index == 1) leadpos1.y += -1;
	}
	
	if (ptr->GetKey(olc::K).bHeld)
	{
		if (index == 0) leadpos0.y += 1;
		if (index == 1) leadpos1.y += 1;
	}
	
	if (ptr->GetKey(olc::J).bHeld)
	{
		if (index == 0) leadpos0.x += -1;
		if (index == 1) leadpos1.x += -1;
		
	}
	if (ptr->GetKey(olc::L).bHeld)
	{
		if (index == 0) leadpos0.x += 1;
		if (index == 1) leadpos1.x += 1;
	}

	if (ptr->GetKey(olc::I).bReleased)
	{
		if (index == 0) leadpos0.y += 0;
		if (index == 1) leadpos1.y += 0;
	}

	if (ptr->GetKey(olc::K).bReleased)
	{
		if (index == 0) leadpos0.y += 0;
		if (index == 1) leadpos1.y += 0;
	}

	if (ptr->GetKey(olc::J).bReleased)
	{
		if (index == 0) leadpos0.x += 0;
		if (index == 1) leadpos1.x += 0;

	}
	if (ptr->GetKey(olc::L).bReleased)
	{
		leadpos0.x += 0;
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

	bObjects[3]->position.x = Mainpos.x;
	bObjects[3]->position.y = Mainpos.y;

	for (int i = 0; i < thebody.size(); i++)
	{
		
		if(i == index)
		{
		
			Basepos = Mainpos;
		
		
			segment baseseg = thebody[0]->getSegment(0);
			bObjects[4]->position.x = Basepos.x;
			bObjects[4]->position.y = Basepos.y;
			bObjects[4]->rotation = baseseg.angle - 1.57;
		
		
			segment leadseg = thebody[0]->getSegment(1);
		
			bObjects[5]->position.x = leadseg.a.x;
			bObjects[5]->position.y = leadseg.a.y;
		
		
		
			float currentangle = leadseg.angle - 1.57;
			float minrange = -0.1;
			float maxrange = -0.5;
			float distX = leadseg.a.x - leadpos0.x;
			float distY = leadseg.a.y - leadpos0.y;
			float dx = distX * cos(currentangle);
			float dy = distX * sin(currentangle);
		
			if (currentangle > minrange)
			{
		
		
				bObjects[5]->rotation = minrange;
			}
			else if (currentangle < maxrange)
			{
		
				bObjects[5]->rotation = maxrange;
			}
			else
			{
		
				bObjects[5]->rotation = currentangle;
		
			}
		
			newpos = { (Mainpos.x) + leadpos0.x, (Mainpos.y + 180) + leadpos0.y };
		
			if (newpos.x < Mainpos.x - 30)
			{
				newpos.x = Mainpos.x - 30;
		
			}
			if (newpos.x > Mainpos.x + 30)
			{
				newpos.x = Mainpos.x + 30;
			}
		
			if (newpos.y < Mainpos.y + 160)
			{
				newpos.y = Mainpos.y + 160;
			}
			if (newpos.y > Mainpos.y + 180)
			{
				newpos.y = Mainpos.y + 180;
			}
		
			//bObjects[2]->rotation = inrange(leadseg.baseangle,leadseg.angle ,30);
			bObjects[6]->position.x = leadseg.b.x;
			bObjects[6]->position.y = leadseg.b.y;
		
			
			thebody[0]->addBase(bObjects[3]->position.x, bObjects[3]->position.y);
			thebody[0]->Update(newpos.x, newpos.y, true, 0);
			thebody[0]->UpdateBase();
			ptr->FillCircle(newpos.x, newpos.y, 5, olc::CYAN);
			//player->update(ptr);
		}


		if (i == index)
		{

			Basepos = Mainpos;


			segment baseseg = thebody[1]->getSegment(0);
			bObjects[0]->position.x = Basepos.x;
			bObjects[0]->position.y = Basepos.y;
			bObjects[0]->rotation = baseseg.angle - 1.57;


			segment leadseg = thebody[1]->getSegment(1);

			bObjects[1]->position.x = leadseg.a.x;
			bObjects[1]->position.y = leadseg.a.y;



			float currentangle = leadseg.angle - 1.57;
			float minrange = -0.1;
			float maxrange = -0.5;
			float distX = leadseg.a.x - leadpos1.x;
			float distY = leadseg.a.y - leadpos1.y;
			float dx = distX * cos(currentangle);
			float dy = distX * sin(currentangle);

			if (currentangle > minrange)
			{


				bObjects[1]->rotation = minrange;
			}
			else if (currentangle < maxrange)
			{

				bObjects[1]->rotation = maxrange;
			}
			else
			{

				bObjects[1]->rotation = currentangle;

			}

			newpos = { (Mainpos.x) + leadpos1.x, (Mainpos.y + 180) + leadpos1.y };

			if (newpos.x < Mainpos.x - 30)
			{
				newpos.x = Mainpos.x - 30;

			}
			if (newpos.x > Mainpos.x + 30)
			{
				newpos.x = Mainpos.x + 30;
			}

			if (newpos.y < Mainpos.y + 160)
			{
				newpos.y = Mainpos.y + 160;
			}
			if (newpos.y > Mainpos.y + 180)
			{
				newpos.y = Mainpos.y + 180;
			}

			//bObjects[2]->rotation = inrange(leadseg.baseangle,leadseg.angle ,30);
			bObjects[2]->position.x = leadseg.b.x;
			bObjects[2]->position.y = leadseg.b.y;


			thebody[1]->addBase(bObjects[3]->position.x, bObjects[3]->position.y);
			thebody[1]->Update(newpos.x, newpos.y, true, 0);
			thebody[1]->UpdateBase();
			ptr->FillCircle(newpos.x, newpos.y, 5, olc::CYAN);
			//player->update(ptr);
		}
	}
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
	for(int i = 0; i < thebody.size() - 1;i++)
	{ 
	  thebody[i]->Render(ptr);
	}
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
