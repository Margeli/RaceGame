#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;
class btVector3;

enum SceneObjectType {
	None =0,
	Turbo,
	Floor, 
	Ramp
};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetSensor()const;
	btVector3 GetPos() const;

private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;
	SceneObjectType type = None;
};

#endif // __PhysBody3D_H__