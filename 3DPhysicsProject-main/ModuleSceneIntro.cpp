#include "Globals.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "PhysVehicle3D.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Color.h"

#include <stdio.h>
//#include "Color.cpp"

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

	Mix_ResumeMusic();
	Mix_SetMusicPosition(0);
	// Load music
    App->audio->PlayMusic("Assets/Get_Low.wav");

	App->camera->Move(vec3(0.0f, 4.0f, -12.0f));
	App->camera->LookAt(vec3(0, 3, 0));

    // Lap barrier
    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 15.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Barrier_Lap_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 15.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Barrier_Lap_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 15.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Barrier_Lap_T", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 15.0f), vec3(32.0f, 500.0f, 0.5f), White, 0, "Barrier_Lap_Sensor", true));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 1340.0f), vec3(32.0f, 500.0f, 2.0f), White, 0, "Barrier_Lap_Sensor_Activator", true));

    // General setup
    geometryList.add(CreateRamp(vec3(0.0f, 0.0f, -120.0f), vec3(30.0f, 1.0f, 25.0f), Red, -15.0f, { 1,0,0 }, "Ramp_Obstacle", 0, false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, -390.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part -1", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, -140.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 0", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 110.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 1", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 360.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 2", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 610.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 3", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 860.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 4", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1110.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 5", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, -1000.0f), vec3(30.0f, 10.0f, 10000.0f), White, 0, "GroundSensor", true));
    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 1470.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Barrier_Lap_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 1470.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Barrier_Lap_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 1470.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Barrier_Lap_T", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1360.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 6", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1610.0f), vec3(30.0f, 0.0f, 250.0f), White, 0, "Ground Part 7", false));

    geometryList.add(CreateCube(vec3(-15.0f, 0.0f, 465.0f), vec3(1.0f, 6.5f, 2560.0f), Black, 0, "Left_Railing", false));
    geometryList.add(CreateCube(vec3(15.0f, 0.0f, 465.0f), vec3(1.0f, 6.5f, 2560.0f), Black, 0, "Right_Railing", false));

   

    // Teleports
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, -110.0f), vec3(30.0f, 500.6f, 2.0f), Black, 0, "Portal_Beggining", true));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1360.0f), vec3(30.0f, 500.6f, 2.0f), Black, 0, "Portal_End", true));

    // Obstacles
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 100.0f), vec3(30.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 110.0f), vec3(30.0f, 0.7f, 15.0f), Blue, 0, "Ice_Speeder", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 110.0f), vec3(30.0f, 500.0f, 15.0f), Blue, 0, "Ice_Speeder_Sensor", true));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 210.0f), vec3(30.0f, 0.7f, 35.0f), Blue, 0, "Ice_Speeder", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 210.0f), vec3(30.0f, 500.0f, 35.0f), Blue, 0, "Ice_Speeder_Sensor", true));

    geometryList.add(CreateCube(vec3(-5.0f, 0.0f, 320.0f), vec3(15.0f, 0.7f, 50.0f), Orange, 0, "Dirt_Slower", false));
    geometryList.add(CreateCube(vec3(-5.0f, 0.0f, 320.0f), vec3(15.0f, 500.0f, 50.0f), Orange, 0, "Dirt_Slower_Sensor", true));

    geometryList.add(CreateCube(vec3(10.0f, 0.0f, 320.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1210.0f), vec3(30.0f, 0.7f, 15.0f), Orange, 0, "Dirt_Slower", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 1210.0f), vec3(30.0f, 500.0f, 15.0f), Orange, 0, "Dirt_Slower_Sensor", true));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 865.0f), vec3(30.0f, 0.5f, 10.0f), Orange, 0, "Dirt_Slower", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 865.0f), vec3(30.0f, 500.0f, 10.0f), Orange, 0, "Dirt_Slower_Sensor", true));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 470.0f), vec3(30.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));
    geometryList.add(CreateCube(vec3(4.5f, 0.0f, 470.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-4.5f, 0.0f, 470.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(12.5f, 0.0f, 470.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-12.5f, 0.0f, 470.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));

    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 650.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));
    geometryList.add(CreateCube(vec3(10.0f, 0.0f, 650.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 670.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 690.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));
    geometryList.add(CreateCube(vec3(10.0f, 0.0f, 690.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 720.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    //geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 740.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));
    //geometryList.add(CreateCube(vec3(10.0f, 0.0f, 740.0f), vec3(10.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));

    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 856.0f), vec3(30.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));
  
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 876.0f), vec3(30.0f, 5.6f, 2.0f), Black, 0, "Barrier_Obstacle", false));


    geometryList.add(CreateCube(vec3(20.0f, 0.0f, 50.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-22.0f, 0.0f, 80.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(47.0f, 0.0f, 110.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 120.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(50.0f, 0.0f, 150.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-27.0f, 0.0f, 170.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-7.0f, 0.0f, 140.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(10.0f, 0.0f, 250.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 200.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-31.0f, 0.0f, 240.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(25.0f, 0.0f, 300.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-50.0f, 0.0f, 320.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 350.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 400.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(45.0f, 0.0f, 420.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(5.0f, 0.0f, 420.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-5.0f, 0.0f, 480.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(50.0f, 0.0f, 520.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(45.0f, 0.0f, 580.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-30.0f, 0.0f, 620.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(12.0f, 0.0f, 610.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(40.0f, 0.0f, 680.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-12.0f, 0.0f, 700.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(0.0f, 0.0f, 750.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-50.0f, 0.0f, 800.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(40.0f, 0.0f, 820.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(2.0f, 0.0f, 840.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-2.0f, 0.0f, 870.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-56.0f, 0.0f, 900.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(56.0f, 0.0f, 930.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-56.0f, 0.0f, 900.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 970.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(45.0f, 0.0f, 950.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-35.0f, 0.0f, 1000.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(40.0f, 0.0f, 1250.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(8.0f, 0.0f, 1030.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 1080.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(12.0f, 0.0f, 1110.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-4.0f, 0.0f, 1190.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 1250.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-20.0f, 0.0f, 1290.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(25.0f, 0.0f, 1320.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(30.0f, 0.0f, 1330.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-35.0f, 0.0f, 1340.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));



    geometryList.add(CreateCube(vec3(20.0f, 0.0f, 50.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-22.0f, 0.0f, 80.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(47.0f, 0.0f, 110.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 120.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(50.0f, 0.0f, 150.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-27.0f, 0.0f, 170.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-7.0f, 0.0f, 140.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(10.0f, 0.0f, 250.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 200.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-31.0f, 0.0f, 240.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(25.0f, 0.0f, 300.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-50.0f, 0.0f, 320.0f + 1360.0f + 95.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 1055.0f - 1360.0f - 62.0f), vec3(2.0f, 10.0f, 165.0f), Dark_Grey, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 1055.0f - 1360.0f - 62.0f), vec3(2.0f, 10.0f, 165.0f), Dark_Grey, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 1055.0f - 1360.0f - 62.0f), vec3(32.0f, 2.0f, 165.0f), Dark_Grey, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-2.0f, 0.0f, 870.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-56.0f, 0.0f, 900.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(56.0f, 0.0f, 930.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-56.0f, 0.0f, 900.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 970.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(45.0f, 0.0f, 965.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-35.0f, 0.0f, 1000.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(40.0f, 0.0f, 1265.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(8.0f, 0.0f, 1030.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-10.0f, 0.0f, 1080.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(12.0f, 0.0f, 1110.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-4.0f, 0.0f, 1190.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-40.0f, 0.0f, 1265.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-20.0f, 0.0f, 1290.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(25.0f, 0.0f, 1320.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(30.0f, 0.0f, 1330.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));
    geometryList.add(CreateCube(vec3(-35.0f, 0.0f, 1340.0f - 1360.0f - 62.0f), vec3(4.0f, 100.6f, 4.0f), Black, 0, "Column_Obstacle", false));

    geometryList.add(CreateRamp(vec3(0.0f, 0.0f, 1300.0f), vec3(30.0f, 1.0f, 25.0f), Red, -15.0f, {1,0,0}, "Ramp_Obstacle", 0, false));

    // Decoration
    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 900.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 900.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 900.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 920.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 920.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 920.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 940.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 940.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 940.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 960.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 960.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 960.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 980.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 980.0f), vec3(2.0f, 10.0f, 2.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 980.0f), vec3(32.0f, 2.0f, 2.0f), White, 0, "Deco_Tunel_T", false));

    geometryList.add(CreateCube(vec3(-15.0f, 5.0f, 1055.0f), vec3(2.0f, 10.0f, 150.0f), White, 0, "Deco_Tunel_L", false));
    geometryList.add(CreateCube(vec3(15.0f, 5.0f, 1055.0f), vec3(2.0f, 10.0f, 150.0f), White, 0, "Deco_Tunel_R", false));
    geometryList.add(CreateCube(vec3(0.0f, 11.0f, 1055.0f), vec3(32.0f, 2.0f, 150.0f), White, 0, "Deco_Tunel_T", false));

	//geometryList.add(CreateCube(vec3(-181.0f, 6.5f, -411.212f), vec3(1.0f, 13.0f, 815.0f), Blue, 0, "wall1"));
	//geometryList.add(CreateCube(vec3(-151.028f, 6.5f, -394.152f), vec3(1.0f, 13.0f, 719.176f), Blue, 0, "wall2"));
    
    lap = App->audio->LoadFx("Assets/checkpoint.wav");
    gameEndWin = App->audio->LoadFx("Assets/end.wav");
    gameEndLoose = App->audio->LoadFx("Assets/endLoose.wav");
    countDown = App->audio->LoadFx("Assets/Mario_Kart_Countdown.wav");
    //jump = App->audio->LoadFx("Assets/countdown.wav");

    sceneBeginTimer = 0;
    sceneEndTimer = 0;

    trueLooseCondition = false;
    countDownTimer = 18820;

    vehicleIndex = 1;

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
    countDownTimer--;

    sceneBeginTimer++;
    if (App->player->winCondition == true || App->player->looseCondition == true) sceneEndTimer++;
    if (App->player2->winCondition == true || App->player2->looseCondition == true) sceneEndTimer++;

	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
    if (sceneBeginTimer <= 1) App->audio->PlayFx(countDown);

    if (sceneEndTimer > 1 && sceneEndTimer <= 3) App->audio->PlayFx(gameEndWin);

    if (sceneBeginTimer <= 240)
    {
        /* //This feature of switching vehicles is finally removed
        if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && vehicleIndex != 1)
        {
            App->player->vehicle->SetPos(App->player2->currentPlayerPosition.x(), App->player2->currentPlayerPosition.y(), App->player2->currentPlayerPosition.z());
            App->player->vehicle->SetLinearVelocity(0, 0, 0);

            vehicleIndex = 1;
        }
        if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && vehicleIndex != 2)
        {
            App->player2->vehicle->SetPos(App->player->currentPlayerPosition.x(), App->player->currentPlayerPosition.y(), App->player->currentPlayerPosition.z());
            App->player2->vehicle->SetLinearVelocity(0, 0, 0);

            vehicleIndex = 2;
        }
        */
    }

    if (countDownTimer <= 0)
    {
        Mix_PauseMusic();
        if(App->player->winCondition == false && App->player2->winCondition == false) trueLooseCondition = true;

        if(countDownTimer < 0 && countDownTimer >= -1 && trueLooseCondition == true) App->audio->PlayFx(gameEndLoose);
    }

    display(dt);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
    if (body1->IsSensor())
    {
        LOG("Body1: Im a sensor my name is %s", body1->name.GetString());

    }
    else if (body2->IsSensor())
    {
        LOG("Body2: Im a sensor my name is %s", body2->name.GetString());

        // Example
        /*
        if (body2->name == "loopsensor1")
        {
            swapCamera = true;
        }
        */

        if (body2->name == "Barrier_Lap_Sensor_Activator")
        {
            lapSensorActivated = true;
        }

        if (body2->name == "Barrier_Lap_Sensor")
        {
            if (lapSensorActivated == true)
            {
                App->player->lapDone = true;
                //App->player2->lapDone = true;
                lapSensorActivated = false;

                App->audio->PlayFx(lap);
            }
        }

        if (body2->name == "Dirt_Slower_Sensor")
        {
            App->player->inDirt = true;
            App->player2->inDirt = true;
        }
        if (body2->name == "GroundSensor")
        {
            App->player->inDirt = false;
            App->player2->inDirt = false;
        }
        if (body2->name == "Ice_Speeder_Sensor")
        {
            App->player->inIce = true;
            App->player2->inIce = true;
        }
        if (body2->name == "iceSensor")
        {
            App->player->inIce = false;
            App->player2->inIce = false;
        }

        if (body2->name == "Portal_End")
        {
            App->player->vehicle->SetPos(App->player->currentPlayerPosition.x(), App->player->currentPlayerPosition.y(), -95);
            App->player2->vehicle->SetPos(App->player->currentPlayerPosition.x(), App->player->currentPlayerPosition.y(), -95);
        }
        if (body2->name == "Portal_Beggining")
        {
            App->player->vehicle->SetPos(App->player->currentPlayerPosition.x(), App->player->currentPlayerPosition.y(), 1315);
            App->player2->vehicle->SetPos(App->player->currentPlayerPosition.x(), App->player->currentPlayerPosition.y(), 1315);
        }
    }

    if (body2->name == "Ground Part -1")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
        

    }
    if (body2->name == "Ground Part 0")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
       
    }
    if (body2->name == "Ground Part 1")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
       
    }
    if (body2->name == "Ground Part 2")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
     
    }
    if (body2->name == "Ground Part 3")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
       
    }
    if (body2->name == "Ground Part 4")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
       
    }
    if (body2->name == "Ground Part 5")
    {
        App->player->inDirt = false;
        App->player2->inDirt = false;
        
    }
}

Cylinder* ModuleSceneIntro::CreateCylinder(vec3 pos, vec2 heightandAngle, Color rgb, float angle, vec3 pivot, float mass, SString name, bool isSensor) // No sirve
{
    Cylinder* cylinder = new Cylinder();
    cylinder->SetRotation(angle, pivot);
    cylinder->SetPos(pos.x, pos.y, pos.z);
    cylinder->height = heightandAngle.x;
    cylinder->radius = heightandAngle.y;
    cylinder->color = rgb;
    physBodies.add(App->physics->AddBodySimpleCylinder(*cylinder, mass));

    return cylinder;
}

Cube* ModuleSceneIntro::CreateCube(vec3 pos, vec3 size, Color rgb, float mass, SString name, bool isSensor)
{
	Cube* cube = new Cube();
	cube->SetPos(pos.x, pos.y, pos.z);
	cube->size = size;
	cube->color = rgb;

	physBodies.add(App->physics->AddBodyV2(*cube, mass, isSensor, name));

	return cube;
}

Cube* ModuleSceneIntro::CreateRamp(vec3 pos, vec3 size, Color rgb, float angle, vec3 pivot, SString name, float mass, bool isSensor)
{
	Cube* cube = new Cube();
	cube->SetRotation(angle, pivot);
	cube->SetPos(pos.x, pos.y, pos.z);
	cube->size = size;
	cube->color = rgb;
	physBodies.add(App->physics->AddBodyV2(*cube, mass, isSensor, name));

	return cube;
}

void ModuleSceneIntro::Circuit(int* lvlcircuit, int* circuitx, int poscircuit)
{

	//create sensors
	if (pb_limits.Count() != 0 && s_limits.Count() != 0 && s_limits.Count() == pb_limits.Count())
	{
		for (int i = 0; i < s_limits.Count(); i++)
		{
			pb_limits[i]->SetAsSensor(true);
			pb_limits[i]->collision_listeners.add(this);
		}

		for (int i = 0; i < s_endlvl.Count(); i++)
		{
			pb_endlvl[i]->SetAsSensor(true);
			pb_endlvl[i]->collision_listeners.add(this);
		}
	}
}

void ModuleSceneIntro::display(float dt)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glBindTexture(GL_TEXTURE_2D, texture[1]);

    glDisable(GL_TEXTURE_2D);

    //Plane p(0, 1, 0, 0);
    //p.axis = true;
    //p.Render();

    //l.Render();

    Cube trafficLight1(4.0f, 4.0f, 4.0f);
    trafficLight1.SetPos(6.0f, 8.0f, 15.0f);
    trafficLight1.axis = false;

    Cube trafficLight2(4.0f, 4.0f, 4.0f);
    trafficLight2.SetPos(0.0f, 8.0f, 15.0f);
    trafficLight2.axis = false;

    Cube trafficLight3(4.0f, 4.0f, 4.0f);
    trafficLight3.SetPos(-6.0f, 8.0f, 15.0f);
    trafficLight3.axis = false;
    

    if (sceneBeginTimer <= 1)
    {
        trafficLight1.color = Dark_Grey;
        trafficLight2.color = Dark_Grey;
        trafficLight3.color = Dark_Grey;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (sceneBeginTimer <= 60)
    {
        trafficLight1.color = Red;
        trafficLight2.color = Dark_Grey;
        trafficLight3.color = Dark_Grey;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (sceneBeginTimer <= 120)
    {
        trafficLight1.color = Red;
        trafficLight2.color = Red;
        trafficLight3.color = Dark_Grey;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (sceneBeginTimer <= 180)
    {
        trafficLight1.color = Red;
        trafficLight2.color = Red;
        trafficLight3.color = Red;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (sceneBeginTimer <= 240)
    {
        trafficLight1.color = Green;
        trafficLight2.color = Green;
        trafficLight3.color = Green;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (sceneBeginTimer > 240)
    {
        trafficLight1.color = Green;
        trafficLight2.color = Green;
        trafficLight3.color = Green;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }
    else if (App->player->winCondition == true || App->player->looseCondition == true || App->player2->winCondition == true || App->player2->looseCondition == true)
    {
        trafficLight1.color = Blue;
        trafficLight2.color = Blue;
        trafficLight3.color = Blue;

        trafficLight1.Render();
        trafficLight2.Render();
        trafficLight3.Render();
    }

    p2List_item<Cube*>* itemCubes = geometryList.getFirst();

    p2List_item<PhysBody3D*>* itemBodies = physBodies.getFirst();

    while (itemBodies != nullptr && itemCubes != nullptr)
    {
        if ((itemBodies->data->IsSensor() != true || itemBodies->data->name == "turbo") && itemBodies->data->name != "Inv_Limit")
        {
            itemCubes->data->Render();
        }
        itemBodies->data->GetTransform(&itemCubes->data->transform);
        itemCubes = itemCubes->next;
        itemBodies = itemBodies->next;
    }

    itemCubes = geometryList.getFirst();
    itemBodies = physBodies.getFirst();
    while (itemBodies != nullptr && itemCubes != nullptr)
    {
        if (itemBodies->data->name == "turbo")
        {
            //itemCubes->data->transform.rotate(angleTurbo, vec3(0.0f, 1.0f, 1.0f));
        }
        itemCubes = itemCubes->next;
        itemBodies = itemBodies->next;
    }
    //angleTurbo += 100.0f * dt;

    itemCubes = lights.getFirst();
    while (itemCubes != nullptr)
    {
        itemCubes->data->Render();
        itemCubes = itemCubes->next;
    }

    /*
    p2List_item<Torus*>* t = torusCheckpointList.getFirst();
    while (t != nullptr)
    {
        t->data->Render();
        t = t->next;
    }

    p2List_item<Cube*>* c = sticksList.getFirst();
    while (c)
    {
        c->data->Render();
        c = c->next;
    }
    */

    //donut.Render();

    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);

    //glVertex3f(-TEX_SIZE, 0.0, TEX_SIZE); // TEX_SIZE is image size

    glTexCoord2f(1.0, 0.0);

    //glVertex3f(TEX_SIZE, 0.0, TEX_SIZE);

    glTexCoord2f(1.0, 1.0);

    //glVertex3f(TEX_SIZE, 0.0, -TEX_SIZE);

    glTexCoord2f(0.0, 1.0);

    //glVertex3f(-TEX_SIZE, 0.0, -TEX_SIZE);

    glDisable(GL_TEXTURE_2D);

    glEnd();

    //glutSwapBuffers();

}