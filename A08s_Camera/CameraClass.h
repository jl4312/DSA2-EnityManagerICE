/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "RE\ReEngAppClass.h"
//Camera Class
class CameraClass
{
	bool m_bPerspectiveView = true; //perspective = true | orthographic = false

	float m_fFOV = 45.0f;

	vector2 m_v2WindowSize = vector2(0.0f, 0.0f);
	vector2 m_v2NearFar = vector2(0.001f, 1000.0f);

	vector3 m_v3Eye = vector3(0.0f, 0.0f, 5.0f);
	
	vector3 m_v3Target = vector3(0.0f, 0.0f, 5.0f);

	vector3 m_v3Up = vector3(0.0f, 1.0f, 0.0f);
	vector3 m_v3Forward = vector3(0.0f, 0.0f,-1.0f);
	vector3 m_v3Right = vector3(1.0f, 0.0f, 0.0f);

	matrix4 m_m4Projection = matrix4(1.0f);
	matrix4 m_m4View = matrix4(1.0f);
public:
	/* Constructor */
	CameraClass(void);
	/* Constructor with parameters */
	CameraClass(vector3 a_v3Eye, vector3 a_v3Target, vector3 a_v3Up);
	/* Copy Constructor */
	CameraClass(CameraClass const& other);
	/* Copy Assignment Operator*/
	CameraClass& operator=(CameraClass const& other);
	/* Destructor */
	~CameraClass(void);

	/* Gets the View matrix from the camera */
	matrix4 GetViewMatrix(void);
	/* Gets the Projection matrix from the camera */
	matrix4 GetProjectionMatrix(void);
	/* Gets the ModelViewProjection matrix from the camera */
	matrix4 GetMVP(matrix4 a_m4ModelToWorld);
	
	/* Changes the near and far planes */
	void SetNearFarPlanes(float a_fNear, float a_fFar);
	/* Set the window size based on the system's */
	void SetWindowSize(void);
	/* Calculates the projection based on the camera values */
	void CalculateProjection(void);
	/* Calculates the view based on the camera values */
	void CalculateView(void);
	/* Set Field of View */
	void SetFOV(float a_fFOV);

	/* Sets the camera at the specified position */
	void SetPosition(vector3 a_vPosition);

	/*	Translates the camera forward or backward */
	void MoveForward(float a_fDistance = 0.1f);
	/*	Translates the camera Upward or downward */
	void MoveVertical(float a_fDistance = 0.1f);
	/*	Translates the camera right or left */
	void MoveSideways(float a_fDistance = 0.1f);

	/*	Rotates the camera Pitch */
	void ChangePitch(float a_fDegree = 1.0f);
	/*	Rotates the camera Yaw */
	void ChangeYaw(float a_fDegree = 1.0f);
	/*	Rotates the camera Roll */
	void ChangeRoll(float a_fDegree = 1.0f);

private:
	/* Releases the object from memory */
	void Release(void);
	/* Initialize the object's fields */
	void Init(void);
	/* Swaps the contents of the object with another object's content */
	void Swap(CameraClass& other);
};

#endif //__CAMERACLASS_H_