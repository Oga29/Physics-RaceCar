#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"
#include "Bullet/include/LinearMath/btVector3.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define JUMP_IMPULSE 1500.0f
#define JUMP_COOLDOWN 3.0f

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer2();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	btVector3 initialPosition;
	btVector3 currentPlayerPosition;

	float turn;
	float acceleration;
	float brake;
	int delay = 0;
	int seconds = 0;
	int minutes = 0;
	int lastSeconds = 0;
	int lastMinutes = 0;
	int NumberOfLaps = 0;
	bool winCondition = false;
	bool lapDone = false;
	bool lap1 = true;
	bool lap2 = false;
	bool lap3 = false;
	bool lap4 = false;
	bool inDirt = false;
	bool inIce = false;
	bool looseCondition = false;

private:

	Timer jump_coolddown;

	Timer break_timer;
};