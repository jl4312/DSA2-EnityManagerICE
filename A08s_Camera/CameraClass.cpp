#include "CameraClass.h"
//  CameraClass
void CameraClass::Init(void)
{
	m_bPerspectiveView = true;

	m_fFOV = 45.0f;

	m_v3Eye = vector3(0.0f, 0.0f, 5.0f);
	m_v3Target = vector3(0.0f, 0.0f, 4.0f);

	m_v3Up = vector3(0.0f, 1.0f, 0.0f);
	m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
	m_v3Right = vector3(1.0f, 0.0f, 0.0f);

	SetWindowSize();
	SetNearFarPlanes(0.001f, 1000.0f);

	m_m4Projection = matrix4(1.0f);
	m_m4View = matrix4(1.0f);
}
void CameraClass::Swap(CameraClass& other)
{
}
void CameraClass::Release(void)
{
}
//The big 3
CameraClass::CameraClass()
{
	Init();
	CalculateProjection();
}
CameraClass::CameraClass(vector3 a_v3Eye, vector3 a_v3Target, vector3 a_v3Up)
{
	Init();

	m_v3Eye = a_v3Eye;
	m_v3Target = a_v3Target;
	m_v3Up = a_v3Up;
	m_v3Forward = glm::normalize(m_v3Target - m_v3Eye);
	m_v3Right = glm::normalize(glm::cross(m_v3Forward, m_v3Up));
	CalculateProjection();
}
CameraClass::CameraClass(CameraClass const& other)
{
}
CameraClass& CameraClass::operator=(CameraClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		CameraClass temp(other);
		Swap(temp);
	}
	return *this;
}
CameraClass::~CameraClass(){ Release(); };
//Accessors
matrix4 CameraClass::GetViewMatrix(void){ CalculateView(); return m_m4View; }
matrix4 CameraClass::GetProjectionMatrix(void){ CalculateProjection(); return m_m4Projection; }
void CameraClass::SetNearFarPlanes(float a_fNear, float a_fFar){ m_v2NearFar = vector2(a_fNear, a_fFar); }
void CameraClass::SetFOV(float a_fFOV){ m_fFOV = a_fFOV; }
void CameraClass::SetPosition(vector3 a_vPosition)
{
	m_v3Eye = a_vPosition;
	m_v3Target = glm::normalize(m_v3Eye + m_v3Forward);
	m_v3Forward = glm::normalize(m_v3Target - m_v3Eye);
	CalculateProjection();
}
void CameraClass::SetWindowSize(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	m_v2WindowSize = vector2(pSystem->GetWindowWidth(), pSystem->GetWindowHeight());
	if (m_v2WindowSize.x < 1) m_v2WindowSize.x = 1;
	if (m_v2WindowSize.y < 1) m_v2WindowSize.y = 1; 
}
matrix4 CameraClass::GetMVP(matrix4 a_m4ModelToWorld)
{
	CalculateView();
	CalculateProjection();
	return m_m4Projection * m_m4View * a_m4ModelToWorld;
}
//--- Non Standard Singleton Methods
void CameraClass::CalculateProjection(void)
{
	if (m_bPerspectiveView)
	{
		m_m4Projection = glm::perspective(m_fFOV, m_v2WindowSize.x / m_v2WindowSize.y, m_v2NearFar.x, m_v2NearFar.y);
	}
	else
	{
		m_m4Projection = glm::ortho(-m_v2WindowSize.x, m_v2WindowSize.x, -m_v2WindowSize.y, m_v2WindowSize.y, m_v2NearFar.x, m_v2NearFar.y);
	}
}
void CameraClass::CalculateView(void)
{
	m_m4View = glm::lookAt(m_v3Eye, m_v3Target, m_v3Up);
}

void CameraClass::MoveForward(float a_fDistance)
{
	m_v3Eye += m_v3Forward * a_fDistance;
	m_v3Target += m_v3Forward * a_fDistance;
}

void CameraClass::MoveVertical(float a_fDistance)
{
	m_v3Eye += m_v3Up * a_fDistance;
	m_v3Target += m_v3Up * a_fDistance;
}

void CameraClass::MoveSideways(float a_fDistance)
{
	m_v3Eye += m_v3Right * a_fDistance;
	m_v3Target += m_v3Right * a_fDistance;
}

void CameraClass::ChangePitch(float a_fDegree)
{
	quaternion qOrientation = glm::angleAxis(a_fDegree, m_v3Right);
	//quaternion qOrientation = quaternion(glm::radians(a_fDegree), 1.0f, 0.0f, 0.0f);
	qOrientation = glm::normalize(qOrientation);
	m_v3Forward = qOrientation * m_v3Forward;
	m_v3Up = qOrientation * m_v3Up;
	m_v3Right = qOrientation * m_v3Right;
}
void CameraClass::ChangeYaw(float a_fDegree)
{
	//quaternion qOrientation = quaternion(glm::radians(a_fDegree), 0.0f, 1.0f, 0.0f);
	quaternion qOrientation = glm::angleAxis(a_fDegree, m_v3Up);
	qOrientation = glm::normalize(qOrientation);

	m_v3Forward = m_v3Forward * qOrientation;
	m_v3Up = m_v3Up * qOrientation;
	m_v3Right = m_v3Right * qOrientation;

	m_v3Target = m_v3Target* qOrientation;
}
void CameraClass::ChangeRoll(float a_fDegree)
{
	quaternion qOrientation = quaternion(glm::radians(a_fDegree), 0.0f, 0.0f, 1.0f);
	qOrientation = glm::normalize(qOrientation);
	m_v3Forward = qOrientation * m_v3Forward;
	m_v3Up = qOrientation * m_v3Up;
	m_v3Right = qOrientation * m_v3Right;
}