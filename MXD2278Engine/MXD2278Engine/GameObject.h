#pragma once
#include "Model.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
struct RigidBody {
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	float maxSpeed;
	glm::vec3 velocityChange;
	bool usesGravity;
};

class GameObject
{
private:


public:
	enum colliders { colliderless, axisAlignedBoundingBox, sphere };
	colliders collider;
	Model model;
	RigidBody rigidBody;
	Transform transform;
	void updateModel(GLuint program,float);
	void moveModel(float);
	bool collidesWith(const GameObject & other);
	GameObject();
	~GameObject();
};

