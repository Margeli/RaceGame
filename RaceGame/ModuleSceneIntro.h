#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define ROAD_COLOR Grey
#define RAMP_COLOR Yellow
#define ROAD_HEIGHT 0.1f

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();



	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	Cube CreateFloor(float width, float height, float large, float x, float y, float z, Color color = ROAD_COLOR);
	Cube CreateTurboPart(float width, float height, float large, float x, float y, float z, Color color = Orange);
	Cube CreateRamp(float width, float height, float large, float x, float y, float z,float degree,  vec3 axis, Color color = RAMP_COLOR);
	void StartTerrain();

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube dark_floor;
	p2List<Cube> roads;
	
};
