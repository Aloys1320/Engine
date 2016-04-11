#include "Camera.h"



void Camera::updateCamera(GLuint program, float time)
{
	moveCamera(time);
	perspectiveMat = glm::perspective(fov, aspect, zNear, zFar);
	glm::vec3 eye = camTransform.location;
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(camTransform.rotation.y, camTransform.rotation.x, camTransform.rotation.z);
	glm::vec3 center = eye + rotMat*glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat*glm::vec3(0, 1, 0);

	cameraMatrix = glm::perspective(fov, aspect, zNear, zFar)*glm::lookAt(eye, center, up);
	glProgramUniformMatrix4fv(program, glGetUniformLocation(program, "cameraMat"), 1, GL_FALSE, &cameraMatrix[0][0]);

}

void Camera::moveCamera(float time)
{
	//Calc Forces
	camRigidBody.velocity += camRigidBody.velocityChange;
	camRigidBody.force += (camRigidBody.velocity*camRigidBody.mass);

	//Limit a Game Objects max speed (default max speed is .025)
	//if (glm::length2(rigidBody.force)> rigidBody.maxSpeed) {
	//	rigidBody.force = glm::normalize(rigidBody.force);
	//	rigidBody.force *= rigidBody.maxSpeed;
	//}
	//rigidBody.force = glm::max(rigidBody.force, rigidBody.maxSpeed, rigidBody.maxSpeed);
	//Update the objects location
	camTransform.location += ((camRigidBody.force) * (time/7.5f));
	if (camRigidBody.mass >= 1) {
	//	std::cout << "x: " << camRigidBody.force.x << "y:" << camRigidBody.force.y << "z: " << camRigidBody.force.z << std::endl;
	}

	//Reset the applied force (doesnt reset the velocity, that will slowly dwindle down below)
	camRigidBody.force = glm::vec3(0);

	//Apply Friction (x axis)
	camRigidBody.velocity = camRigidBody.velocity * .9f;
	std::cout << "CVx: " << camRigidBody.velocity.x << "CVy:" << camRigidBody.velocity.y << "CVz: " << camRigidBody.velocity.z << std::endl;

	//Actual Movment
	glm::mat4 translate;
	translate = { 1, 0, 0, camTransform.location.x,
		0, 1, 0, camTransform.location.y,
		0, 0, 1, camTransform.location.z,
		0, 0, 0, 1 };
	camTransform.worldTrans =
		glm::scale(transform.size) *
		glm::yawPitchRoll(camTransform.rotation.y, camTransform.rotation.x, camTransform.rotation.z) *
		translate;

}

Camera::Camera()
{
	zoom = 1.f;
	width = 800;
	height = 600;
	fov = 3.14159f * .4f / zoom;
	aspect = (float)width / (float)height;
	zNear = .01f;
	zFar = 1000.f;
	perspectiveMat=glm::perspective(fov, aspect, zNear, zFar);
	camRigidBody.mass = 1;
}


Camera::~Camera()
{
}
