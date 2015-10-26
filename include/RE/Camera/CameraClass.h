/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{
	//Camera Class
	class ReEngDLL CameraClass
	{
		bool m_bFPS = true; //If set to false will behave like a flight simulator camera

		CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP; //Sets the mode the camera will display

		float m_fFOV = 45.0f;

		vector2 m_v2NearFar = vector2(0.001f, 1000.0f);

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		vector3 m_v3PitchYawRoll = vector3(0.0f);

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		/*
		Method: CameraClass
		Usage: Constructor
		Arguments: ---
		Output: class object
		*/
		CameraClass(void);
		/* Constructor with parameters */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		CameraClass(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
		/* Copy Constructor */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		CameraClass(CameraClass const& other);
		/* Copy Assignment Operator*/
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		CameraClass& operator=(CameraClass const& other);
		/* Destructor */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		~CameraClass(void);

		/* Gets the View matrix from the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetViewMatrix(void);
		/* Gets the Projection matrix from the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetProjectionMatrix(void);
		/* Gets the ModelViewProjection matrix from the camera */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		matrix4 GetMVP(matrix4 a_m4ModelToWorld);
		/* Gets the ViewProjection matrix from the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetVP(void);

		/* Gets the position of the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		vector3 GetPosition(void);

		/* Changes the near and far planes */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		void SetNearFarPlanes(float a_fNear, float a_fFar);
		/* Calculates the projection based on the camera values */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		void CalculateProjection(void);
		/* Calculates the view based on the camera values */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		void CalculateView(void);
		/* Set Field of View */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		void SetFOV(float a_fFOV);

		/* Sets the camera at the specified position */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		void SetPosition(vector3 a_vPosition);
		/* Sets the camera at the specified position and target */
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		void SetPositionAndView(vector3 a_v3Position, vector3 a_v3Target);

		/* Gets the camera space just in front of the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetCameraSpaceAdjusted(void);
		/* Gets the camera plane of the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		matrix4 GetCameraPlane(void);

		/*	Translates the camera forward or backward */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void MoveForward(float a_fDistance = 0.1f);
		/*	Translates the camera Upward or downward */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void MoveVertical(float a_fDistance = 0.1f);
		/*	Translates the camera right or left */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f);

		/*	Rotates the camera Pitch */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void ChangePitch(float a_fDegree = 0.01f);
		/*	Rotates the camera Yaw */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void ChangeYaw(float a_fDegree = 0.01f);
		/*	Rotates the camera Roll */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void ChangeRoll(float a_fDegree = 0.01f);

		/* Sets the camera in First Person Shooter mode, if false it will work like an aircraft */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void SetFPS(bool a_bFPS = true);
		/* Sets the camera in Perspective mode, if false it will work as an orthographic camera*/
		/*
		Method: Usage:
		Arguments:
		Output:
		*/
		void SetCameraMode(CAMERAMODE a_nMode = CAMERAMODE::CAMPERSP);
		/* Returns the current value for the camera mode*/
		/*
		Method: Usage:
		Arguments: ---
		Output:
		*/
		CAMERAMODE GetCameraMode(void);

		/* Resets the value of the camera */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		void ResetCamera(void);

	private:
		/* Releases the object from memory */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		void Release(void);
		/* Initialize the object's fields */
		/*
		Method: Usage:
		Arguments: ---
		Output: ---
		*/
		void Init(void);
		/* Swaps the contents of the object with another object's content */
		/*
		Method: Usage:
		Arguments:
		Output: ---
		*/
		void Swap(CameraClass& other);
	};

	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass>;
	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass*>;
}
#endif //__CAMERACLASS_H_