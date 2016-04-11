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

};

class GameObject
{
private:


public:
	Model model;
	RigidBody rigidBody;
	Transform transform;
	void updateModel(GLuint program,float);
	void moveModel(float);
	GameObject();
	~GameObject();
};

