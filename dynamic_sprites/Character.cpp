#include "Character.h"

Limb::Limb(olc::vf2d origin, float l1, float l2, bool inverseJoint)
{
	this->p1 = origin;
	this->l1 = l1;
	this->l2 = l2;
	this->inverseJoint = inverseJoint;
}

Human_Skeleton::Human_Skeleton(olc::vf2d p)
{
	NormalStance(p);
}

void Human_Skeleton::NormalStance(olc::vf2d p)
{
	head = { 0.0f, -14.0f };
	neck = { 0.0f, 0.0f };
	left_shoulder = { -10.0f, 2.0f };
	right_shoulder = { 10.0f, 2.0f };
	left_hand = { -12.0f, 30.0f };
	right_hand = { 12.0f, 30.0f };
	hip_bone = { 0.0f, 26.0f };
	left_hip = { -8.0f, 28.0f };
	right_hip = { 8.0f, 28.0f };
	left_foot = { -8.0f, 58.0f };
	right_foot = { 8.0f, 58.0f };
}

Character::Character(olc::vf2d p)
{
	this->p = p;
	left_arm = Limb(skeleton.left_shoulder, 16.0f, 12.0f, true);
	right_arm = Limb(skeleton.right_shoulder, 16.0f, 12.0f, false);
	left_leg = Limb(skeleton.left_hip, 16.0f, 14.0f, false);
	right_leg = Limb(skeleton.right_hip, 16.0f, 14.0f, true);
}

Kinematics::Kinematics(olc::PixelGameEngine* pge)
{
	player = new Character({ 300, 200 });
}

void Kinematics::FKAL(Limb& limb, olc::vf2d target)
{
	std::vector<olc::vf2d> calculatedPoints;

	olc::vf2d diff = target - limb.p1;

	//get l
	float length = (float)sqrt((diff.x * diff.x) + (diff.y * diff.y));

	//get a		
	float a = acos(std::clamp((limb.l1 * limb.l1 + limb.l2 * limb.l2 - length * length) / (2 * limb.l1 * limb.l2), -1.0f, 1.0f));

	//get b
	float b = acos(std::clamp((limb.l1 * limb.l1 + length * length - limb.l2 * limb.l2) / (2 * limb.l1 * length), -1.0f, 1.0f));

	if (limb.inverseJoint) {
		a = -a;
		b = -b;
	}

	//get c
	float c = atan2(diff.y, diff.x);

	//Recombine a, b, c into usable x,y coords

	float limb_1_angle = b + c;
	float limb_2_angle = 3.14f + (a + b + c);

	limb.a1 = limb_1_angle;
	limb.a2 = limb_2_angle;

	limb.p2 = limb.p1 + polarToCartesian(limb_1_angle, limb.l1);

	limb.p3 = limb.p2 + polarToCartesian(limb_2_angle, limb.l2);
}

olc::vf2d Kinematics::polarToCartesian(float angle, float distance)
{
	float x = distance * cos(angle);
	float y = distance * sin(angle);
	return { x, y };
}

bool Kinematics::IsPointInCircle(olc::vf2d a, olc::vf2d b, float r)
{
	return fabs((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) < (r * r);
}

void Kinematics::IsJointSelected(olc::PixelGameEngine* pge)
{
	if (IsPointInCircle(player->left_arm.p3 + player->p, pge->GetMousePos()))
		selectedJoint = &player->skeleton.left_hand;
	else if (IsPointInCircle(player->right_arm.p3 + player->p, pge->GetMousePos()))
		selectedJoint = &player->skeleton.right_hand;
	else if (IsPointInCircle(player->left_leg.p3 + player->p, pge->GetMousePos()))
		selectedJoint = &player->skeleton.left_foot;
	else if (IsPointInCircle(player->right_leg.p3 + player->p, pge->GetMousePos()))
		selectedJoint = &player->skeleton.right_foot;
	else
		selectedJoint = nullptr;
}

void Kinematics::DrawCharacter(Character* c, olc::PixelGameEngine* pge)
{
	float r = 5.0f;

	pge->DrawCircle(c->p + c->skeleton.head, r);
	pge->DrawCircle(c->p + c->skeleton.left_hand, r);
	pge->DrawCircle(c->p + c->skeleton.right_hand, r);
	pge->DrawCircle(c->p + c->skeleton.left_foot, r);
	pge->DrawCircle(c->p + c->skeleton.right_foot, r);
    pge->DrawLine(c->p + c->skeleton.head, c->p + c->skeleton.neck, olc::YELLOW);
	pge->DrawLine(c->p + c->skeleton.left_shoulder, c->p + c->skeleton.neck, olc::YELLOW);
	pge->DrawLine(c->p + c->skeleton.right_shoulder, c->p + c->skeleton.neck, olc::YELLOW);
	pge->DrawLine(c->p + c->skeleton.hip_bone, c->p + c->skeleton.neck, olc::YELLOW);
	pge->DrawLine(c->p + c->skeleton.hip_bone, c->p + c->skeleton.left_hip, olc::YELLOW);
	pge->DrawLine(c->p + c->skeleton.hip_bone, c->p + c->skeleton.right_hip, olc::YELLOW);
	pge->DrawLine(c->p + c->left_arm.p1, c->p + c->left_arm.p2, olc::BLUE);
	pge->DrawLine(c->p + c->left_arm.p2, c->p + c->left_arm.p3, olc::BLUE);
    pge->DrawLine(c->p + c->right_arm.p1, c->p + c->right_arm.p2, olc::BLUE);
	pge->DrawLine(c->p + c->right_arm.p2, c->p + c->right_arm.p3, olc::BLUE);
    pge->DrawLine(c->p + c->left_leg.p1, c->p + c->left_leg.p2, olc::BLUE);
	pge->DrawLine(c->p + c->left_leg.p2, c->p + c->left_leg.p3, olc::BLUE);
    pge->DrawLine(c->p + c->right_leg.p1, c->p + c->right_leg.p2, olc::BLUE);
	pge->DrawLine(c->p + c->right_leg.p2, c->p + c->right_leg.p3, olc::BLUE);
}

void Kinematics::setup(olc::PixelGameEngine* pge)
{
	
	
}

void Kinematics::update(olc::PixelGameEngine* pge)
{
	FKAL(player->left_arm, player->skeleton.left_hand);
	pge->DrawString(20, 20, "p1x: " + std::to_string(player->left_arm.p1.x) + "ply: " +std::to_string(player->left_arm.p1.y));
	pge->DrawString(20, 30, "p2x: " + std::to_string(player->left_arm.p2.x) + "p2y: " + std::to_string(player->left_arm.p2.y));
	pge->DrawString(20, 40, "p3x: " + std::to_string(player->left_arm.p3.x) + "p3y: " + std::to_string(player->left_arm.p3.y));
	FKAL(player->right_arm, player->skeleton.right_hand);
	FKAL(player->left_leg, player->skeleton.left_foot);
	FKAL(player->right_leg, player->skeleton.right_foot);

	if (pge->GetKey(olc::UP).bHeld)
	{
		player->p.y -= 0.01f;
	}

	if (pge->GetKey(olc::DOWN).bHeld)
	{
		player->p.y += 0.01f;
	}

	if (pge->GetKey(olc::LEFT).bHeld)
	{
		player->p.x -= 0.01f;
		player->viewDir = -1;
	}

	if (pge->GetKey(olc::RIGHT).bHeld)
	{
		player->p.x += 0.01f;
		player->viewDir = 1;
	}
	if (pge->GetMouse(0).bPressed) {
		IsJointSelected(pge);
	}

	if (pge->GetMouse(0).bHeld) {
		if (selectedJoint != nullptr) {
			selectedJoint->x = pge->GetMouseX() - player->p.x;
			selectedJoint->y = pge->GetMouseY() - player->p.y;
		}
	}

}

void Kinematics::render(olc::PixelGameEngine* pge)
{
	DrawCharacter(player, pge);
}
