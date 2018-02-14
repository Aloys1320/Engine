#pragma once
#include "GameObject.h"
class Camera
{
private:
	float zoom;
	int width;
	int height;

	float fov;
	float aspect;
	float zNear;
	float zFar;
	Transform transform;
	RigidBody rigidBody;
	glm::mat4 perspectiveMat;

	glm::mat4 cameraMatrix;
public:
	Transform camTransform;
	RigidBody camRigidBody;
	void updateCamera(GLuint,float);
	void moveCamera(float);
	Camera();
	~Camera();
};

