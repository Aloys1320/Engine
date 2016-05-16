#include "GameObject.h"
#include "ShaderManager.h"
#include <math.h>

void GameObject::updateModel(GLuint program,float time)
{
	moveModel(time);

	glProgramUniformMatrix4fv(program, glGetUniformLocation(program, "worldLoc"), 1, GL_FALSE, &transform.worldTrans[0][0]);
	model.render();
}

void GameObject::moveModel(float time)
{
	//Apply Friction
	rigidBody.force -= rigidBody.velocity * .0125f;
	
	//Gravity
	if(rigidBody.usesGravity)
		rigidBody.force += glm::vec3(0, -9.81, 0);
	
	//Calc Forces
	rigidBody.velocity += (rigidBody.force*time)/rigidBody.mass;
	rigidBody.force = glm::vec3(0);
	transform.location += ((rigidBody.velocity) * time);




	//std::cout << "Vx: " << rigidBody.velocity.x << "Vy:" << rigidBody.velocity.y << "Vz: " << rigidBody.velocity.z << std::endl;

	//Actual Movment
	transform.worldTrans = 
							glm::translate(transform.location) *
							glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) *
							glm::scale(transform.size);

}

bool GameObject::collidesWith(const GameObject & other)
{
	//If either has no collider
	if(collider==colliderless||other.collider==colliderless)
		return false;
	
	//If Both have sphere
	else if (collider == sphere&&other.collider == sphere) {
		glm::vec3 dist = transform.location - other.transform.location;
		//Get length of distance between them and check if it is larger than the radii sum
		if (pow(dist.x, 2) + pow(dist.y, 2) + pow(dist.z, 2) > pow((transform.size.x + other.transform.size.x),2))
			return false;
	}

	//If both are aabb based, check each axis
	else if(collider==axisAlignedBoundingBox&&other.collider==axisAlignedBoundingBox){
		if (
			abs(transform.location.x - other.transform.location.x) > (transform.size.x + other.transform.size.x) || // X-Axis Check
			abs(transform.location.y - other.transform.location.y) > (transform.size.y + other.transform.size.y) || // Y-Axis Check
			abs(transform.location.z - other.transform.location.z) > (transform.size.z + other.transform.size.z)	// Z-Axis Check
			) 
					return false;
	}

	//No Collisions detected, return true
	return true;
}

GameObject::GameObject()
{
	rigidBody.maxSpeed = .25;
	rigidBody.velocityChange = glm::vec3(0);

}


GameObject::~GameObject()
{
}
