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
	camRigidBody.force -= camRigidBody.velocity * 1.0f;

	//Calc Forces
	camRigidBody.velocity += (camRigidBody.force*time) / camRigidBody.mass;
	camRigidBody.force = glm::vec3(0);
	camTransform.location += ((camRigidBody.velocity) * time);



	//Actual Movment

	camTransform.worldTrans =
		glm::translate(transform.location) *
		glm::yawPitchRoll(camTransform.rotation.y, camTransform.rotation.x, camTransform.rotation.z) *
		glm::scale(transform.size);

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
