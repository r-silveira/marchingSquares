

#include<gl/glut.h>
#include "Image.h"
#include <iostream>

#include "MarchingSquares.h"

//-----------------------------------------------------------------------------

float* heights_ = NULL;
int imageWidth = 0;
int imageLenght = 0;

MarchingSquares marchingSquares;


//-----------------------------------------------------------------------------
void drawAxis()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(imageWidth, 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, imageLenght, 0.0f);
	glEnd();
}


//-----------------------------------------------------------------------------
void drawHeights()
{
	if (marchingSquares.getData() != NULL)
	{
		glBegin(GL_POINTS);
		for (int i = 0 ; i < marchingSquares.getHeight(); ++i)
		{
			for (int j = 0; j < marchingSquares.getHeight(); ++j) 
			{
				const float& color = marchingSquares.atDataIndex(i,j);

				glColor3f(color, color, color);
				glVertex2f(i,j);
			}
		}
		glEnd();
	}
}


//-----------------------------------------------------------------------------
void drawIsolines()
{
	glBegin(GL_LINES);

	for (std::list< Vec2<float> >::const_iterator it = marchingSquares.getIsolineVertexList()->begin();
		it != marchingSquares.getIsolineVertexList()->end(); ++it)
	{
		glVertex2f((*it)[0], (*it)[1]);
	}

	glEnd();
}


//-----------------------------------------------------------------------------
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

	/*
	glPushMatrix();
	glTranslatef(0.5f, 0.5f, 0.0f);
	drawAxis();
	glPopMatrix();
	*/

	drawHeights();

	/*
	float threshold = 0.0f;

	glColor3f(threshold, 0.0f, 1.0f- threshold);
	marchingSquares.setThreshold(threshold);
	processEachCells();

	threshold = 0.3f;
	glColor3f(threshold, 0.0f, 1.0f- threshold);
	marchingSquares.setThreshold(threshold);
	processEachCells();

	threshold = 0.6f;
	glColor3f(threshold, 0.0f, 1.0f- threshold);
	marchingSquares.setThreshold(threshold);
	processEachCells();

	threshold = 0.9f;
	glColor3f(threshold, 0.0f, 1.0f- threshold);
	marchingSquares.setThreshold(threshold);
	processEachCells();
	*/
	
	glColor3f(marchingSquares.getThreshold(), 0.0f, 1.0f- marchingSquares.getThreshold());
	drawIsolines();

	glutSwapBuffers();
}


void idle()
{
	
}


//-----------------------------------------------------------------------------
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0.0,imageWidth, 0.0f, imageLenght);
    glMatrixMode(GL_MODELVIEW);
}


//-----------------------------------------------------------------------------
void loadImage(char* filename)
{
	std::string imageName = filename;

	CImage* oImage = NULL;
	oImage = new CImage();

	if (oImage == NULL)
	{
		std::cerr << "Erro ao alocar Imagem" << std::endl;
		return;
	}	
	
	if (!oImage->LoadFromFilename(imageName))
	{
		std::cerr << "Imagem nao encontrada" << std::endl;
		return;
	}

	imageWidth = oImage->GetWidth();
	imageLenght = oImage->GetHeight();
	const int& nDepth = oImage->GetPixelDepth();
	const unsigned char* pixels = oImage->GetData();

	if (heights_ != NULL)
	{
		delete[] heights_;
		heights_ = NULL;
	}

	// alocate memory for the terrain, and check for errors
	heights_ = new float[imageWidth*imageLenght];
	
	if (!heights_)
		std::cerr << "Nao alocou memoria pra heights_" << std::endl;

	std::cout << "gridLength: " << imageLenght << std::endl;
	std::cout << "gridWidth: " << imageWidth << std::endl;


	for (int i = 0 ; i < imageLenght; ++i)
	{
		for (int j = 0; j < imageWidth; ++j) 
		{
			// compute the height as a value between 0.0 and 1.0
			const float pointHeight = pixels[nDepth*(i*imageWidth + j)+(nDepth-1)] / 256.0f;
			heights_[i*imageWidth + j] = pointHeight;
		}
	}

	delete oImage;
}


//-----------------------------------------------------------------------------
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
    glutCreateWindow("Marching Squares");
   
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutReshapeFunc(myReshape);
    glutDisplayFunc(display); 
	glutIdleFunc(idle);
  
	loadImage("hm3.png");
	//loadImage("hm4.tga");

	marchingSquares.setHeightMap(imageWidth, imageLenght, heights_);
	marchingSquares.computeIsolines(0.63f);
	//marchingSquares.setThreshold(0.4f);
	//marchingSquares.debugInfo();

    glutMainLoop();
}