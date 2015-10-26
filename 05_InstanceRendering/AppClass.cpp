#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering - Example");
}

void AppClass::InitVariables(void)
{
	//Reserve Memory for a MyMeshClass object
	m_pMesh = new MyMesh();

	m_pMesh->AddVertexPosition(vector3(0.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexPosition(vector3(5.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexPosition(vector3(0.0f, 5.0f, 0.0f));

	m_pMesh->AddVertexColor(REGREEN);
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexColor(REBLUE);

	m_pMesh->CompileOpenGL3X();

	m_fMatrixArray = new float[m_nObjects * 16];
	for (int nObject = 0; nObject < m_nObjects; nObject++)
	{
		const float* m4MVP = glm::value_ptr(
			glm::translate(vector3(0.01f * -nObject, 0.0f, 1.0f * -nObject)) *
			glm::rotate(IDENTITY_M4, nObject * 5.0f, REAXISZ)
			);
		memcpy(&m_fMatrixArray[nObject * 16], m4MVP, 16 * sizeof(float));
	}

}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pMesh->RenderList(m_fMatrixArray, m_nObjects);//Rendering nObjects

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->Render();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}