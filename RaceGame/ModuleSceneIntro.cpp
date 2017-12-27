#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

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

	for (p2List_item<Cube>* item = roads.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
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

void ModuleSceneIntro::StartTerrain()
{
	Cube road1 = CreateFloor(20, 15, 150, 0, 0, 0, Grey);
	Cube road2 = CreateFloor(150, 15, 20, 65, 0, 85, Grey);
	Cube road3 = CreateFloor(25, 15, 75, 127.5f, 0, 37.5f, Grey);
	Cube road4 = CreateFloor(75, 15, 20, 102.5f, 0, -10, Grey);
	Cube road5 = CreateFloor(25, 15, 37.5f, 77.5f, 0, -38.75f, Grey);
	Cube road6 = CreateFloor(150, 15, 20, 140, 0, -67.5f, Grey);
	Cube road7 = CreateFloor(20, 15, 37.5f, 205, 0, -96.25f, Grey);
	Cube road8 = CreateFloor(112.5f, 15, 20, 158.75f, 0, -125, Grey);
	Cube road9 = CreateFloor(75, 15, 7.5f, 65, 0, -117.5f, Grey);
	Cube road10 = CreateFloor(75, 15, 7.5f, 65, 0, -132.5f, Grey);
	Cube road11 = CreateFloor(37.5f, 15, 20, 8.75f, 0, -125, Grey);
	Cube road12 = CreateFloor(20, 15, 40, 0, 0, -95, Grey);

}