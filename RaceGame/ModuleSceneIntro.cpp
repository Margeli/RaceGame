#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleAudio.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	App->audio->PlayMusic("audio/music.ogg");
	turbo_fx = App->audio->LoadFx("audio/turbo.wav");
	StartTerrain();
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	dark_floor.Render();
	for (p2List_item<Cube>* item = roads.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == Turbo)
	{
		App->audio->PlayFx(turbo_fx);
		App->player->turbo = true;
	}
	else if (body1->type == Floor)
	{
		App->player->RespawnCar();		
	}
	else if (body1->type == LapSensor)
	{
		App->player->half_lap_done = true;
	}
	else if (body1->type == Goal)
	{
		App->player->LapCompleted();
	}
}

Cube ModuleSceneIntro::CreateNormalFloor(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;

	roads.add(ret);

	App->physics->AddBody(ret, 0);
	return ret;
}

Cube ModuleSceneIntro::CreateFloorAndWalls(float width, float height, float large, float x, float y, float z, bool wallLeft, bool wallRight, bool wallTop, bool wallBack, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;

	roads.add(ret);

	if (wallLeft)
	{
		if (width > large)
		{
			Cube LeftWall(width, 3, 1);
			LeftWall.SetPos(x, y, (z -  large / 2) );
			LeftWall.color = color;
			roads.add(LeftWall);
			App->physics->AddBody(LeftWall, 0);
		}

		else if (width < large)
		{
			Cube LeftWall(1, 3, large);
			LeftWall.SetPos((x - width / 2), y, z);
			LeftWall.color = color;
			roads.add(LeftWall);
			App->physics->AddBody(LeftWall, 0);
		}
	}

	if (wallRight)
	{
		if (width > large)
		{
			Cube RightWall(width, 3, 1);
			RightWall.SetPos(x, y, (z + large / 2));
			RightWall.color = color;
			roads.add(RightWall);
			App->physics->AddBody(RightWall, 0);
		}

		else if (width < large)
		{
			Cube RightWall(1, 3, large);
			RightWall.SetPos((x + width / 2), y, z);
			RightWall.color = color;
			roads.add(RightWall);
			App->physics->AddBody(RightWall, 0);
		}

	}

	App->physics->AddBody(ret, 0);
	return ret;
}

Cube ModuleSceneIntro::CreateTurboPart(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube turbo(width, height, large);
	turbo.SetPos(x, y, z);
	turbo.color = color;

	roads.add(turbo);
	Cube turbosensor = turbo;
	turbosensor.SetPos(x, y + 1.5f, z);

	PhysBody3D* pbody = App->physics->AddBody(turbosensor, 0, SceneObjectType::Turbo);
	pbody->SetSensor();
	pbody->collision_listeners.add(this);

	return turbo;
}

Cube ModuleSceneIntro::CreateRamp(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;
	ret.SetRotation(degree, axis);

	roads.add(ret);

	App->physics->AddBody(ret, 0);
	return ret;

}
Cube ModuleSceneIntro::CreateLowerLimit(float width, float height, float large, float x, float y, float z, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;
	

	roads.add(ret);

	PhysBody3D* pbody = App->physics->AddBody(ret, 0, SceneObjectType::Floor);
	pbody->SetSensor();
	pbody->collision_listeners.add(this);

	return ret;

}
Cube ModuleSceneIntro::CreateLapSensor(float x, float y, float z, bool isgoal) {

	Cube ret(20, 20, 0.3f);
	ret.SetPos(x, y, z);

	SceneObjectType type;

	if (isgoal) {
		type = Goal;
	}
	else {
		type = LapSensor;
	}
	PhysBody3D* pbody = App->physics->AddBody(ret, 0, type);

	pbody->SetSensor();
	pbody->collision_listeners.add(this);

	return ret;
}

void ModuleSceneIntro::StartTerrain()
{
	Cube road1 = CreateRamp(20, ROAD_HEIGHT, 150, 0, 15.30f, 0.4f, 4.1f, {1,0,0}, ROAD_COLOR);
	Cube road2 = CreateFloorAndWalls(150, ROAD_HEIGHT, 20, 65, 10, 85, false, true);
	Cube road3 = CreateFloorAndWalls(25, ROAD_HEIGHT, 75, 127.5f, 10, 37.5f, true);
	Cube road4 = CreateNormalFloor(75, ROAD_HEIGHT, 20, 102.5f, 10, -10);
	Cube road5 = CreateNormalFloor(25, ROAD_HEIGHT, 37.5f, 77.5f, 10, -38.75f);
	Cube road6 = CreateNormalFloor(150, ROAD_HEIGHT, 20, 140, 10, -67.5f);
	Cube road7 = CreateNormalFloor(20, ROAD_HEIGHT, 37.5f, 205, 10, -96.25f);
	Cube road8 = CreateNormalFloor(112.5f, ROAD_HEIGHT, 20, 158.75f, 10, -125);
	Cube road9 = CreateNormalFloor(75, ROAD_HEIGHT, 7.5f, 65, 10, -117.5f);
	Cube road10 = CreateNormalFloor(75, ROAD_HEIGHT, 7.5f, 65, 10, -132.5f);
	Cube road11 = CreateNormalFloor(37.5f, ROAD_HEIGHT, 20, 8.75f, 10, -125);
	Cube road12 = CreateRamp(20, ROAD_HEIGHT, 42.2f, 0, 15.3f, -94.8f ,14.6f, { -1,0,0 }, ROAD_COLOR);
	Cube ramp1 = CreateRamp(20, ROAD_HEIGHT, 10, 130, 10.5, -24,7, { 1,0,0 });//Mini ramp to jump

	Cube turbo1 = CreateTurboPart(5, ROAD_HEIGHT, 20, 65, 10.2f, 85);

	Cube sensor1 = CreateLapSensor( 127.5f, 10, 37.5f);
	Cube goal = CreateLapSensor(0, 20, 0, true);

	Cube dark_floor = CreateLowerLimit(1000, 1, 1000, 0, 4.5f, 0);	
}

