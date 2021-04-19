#include "Camera.h"

using namespace DirectX;

Camera::Camera()
{
	posX = posY = posZ = 0.0f;
	rotX = rotY = rotZ = 0.0f;
}

Camera::~Camera()
{

}

void Camera::setPosition(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
}

void Camera::setRotation(float x, float y, float z)
{
	rotX = x;
	rotY = y;
	rotZ = z;
}

DirectX::XMFLOAT3 Camera::getPosition()
{
	return DirectX::XMFLOAT3(posX,posY,posZ);
}

DirectX::XMFLOAT3 Camera::getRotation()
{
	return DirectX::XMFLOAT3(rotX, rotY, rotZ);
}

void Camera::Render()
{
	XMFLOAT3 up, pos, lookAt;
	XMVECTOR upVector, posVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	upVector = XMLoadFloat3(&up);

	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	posVector = XMLoadFloat3(&pos);

	lookAt.x = 0.0;
	lookAt.y = 0.0;
	lookAt.z = 1.0;

	lookAtVector = XMLoadFloat3(&lookAt);
	
	pitch = rotX * 0.0174532925f;
	yaw = rotY * 0.0174532925f;
	roll = rotZ * 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	lookAtVector = XMVectorAdd(posVector, lookAtVector);

	m_viewmat = XMMatrixLookAtLH(posVector, lookAtVector, upVector);
}

void Camera::getViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewmat;
}
