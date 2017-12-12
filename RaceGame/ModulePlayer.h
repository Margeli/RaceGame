#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 550.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	btVector3 getPos() const;//Get axis of orientation of the player
	vec3 getAxisX() const;
	vec3 getAxisY() const;
	vec3 getAxisZ() const;

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};