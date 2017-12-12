
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

void ModuleSceneIntro::StartTerrain()
{
	Cube road1(20, 15, 150);
	road1.SetPos(0, 0, 0);
	roads.add(road1);

	Cube road2(150, 15, 20);
	road2.SetPos(65, 0, 85);
	roads.add(road2);

	Cube road3(25, 15, 75);
	road3.SetPos(127.5f, 0, 37.5f);
	roads.add(road3);

	Cube road4(75, 15, 20);
	road4.SetPos(102.5f, 0, -10);
	roads.add(road4);

	Cube road5(25, 15, 37.5f);
	road5.SetPos(77.5f, 0, -38.75f);
	roads.add(road5);

	Cube road6(150, 15, 20);
	road6.SetPos(140, 0, -67.5f);
	roads.add(road6);

	Cube road7(20, 15, 37.5f);
	road7.SetPos(205, 0, -96.25f);
	roads.add(road7);

	Cube road8(225, 15, 20);
	road8.SetPos(102.5f, 0, -125);
	roads.add(road8);

	//Here we will put the divided road & we have to change the road8 to the medium length

	Cube road12(20, 1, 40);
	road12.SetPos(0, 0, -95);
	roads.add(road12);

	for (p2List_item<Cube>* item = roads.getFirst(); item; item = item->next)
	{
		App->physics->AddBody(item->data, 0);
	}

}