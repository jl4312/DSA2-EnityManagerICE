#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Sierpinski triangle");
}

uint GetCoefficient(DWORDLONG nRow, DWORDLONG nElement)
{
	// n! / (r! * (n-r)!) where n is the row and r is the element index of the row
	DWORDLONG lRowFac = glm::factorial(nRow);
	DWORDLONG lRowMinEleFac = glm::factorial(nRow - nElement);
	DWORDLONG lEleFac = glm::factorial(nElement);
	return (lRowFac / (lEleFac * lRowMinEleFac));
}

bool GetParity(uint nRow, uint nElement)
{
	//getting the polynomial coefficient
	uint nCoefficient = GetCoefficient(nRow, nElement);
	printf("%d ", nCoefficient);
	//Checking if its pair or odd
	//return (nCoefficient % 2 == 0);
	return !(nCoefficient & 1); //another cool way of checking for parity =)
}

void AppClass::InitVariables(void)
{
	m_pCamera->SetPosition(vector3(0.0f, -12.0f, 50.0f));
	m_pMesh = new MeshClass();

	//Creating the triangle points
	float fRadius = 1.0f;
	double theta = PI / 2.0f;
	for (uint i = 0; i < 3; i++)
	{
		theta += static_cast<GLfloat>(2 * PI / 3);
		m_pMesh->AddVertexPosition(vector3(	cos(theta) * fRadius,
											sin(theta) * fRadius,
											0.0f) );
	}

	//Adding the colors (which doesn't really matter)
	m_pMesh->AddVertexColor(REGREEN);
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexColor(REBLUE);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();

	//Initializing the array of floats
	//I will only make 81 objects
	m_nObjects = 81;
	// We need 16 floats for each object
	m_fMatrixArray = new float[m_nObjects * 16];
	//Initializing the whole spaces to the position at the origin just to play it safe
	vector3 vPosition = vector3(0.0f);
	const float* m4MVP = glm::value_ptr(glm::translate(vPosition));
	for (uint n = 0; n < m_nObjects; n++)
	{
		memcpy(&m_fMatrixArray[n * 16], m4MVP, 16 * sizeof(float));
	}

	//Initializing the values
	uint nRow = 1;//what row I'm in
	uint nElement = 1;//what element of that row
	uint nTriangle = 0;//how many triangles I have reposition
	printf("\n%d -> ", nRow - 1);//for debugging purposes
	while (nTriangle < m_nObjects)//while I'm not done with the triangles I want to initialize
	{
		//Check if this element is odd or pair (Sierpinski Triangle only renders elements whose coefficient is odd)
		if (GetParity(nRow - 1, nElement - 1) == false)//I have to decrease because my row and element index are off by one because the way I'm counting
		{
			m4MVP = glm::value_ptr(glm::translate(vPosition));//translate to the position and save it in a matrix
			memcpy(&m_fMatrixArray[nTriangle * 16], m4MVP, 16 * sizeof(float));//memcopy for fast copy
			nTriangle++;//because as I might be skipping triangles I cant a the regular forLoop for this
		}

		vPosition += vector3(0.87f * 2, 0.0f, 0.0f);//move to the right
		
		if (nElement == nRow)//if Im done with the row
		{
			printf("\n%d -> ", nRow);//debug
			vPosition = vector3(-0.87f * nRow, vPosition.y - 1.5f, 0.0f);//move down and to the left (depending of the triangles)
			nRow++;//Increase the row
			nElement = 0;//reset the elements of the row (because you are in a new one)
		}

		nElement++;//increment the element index
	}
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		m_qArcBall = ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCamera->CalculateView();

	//print info into the console
	printf("FPS: %d            \r", m_pSystem->GetFPS());//print the Frames per Second
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//m_pGrid->Render(1.0f); //renders the grid with a 100 scale

	m_pMesh->Render(m_fMatrixArray, m_nObjects);//Rendering nObjects

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