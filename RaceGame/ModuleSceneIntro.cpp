
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
	Cube road1(20, 15, 150);	road1.SetPos(0, 0, 0);				road1.color = Grey;		roads.add(road1);

	Cube road2(150, 15, 20);	road2.SetPos(65, 0, 85);			road2.color = Grey;		roads.add(road2);

	Cube road3(25, 15, 75);		road3.SetPos(127.5f, 0, 37.5f);		road3.color = Grey;		roads.add(road3);

	Cube road4(75, 15, 20);		road4.SetPos(102.5f, 0, -10);		road4.color = Grey;		roads.add(road4);

	Cube road5(25, 15, 37.5f);	road5.SetPos(77.5f, 0, -38.75f);	road5.color = Grey;		roads.add(road5);

	Cube road6(150, 15, 20);	road6.SetPos(140, 0, -67.5f);		road6.color = Grey;		roads.add(road6);

	Cube road7(20, 15, 37.5f);	road7.SetPos(205, 0, -96.25f);		road7.color = Grey;		roads.add(road7);

	Cube road8(112.5f, 15, 20);	road8.SetPos(158.75f, 0, -125);		road8.color = Grey;		roads.add(road8);

	Cube road9(75, 15, 7.5f);	road9.SetPos(65, 0, -117.5f);		road9.color = Grey;		roads.add(road9);

	Cube road10(75, 15, 7.5f);	road10.SetPos(65, 0, -132.5f);		road10.color = Grey;	roads.add(road10);
			
	Cube road11(37.5f, 15, 20);	road11.SetPos(8.75f, 0, -125);		road11.color = Grey;	roads.add(road11);

	Cube road12(20, 15, 40);	road12.SetPos(0, 0, -95);			road12.color = Grey;	roads.add(road12);

	//Borders of road
	/*Cube border1(2, 18, 230);	border1.SetPos(-11, 0, -20);		border1.color = Grey;	roads.add(border1);
*/
	Cube test(20, 15, 200);		test.SetPos(-20, 0, 0);				test.SetRotation(-5, {1, 0, 0});		roads.add(test);

	for (p2List_item<Cube>* item = roads.getFirst(); item; item = item->next)
	{
		App->physics->AddBody(item->data, 0);
	}


}