#pragma once

#ifndef _CAMERA_
#define _CAMERA_

#include <DirectXMath.h>
class Camera
{
public:
	Camera();
	~Camera();

	void setPosition(float, float, float);
	void setRotation(float, float, float);


	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();

	void Render();
	void getViewMatrix(DirectX::XMMATRIX&);
private:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	DirectX::XMMATRIX m_viewmat;

};

#endif