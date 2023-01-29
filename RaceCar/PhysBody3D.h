#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "SString.h"

class btRigidBody;
class Module;
class btQuaternion;

struct Euler
{
	float roll;
	float pitch; 
	float yaw;
};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	Euler GetEulerAngles(btQuaternion q);
	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetRotation(btQuaternion q);
	void SetAsSensor(bool is_sensor);
	void SetLinearVelocity(float x, float y, float z);
	bool IsSensor();

private:
	btRigidBody* body = nullptr;

	bool isSensor = false;

public:
	SString name;
	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__