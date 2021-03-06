#include "EulerCamera.h"

EulerCamera::EulerCamera(void)
{
	mAngleX = 0;
	mAngleY = 0;
	this->Reset(0, 0, 0, 
		0, 0, -1, 
		0, 1, 0);

	SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
	this->Set_CameraBoundry(100.0f);
}

EulerCamera::~EulerCamera(void)
{
}

glm::vec3 EulerCamera::GetLookDirection()
{
	return -mDirection;
}

void EulerCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void EulerCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;
	
	//still needs normalization
	mDirection = center - mPosition;
	//i = j x k
	mRight = glm::cross( mDirection,up );
	//j = k x i
	mUp = up;
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);

	mViewMatrix = glm::lookAt(mPosition,center,mUp);
	//UpdateViewMatrix();
}

bool EulerCamera::validboundry(float dist,glm::vec3 dir)
{
	vec3 NextPosition = mPosition+dist*dir;
	return(abs(NextPosition.x) < Get_CameraBoundry() &&abs(NextPosition.z) < Get_CameraBoundry());   
//&& abs(NextPosition.y) < Get_CameraBoundry()
}

glm::mat4 EulerCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void EulerCamera::UpdateViewMatrix()
{
	const float PI = 3.14f;
	mDirection = glm::vec3(
		-cos(mAngleY)*sin(mAngleX), 
		 sin(mAngleY), 
		-cos(mAngleY)*cos(mAngleX));
	

	mDirection = glm::normalize(mDirection);

	mRight = glm::cross(mDirection,glm::vec3(0,1,0));

	mUp = glm::cross(mRight,mDirection);

	glm::vec3 center = mPosition + mDirection;
	mViewMatrix = glm::lookAt(mPosition,center,mUp);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}


glm::mat4 EulerCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void EulerCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV,aspectRatio,near,far);
}

void EulerCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void EulerCamera::Yaw(float angleDegrees)
{
	mAngleX +=angleDegrees;
}

void EulerCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (mAngleY + angleDegrees < PI/2.0 && mAngleY + angleDegrees > - PI/2.0)
		mAngleY +=angleDegrees;
}

void EulerCamera::Roll(float angleDegrees)
{
	//no ROLL!!!
}

void EulerCamera::Walk(float dist)
{
	if (validboundry(dist,mDirection))
		mPosition += dist *vec3( mDirection.x,0,mDirection.z); //ignore y component of right dir
}

void EulerCamera::Strafe(float dist)
{
	if (validboundry(dist,mRight))
		mPosition += dist *vec3( mRight.x,0,mRight.z); //ignore y component of right dir
}

void EulerCamera::Fly(float dist)
{
	if (validboundry(dist,mUp))
	mPosition += dist * mUp;
}

glm::vec3 EulerCamera::GetEyePosition()
{
	return mPosition;
}

void EulerCamera::SetEyePosition(vec3 val)
{
	mPosition = val;
}
