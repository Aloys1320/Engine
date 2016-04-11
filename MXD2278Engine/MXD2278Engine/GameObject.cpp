#include "GameObject.h"
#include "ShaderManager.h"


void GameObject::updateModel(GLuint program,float time)
{
	moveModel(time);

	glProgramUniformMatrix4fv(program, glGetUniformLocation(program, "worldLoc"), 1, GL_FALSE, &transform.worldTrans[0][0]);
	model.render();
}

void GameObject::moveModel(float time)
{
	//Calc Forces
	rigidBody.velocity += rigidBody.velocityChange;
	rigidBody.force += (rigidBody.velocity*rigidBody.mass);

	//Limit a Game Objects max speed (default max speed is .025)
	//if (glm::length2(rigidBody.force)> rigidBody.maxSpeed) {
	//	rigidBody.force = glm::normalize(rigidBody.force);
	//	rigidBody.force *= rigidBody.maxSpeed;
	//}
	//rigidBody.force = glm::max(rigidBody.force, rigidBody.maxSpeed, rigidBody.maxSpeed);
	//Update the objects location
	transform.location += ((rigidBody.force) * (time/60));
	/*if (rigidBody.mass >= 1) {
		std::cout << "x: " <<rigidBody.force.x<< "y:" << rigidBody.force.y << "z: " << rigidBody.force.z << std::endl;
	}*/

	//Reset the applied force (doesnt reset the velocity, that will slowly dwindle down below)
	rigidBody.force = glm::vec3(0);

	//Apply Friction (x axis)
	//if (glm::length2(rigidBody.velocity)>0)
	rigidBody.velocity = rigidBody.velocity * .9f;

	//std::cout << "Vx: " << rigidBody.velocity.x << "Vy:" << rigidBody.velocity.y << "Vz: " << rigidBody.velocity.z << std::endl;

	//Actual Movment
	glm::mat4 translate;
	translate = { 1, 0, 0, transform.location.x,
		0, 1, 0, transform.location.y,
		0, 0, 1, transform.location.z,
		0, 0, 0, 1 };
	transform.worldTrans = 
		glm::scale(transform.size) *
		glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) *
		translate;

}

GameObject::GameObject()
{
	rigidBody.maxSpeed = .25;
	rigidBody.velocityChange = glm::vec3(0);

}


GameObject::~GameObject()
{
}
