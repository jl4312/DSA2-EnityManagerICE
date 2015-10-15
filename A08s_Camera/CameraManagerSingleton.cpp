#include "CameraManagerSingleton.h"
//  MyCameraSingleton
CameraManagerSingleton* CameraManagerSingleton::m_pInstance = nullptr;
void CameraManagerSingleton::Init(void)
{
	m_nActiveCamera = 0;
	AddCamera(vector3(0.0f, 0.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f));
	m_nCameraCount = m_lCamera.size();
}
void CameraManagerSingleton::Release(void)
{
	for (uint nCamera = 0; nCamera < m_lCamera.size(); nCamera++)
	{
		CameraClass* pCamera = m_lCamera[nCamera];
		if (pCamera != nullptr)
		{
			delete pCamera;
			pCamera = nullptr;
		}
	}
	m_nCameraCount = m_lCamera.size();
}
CameraManagerSingleton* CameraManagerSingleton::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CameraManagerSingleton();
	}
	return m_pInstance;
}
void CameraManagerSingleton::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
CameraManagerSingleton::CameraManagerSingleton()
{
	Init();
}
CameraManagerSingleton::CameraManagerSingleton(CameraManagerSingleton const& other){ }
CameraManagerSingleton& CameraManagerSingleton::operator=(CameraManagerSingleton const& other) { return *this; }
CameraManagerSingleton::~CameraManagerSingleton(){ Release(); };
//Accessors
void CameraManagerSingleton::SetActiveCamera(uint a_nIndex){ if (a_nIndex <= m_nCameraCount) m_nActiveCamera = a_nIndex; return; }
uint CameraManagerSingleton::GetCameraCount(void){ return m_nCameraCount; }
void CameraManagerSingleton::SetPosition(vector3 a_v3Position, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->SetPosition(a_v3Position);
	}
	return m_lCamera[m_nActiveCamera]->SetPosition(a_v3Position);
}
void CameraManagerSingleton::SetNearFarPlanes(float a_fNear, float a_fFar, int a_nIndex)
{
	if (a_nIndex = -1)
		m_lCamera[m_nActiveCamera]->SetNearFarPlanes(a_fNear, a_fFar);
	else if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		m_lCamera[a_nIndex]->SetNearFarPlanes(a_fNear, a_fFar);
	}
}
void CameraManagerSingleton::SetWindowSize(int a_nIndex)
{
	if (a_nIndex = -1)
		m_lCamera[m_nActiveCamera]->SetWindowSize();
	else if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		m_lCamera[a_nIndex]->SetWindowSize();
	}
}

void CameraManagerSingleton::SetFOV(float a_fFOV, int a_nIndex)
{
	if (a_nIndex = -1)
		m_lCamera[m_nActiveCamera]->SetFOV(a_fFOV);
	else if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		m_lCamera[a_nIndex]->SetFOV(a_fFOV);
	}
}
matrix4 CameraManagerSingleton::GetViewMatrix(int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->GetViewMatrix();
	}
	return m_lCamera[m_nActiveCamera]->GetViewMatrix();
}
matrix4 CameraManagerSingleton::GetProjectionMatrix(int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->GetProjectionMatrix();
	}
	return m_lCamera[m_nActiveCamera]->GetProjectionMatrix();
}
matrix4 CameraManagerSingleton::GetMVPMatrix(matrix4 a_m4ModelToWorld, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->GetMVP(a_m4ModelToWorld);
	}
	return m_lCamera[m_nActiveCamera]->GetMVP(a_m4ModelToWorld);
}

//--- Non Standard Singleton Methods
uint CameraManagerSingleton::AddCamera(vector3 a_v3Eye, vector3 a_v3Target, vector3 a_v3Up)
{
	CameraClass* pCamera = new CameraClass(a_v3Eye, a_v3Target, a_v3Up);
	m_lCamera.push_back(pCamera);
	m_nCameraCount = m_lCamera.size();
	return m_nCameraCount - 1;
}
void CameraManagerSingleton::CalculateProjection(int a_nIndex)
{
	if (a_nIndex = -1)
		m_lCamera[m_nActiveCamera]->CalculateProjection();
	else if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		m_lCamera[a_nIndex]->CalculateProjection();
	}
}
void CameraManagerSingleton::CalculateView(int a_nIndex)
{
	if (a_nIndex = -1)
		m_lCamera[m_nActiveCamera]->CalculateView();
	else if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		m_lCamera[a_nIndex]->CalculateView();
	}
}
void CameraManagerSingleton::MoveForward(float a_fDistance, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->MoveForward(a_fDistance);
	}
	return m_lCamera[m_nActiveCamera]->MoveForward(a_fDistance);
}

void CameraManagerSingleton::MoveVertical(float a_fDistance, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->MoveVertical(a_fDistance);
	}
	return m_lCamera[m_nActiveCamera]->MoveVertical(a_fDistance);
}

void CameraManagerSingleton::MoveSideways(float a_fDistance, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->MoveSideways(a_fDistance);
	}
	return m_lCamera[m_nActiveCamera]->MoveSideways(a_fDistance);
}
void CameraManagerSingleton::ChangePitch(float a_fDegree, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->ChangePitch(a_fDegree);
	}
	return m_lCamera[m_nActiveCamera]->ChangePitch(a_fDegree);
}
void CameraManagerSingleton::ChangeYaw(float a_fDegree, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->ChangeYaw(a_fDegree);
	}
	return m_lCamera[m_nActiveCamera]->ChangeYaw(a_fDegree);
}
void CameraManagerSingleton::ChangeRoll(float a_fDegree, int a_nIndex)
{
	if (static_cast<uint>(a_nIndex) <= m_nCameraCount)
	{
		return m_lCamera[a_nIndex]->ChangeRoll(a_fDegree);
	}
	return m_lCamera[m_nActiveCamera]->ChangeRoll(a_fDegree);
}