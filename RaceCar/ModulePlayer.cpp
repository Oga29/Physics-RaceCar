#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"
#include "Timer.h"
VehicleInfo car;
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	jump_coolddown.Start();
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	car;
	

	// Car properties ----------------------------------------
	car.chassis_size.Set(3.0, 0.6, 7);
	car.chassis2_size.Set(2.3, 1.0, 5.0);
	car.chassis3_size.Set(2.5, 2, 0.5);
	car.chassis4_size.Set(3, 2, 0.5);
	car.mass = 130.0f;
	car.chassis_offset.Set(0, 0.5, 0);
	car.chassis2_offset.Set(0, 1, -1);
	car.chassis3_offset.Set(0, 0.7, 2);
	car.chassis4_offset.Set(0, 0.7, -3);

	//car.chassis_size.Set(3, 1.5, 6);
	//car.chassis_offset.Set(0, 1.5, 0);
	//car.chassis2_size.Set(3, 0.25, 3);
	//car.chassis2_offset.Set(0, 4, -1.5);
	//car.chassis3_size.Set(0.5, 0.5, 0.5);
	//car.chassis3_offset.Set(1, 1.5, 3);
	//car.chassis4_size.Set(0.5, 0.5, 0.5);
	//car.chassis4_offset.Set(-1, 1.5, 3);
	//car.chassis5_size.Set(0.25, 1.7, 0.25);
	//car.chassis5_offset.Set(1.38, 3.09, -2.88);
	//car.chassis6_size.Set(0.25, 1.7, 0.25);
	//car.chassis6_offset.Set(1.38, 3.09, -0.12);
	//car.chassis7_size.Set(0.25, 1.7, 0.25);
	//car.chassis7_offset.Set(-1.38, 3.09, -2.88);
	//car.chassis8_size.Set(0.25, 1.7, 0.25);
	//car.chassis8_offset.Set(-1.38, 3.09, -0.12);


	
	car.suspensionStiffness = 26.10f;
	car.suspensionCompression = 1.42f;
	car.suspensionDamping = 2.35f;
	car.maxSuspensionTravelCm = 510.0f;
	car.frictionSlip = 100.5;
	car.maxSuspensionForce = 1000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 0.8f;
	float wheel_radius = 0.75f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 0.8f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.2f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.2f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.2f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.2f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 5, 0);

	
	//vehicle->collision_listeners.add(this);
	vehicle->collision_listeners.add(App->scene_intro);

	vehicle->vehicle->getRigidBody()->setUserPointer(vehicle);

	initialPosition = vehicle->vehicle->getChassisWorldTransform().getOrigin();
	currentPlayerPosition = vehicle->vehicle->getChassisWorldTransform().getOrigin();

	//App->physics->AddConstraintP2P(*decorBody->body, *vehicle->body, car.rear_chassis_offset, car.rear_chassis_offset);

	inDirt = false;
	inIce = false;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->scene_intro->vehicleIndex == 1)
	{
		turn = acceleration = brake = 0.0f;

		if ((winCondition == false && looseCondition == false && App->scene_intro->trueLooseCondition == false) && App->scene_intro->sceneBeginTimer > 220)
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && (vehicle->GetKmh() < 120))
			{
				acceleration = MAX_ACCELERATION;
			}

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && (vehicle->GetKmh() > -30))
			{
				if (vehicle->GetKmh() > 10)
				{
					brake = BRAKE_POWER / 50;
				}

				else
				{

					if (vehicle->GetKmh() < -30)
					{
						acceleration = MAX_ACCELERATION * 5;
					}
					acceleration = -MAX_ACCELERATION * 5;
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				if (turn < TURN_DEGREES)
					turn += TURN_DEGREES;
			}

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				if (turn > -TURN_DEGREES)
					turn -= TURN_DEGREES;
			}
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				if ((jump_coolddown.Read() * 0.001) >= JUMP_COOLDOWN)
				{
					vehicle->Push(0.0f, JUMP_IMPULSE, 0.0f);
					jump_coolddown.Start();
				}

			}

			
		}


		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			App->scene_intro->lapSensorActivated = false;

			App->player->vehicle->SetPos(initialPosition.x(), initialPosition.y(), initialPosition.z());

			mat4x4 tr;
			tr.rotate(0, vec3(0, 1, 0));
			vehicle->vehicle->getRigidBody()->setAngularVelocity(btVector3(0, 0, 0));
			vehicle->SetTransform(&tr);
			

			vehicle->SetLinearVelocity(0, 0, 0);
		}



		vehicle->ApplyEngineForce(acceleration);
		vehicle->Turn(turn);
		vehicle->Brake(brake);

		if (!App->input->GetKey(SDL_SCANCODE_UP) && !App->input->GetKey(SDL_SCANCODE_DOWN))
		{
			vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh()));
		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
		{
			 car.mass += 10.0f;
			//if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) car.mass -= 10.0f;
		}
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
		{
			
			car.mass -= 10.0f;
		}
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && forces == true)
		{
			car.suspensionStiffness = 0.0f;
			car.suspensionCompression = 0.0f;
			car.suspensionDamping = 0.0f;
			car.maxSuspensionTravelCm = 0.0f;
			car.frictionSlip = 0.0f;
			car.maxSuspensionForce = 0.0f;
			forces = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && forces == false)
		{
			car.suspensionStiffness = 26.10f;
			car.suspensionCompression = 1.42f;
			car.suspensionDamping = 2.35f;
			car.maxSuspensionTravelCm = 510.0f;
			car.frictionSlip = 100.5;
			car.maxSuspensionForce = 1000.0f;
			forces = true;
		}


		vehicle->Render();

		float jump_cooldown_calc = 0.0f;
		jump_cooldown_calc = JUMP_COOLDOWN - jump_coolddown.Read() * 0.001f;
		if (jump_cooldown_calc < 0)
			jump_cooldown_calc = 0;

		int tiemer_milisec_read = 0;
		//tiemer_milisec_read = game_timer.Read() - chickens_taken * 2000;

		if (tiemer_milisec_read <= 0)
		{
			tiemer_milisec_read = 0;
		}

		if (winCondition == false || looseCondition == false)delay++;

		if ((delay % 60) == 0 && winCondition == false)
		{
			seconds++;
		}

		if (seconds == 60 && winCondition == false)
		{
			seconds = 0;
			minutes++;
		}
		if (winCondition == true || looseCondition == true)
		{
			seconds = seconds;
			minutes = minutes;
		}
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		{
			winCondition = true;
		}

		if (lap1 == true && lapDone == true)
		{
			lastSeconds = seconds;
			lastMinutes = minutes;
			lap2 = true;
			lapDone = false;
			lap1 = false;
		}
		if (lap2 == true && lapDone == true)
		{
			lastSeconds = seconds;
			lastMinutes = minutes;
			lap3 = true;
			lapDone = false;
			lap2 = false;
		}
		if (lap3 == true && lapDone == true)
		{
			lastSeconds = seconds;
			lastMinutes = minutes;
			lap4 = true;
			lapDone = false;
			lap3 = false;
		}
		if (lap4 == true && lapDone == true)
		{
			lastSeconds = seconds;
			lastMinutes = minutes;
			winCondition = true;
			lapDone = false;
		}

		if (inDirt == true)
		{
			if (vehicle->GetKmh() > 50)
			{
				vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh() + 1000.0f));
			}
		}
		
		else if (inIce == true)
		{
			if (vehicle->GetKmh() > 10)
			{
				vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh() - 500.0f));
			}
		}

		else if (inDirt == false)
		{
			if (vehicle->GetKmh() > 120)
			{
				vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh()));
			}
		}

	
		else if (inIce == false)
		{
			if (vehicle->GetKmh() < 120)
			{
				vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh()));
			}
		}

		//AIR CONTROL
		btVector3 PositionInTheAir;
		PositionInTheAir = vehicle->vehicle->getChassisWorldTransform().getOrigin();
		if (PositionInTheAir.getY() > 1)
		{
			Euler angles = vehicle->GetEulerAngles(vehicle->vehicle->getChassisWorldTransform().getRotation());

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				angles.yaw -= (DEGTORAD * 4);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				angles.yaw += (DEGTORAD * 4);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}

		}
		if (PositionInTheAir.getY() < -2)
		{
			App->scene_intro->lapSensorActivated = false;

			App->player->vehicle->SetPos(initialPosition.x(), initialPosition.y(), initialPosition.z());

			mat4x4 tr;
			tr.rotate(0, vec3(0, 1, 0));
			vehicle->vehicle->getRigidBody()->setAngularVelocity(btVector3(0, 0, 0));
			vehicle->SetTransform(&tr);

			vehicle->SetLinearVelocity(0, 0, 0);
		}


		char title[80];
		if (minutes == 4 && seconds == 0)
		{
			looseCondition == true;
			sprintf(title, "You have lost the race");
		}
		if (winCondition == false)
		{
			sprintf_s(title, "%.1f Km/h       Your Current Time: %d m %d s      Your Last Time: %d m %d s", vehicle->GetKmh(), minutes, seconds, lastMinutes, lastSeconds);
		}

		if (winCondition == true)
		{
			sprintf_s(title, "Your Final Time: %d m %d s", minutes, seconds);
		}
		if (App->scene_intro->trueLooseCondition == true)
		{
			sprintf_s(title, "Time is up! You lost");
		}
		if (winCondition == true)
		{
			if (vehicle->GetKmh() > 0)
			{
				vehicle->ApplyEngineForce(App->physics->DragForce(vehicle->GetKmh() + 1000.0f));
			}
		}
		App->window->SetTitle(title);

		currentPlayerPosition = vehicle->vehicle->getChassisWorldTransform().getOrigin();
	}

	
	return UPDATE_CONTINUE;
}



