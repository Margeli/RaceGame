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
		LOG("Hi");
	}
	if (body1->type == Floor)
	{
		//when the lower limit is hitted
	}
}

Cube ModuleSceneIntro::CreateFloor(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;

	roads.add(ret);

	App->physics->AddBody(ret, 0);
	return ret;
}

Cube ModuleSceneIntro::CreateTurboPart(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;

	roads.add(ret);

	PhysBody3D* pbody = App->physics->AddBody(ret, 0, SceneObjectType::Turbo);
	pbody->SetSensor();
	pbody->collision_listeners.add(this);

	return ret;
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

void ModuleSceneIntro::StartTerrain()
{
	Cube road1 = CreateRamp(20, ROAD_HEIGHT, 150, 0, 16.5f, 0.4f, 5, {1,0,0}, ROAD_COLOR);
	Cube road2 = CreateFloor(150, ROAD_HEIGHT, 20, 65, 10, 85);
	Cube road3 = CreateFloor(25, ROAD_HEIGHT, 75, 127.5f, 10, 37.5f);
	Cube road4 = CreateFloor(75, ROAD_HEIGHT, 20, 102.5f, 10, -10);
	Cube road5 = CreateFloor(25, ROAD_HEIGHT, 37.5f, 77.5f, 10, -38.75f);
	Cube road6 = CreateFloor(150, ROAD_HEIGHT, 20, 140, 10, -67.5f);
	Cube road7 = CreateFloor(20, ROAD_HEIGHT, 37.5f, 205, 10, -96.25f);
	Cube road8 = CreateFloor(112.5f, ROAD_HEIGHT, 20, 158.75f, 10, -125);
	Cube road9 = CreateFloor(75, ROAD_HEIGHT, 7.5f, 65, 10, -117.5f);
	Cube road10 = CreateFloor(75, ROAD_HEIGHT, 7.5f, 65, 10, -132.5f);
	Cube road11 = CreateFloor(37.5f, ROAD_HEIGHT, 20, 8.75f, 10, -125);
	Cube road12 = CreateRamp(20, ROAD_HEIGHT, 42.5f, 0, 16.5f, -94,19.3, { -1,0,0 }, ROAD_COLOR);
	Cube ramp1 = CreateRamp(20, ROAD_HEIGHT, 10, 130, 10.5, -24,7, { 1,0,0 });//Mini ramp to jump

	Cube turbo1 = CreateTurboPart(10, ROAD_HEIGHT, 20, 65, 10.2f, 85);

	Cube dark_floor = CreateLowerLimit(1000, 1, 1000, 0, 7.5f, 0)
	
}