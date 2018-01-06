#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURBO_ACCELERATION 8000.0f
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

	bool turbo = false;
	
	void InitialPos() const;//car spawns to the initial pos
	void RespawnCar() ;
	void LapCompleted();
	void Win();
	
	mutable Timer timer;
	uint current_laps=1;
	bool half_lap_done = false;
	bool input = true;

public:

	uint brakes_fx;
	//uint moving_backwards_fx; TOO REPETITIVE
	uint accelerating_fx;

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};