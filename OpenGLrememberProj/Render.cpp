#include "Render.h"

#include <sstream>
#include <iostream>

#include <windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "MyOGL.h"

#include "Camera.h"
#include "Light.h"
#include "Primitives.h"

#include "GUItextRectangle.h"
#include <math.h>

bool textureMode = true;
bool lightMode = true;




double* findNormal(double* a, double* b) {
	double x = *(a + 1) * *(b + 2) - *(b + 1) + *(a + 2);
	double y = -*(a + 0) * *(b + 2) + *(b + 0) * *(a + 2);
	double z = *(a + 0) * *(b + 1) - *(b + 0) * *(a + 2);

	// ����������� � ������������� lenght
	double lenght = sqrt(x * x + y * y + z * z);

	// ��������� ������ ��� �������
	double* normal = (double*)malloc(3 * sizeof(double));

	// ������ ��������� �������
	normal[0] = x / lenght;
	normal[1] = y / lenght;
	normal[2] = z / lenght;

	// ����������� ��������� �� �������
	return normal;
}

double* findVector(double x, double y, double z, double x1, double y1, double z1) {
	double* vector = (double*)malloc(3 * sizeof(double));

	vector[0] = x1 - x;
	vector[1] = y1 - y;
	vector[2] = z1 - z;

	return vector;
}

double* findVector(double* a, double* b) {
	double* vector = (double*)malloc(3 * sizeof(double));

	vector[0] = *(b + 0) - *(a + 0);
	vector[1] = *(b + 1) - *(a + 1);
	vector[2] = *(b + 2) - *(a + 2);

	return vector;
}

//���������
void fund_bottom(double startHeight) {

	double A[] = { 0, 0, startHeight };
	double B[] = { 5, 3, startHeight };
	double C[] = { 4, 8, startHeight };
	double D[] = { 9, 10, startHeight };
	double E[] = { 14, 5, startHeight };
	double F[] = { 12, -1, startHeight };
	double G[] = { 7, 1, startHeight };
	double H[] = { 4, -2, startHeight };


	glBegin(GL_TRIANGLES);
	glColor3d(0.7, 0.6, 0.4);

	//findNormal(findVector(C, B), findVector(B, A));

	glNormal3f(0, 0, -1);
	glVertex3dv(A);
	glVertex3dv(B);
	glVertex3dv(G);

	glVertex3dv(A);
	glVertex3dv(H);
	glVertex3dv(G);

	glVertex3dv(B);
	glVertex3dv(C);
	glVertex3dv(D);

	glVertex3dv(B);
	glVertex3dv(D);
	glVertex3dv(E);

	glVertex3dv(B);
	glVertex3dv(E);
	glVertex3dv(F);

	glVertex3dv(B);
	glVertex3dv(F);
	glVertex3dv(G);

	glEnd();

}


void fund_top(double height) {

	double A[] = { 0, 0, height };
	double B[] = { 5, 3, height };
	double C[] = { 4, 8, height };
	double D[] = { 9, 10, height };
	double E[] = { 14, 5, height };
	double F[] = { 12, -1, height };
	double G[] = { 7, 1, height };
	double H[] = { 4, -2, height };


	glBegin(GL_TRIANGLES);
	glColor3d(0.7, 0.6, 0.4);

	glNormal3f(0, 0, 1);
	glTexCoord2d(A[0] / 20, A[1] / 20);
	glVertex3dv(A);
	glTexCoord2d(B[0] / 20, B[1] / 20);
	glVertex3dv(B);
	glTexCoord2d(G[0] / 20, G[1] / 20);
	glVertex3dv(G);

	glVertex3dv(A);
	glVertex3dv(H);
	glVertex3dv(G);

	glVertex3dv(B);
	glVertex3dv(C);
	glVertex3dv(D);

	glVertex3dv(B);
	glVertex3dv(D);
	glVertex3dv(E);

	glVertex3dv(B);
	glVertex3dv(E);
	glVertex3dv(F);

	glVertex3dv(B);
	glVertex3dv(F);
	glVertex3dv(G);

	glEnd();

}

double* normalize(double* start, double* end, double* vectHigh) {
	double* vector1 = findVector(start, end);
	double* vector2 = findVector(start, vectHigh);
	return findNormal(vector1, vector2);
}

double* normalizeSides(double* start, double* end, double* vectHigh) {
	double* vector1 = findVector(start, end);
	double* vector2 = findVector(start, vectHigh);
	return findNormal(vector2, vector1);
}

//�������
void sides(double startHeight, double height) {

	double A[] = { 0, 0, startHeight };
	double B[] = { 5, 3, startHeight };
	double C[] = { 4, 8, startHeight };
	double D[] = { 9, 10, startHeight };
	double E[] = { 14, 5, startHeight };
	double F[] = { 12, -1, startHeight };
	double G[] = { 7, 1, startHeight };
	double H[] = { 4, -2, startHeight };
	double vectHigh[] = { 0, 0, 5 };

	glBegin(GL_QUADS);
	glColor3d(0, 0, 0);



	glNormal3dv(normalize(B,A,vectHigh));

	glVertex3d(0, 0, startHeight);
	glVertex3d(0, 0, height);
	glVertex3d(5, 3, height);
	glVertex3d(5, 3, startHeight);


	double vectHigh1[] = { 5,3,5 };
	glNormal3dv(normalize(C, B, vectHigh1));

	glVertex3d(5, 3, startHeight);
	glVertex3d(5, 3, height);
	glVertex3d(4, 8, height);
	glVertex3d(4, 8, startHeight);


	double vectHigh2[] = { 4,8,5 };
	glNormal3dv(normalize(D, C, vectHigh2));

	glVertex3d(4, 8, startHeight);
	glVertex3d(4, 8, height);
	glVertex3d(9, 10, height);
	glVertex3d(9, 10, startHeight);


	double vectHigh3[] = { 9,10,5 };
	glNormal3dv(normalize(E, D, vectHigh3));

	glVertex3d(9, 10, startHeight);
	glVertex3d(9, 10, height);
	glVertex3d(14, 5, height);
	glVertex3d(14, 5, startHeight);


	double vectHigh4[] = { 14,5,5 };
	glNormal3dv(normalize(F, E, vectHigh4));

	glVertex3d(14, 5, startHeight);
	glVertex3d(14, 5, height);
	glVertex3d(12, -1, height);
	glVertex3d(12, -1, startHeight);


	double vectHigh5[] = { 12,-1,5 };
	glNormal3dv(normalize(G, F, vectHigh5));

	glVertex3d(12, -1, startHeight);
	glVertex3d(12, -1, height);
	glVertex3d(7, 1, height);
	glVertex3d(7, 1, startHeight);


	double vectHigh6[] = { 7,1,5 };
	glNormal3dv(normalize(H, G, vectHigh6));

	glVertex3d(7, 1, startHeight);
	glVertex3d(7, 1, height);
	glVertex3d(4, -2, height);
	glVertex3d(4, -2, startHeight);


	double vectHigh7[] = { 4,-2,5 };
	glNormal3dv(normalize(A, H, vectHigh7));

	glVertex3d(4, -2, startHeight);
	glVertex3d(4, -2, height);
	glVertex3d(0, 0, height);
	glVertex3d(0, 0, startHeight);

	glEnd();
}



void bulge_bases(double startHeight, double height) {

	double E[] = { 14, 5, startHeight };
	double F[] = { 12, -1, startHeight };

	int poly = 100;

	// �������� �����
	double center_circle_bottom[] = { (E[0] + F[0]) / 2, (E[1] + F[1]) / 2, startHeight };
	double center_circle_top[] = { (E[0] + F[0]) / 2, (E[1] + F[1]) / 2, height };
	double radius = sqrt(pow(F[0] - E[0], 2) + pow(F[1] - E[1], 2)) / 2;


	glPushMatrix();

	glTranslated(center_circle_bottom[0], center_circle_bottom[1], startHeight);
	glRotated(-90, 0, 0, 1);
	glRotated(-18.4, 0, 0, 1);

	glNormal3f(0, 0, -1);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, startHeight); //����� ���� �������������

	for (int i = 0; i < poly; i++) {
		double angle = 2.0f * 3.1415926f * double(i) / double(poly);

		if (angle <= 3.1415926f) {
			double x = radius * cos(angle);
			double y = radius * sin(angle);
			glVertex3d(x, y, 0);
		}

	}

	glEnd();
	glPopMatrix();



	glPushMatrix();

	glTranslated(center_circle_top[0], center_circle_top[1], height);
	glRotated(-90, 0, 0, 1);
	glRotated(-18.4, 0, 0, 1);


	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, 0); //����� ���� �������������

	for (int i = 0; i <= poly; i++) {
		double angle = 2.0f * 3.1415926f * double(i) / double(poly);
		if (angle <= 3.1415926f) {
			double x = radius * cos(angle);
			double y = radius * sin(angle);
			glVertex3d(x, y, 0);
		}
	}

	glEnd();
	glPopMatrix();

}





void bulge_sides(double startHeight, double height) {

	glColor3d(0.5, 0.5, 0.5);
	int poly = 20;
	//double circle_center[] = { 13, 2, (startHeight + height) / 2 };

	double radius = sqrt(10);
	double angle = 0;


	glPushMatrix();

	glTranslated(13, 2, 0);
	glRotated(-90, 0, 0, 1);
	glRotated(-18.4, 0, 0, 1);


	glBegin(GL_QUADS);

	for (int i = 0; i < poly; i++) {
		angle = 2.0f * 3.1415926f * double(i) / double(poly);


		double start_coord_bottom[] = { radius * cos(angle), radius * sin(angle), startHeight };
		double start_coord_top[] = { radius * cos(angle), radius * sin(angle), height };

		double next_angle = 2.0f * 3.1415926f * double(i + 1) / double(poly);

		double next_coord_bottom[] = { radius * cos(next_angle), radius * sin(next_angle), startHeight };
		double next_coord_top[] = { radius * cos(next_angle), radius * sin(next_angle), height };

		glNormal3dv(normalize(start_coord_bottom, next_coord_bottom, start_coord_top));

		if (angle <= 3.14) {
			glVertex3dv(start_coord_bottom);
			glVertex3dv(next_coord_bottom);
			glVertex3dv(next_coord_top);
			glVertex3dv(start_coord_top);
		}
	}
	glEnd();
	glPopMatrix();
}




void prizma(double startHeight, double height, int poly) {
	fund_bottom(startHeight);
	sides(startHeight, height);
	fund_top(height);

	bulge_bases(startHeight, height);
	bulge_sides(startHeight, height);
}











//����� ��� ��������� ������
class CustomCamera : public Camera
{
public:
	//��������� ������
	double camDist;
	//���� �������� ������
	double fi1, fi2;

	
	//������� ������ �� ���������
	CustomCamera()
	{
		camDist = 15;
		fi1 = 1;
		fi2 = 1;
	}

	
	//������� ������� ������, ������ �� ����� ��������, ���������� �������
	void SetUpCamera()
	{
		//�������� �� ������� ������ ������
		lookPoint.setCoords(0, 0, 0);

		pos.setCoords(camDist*cos(fi2)*cos(fi1),
			camDist*cos(fi2)*sin(fi1),
			camDist*sin(fi2));

		if (cos(fi2) <= 0)
			normal.setCoords(0, 0, -1);
		else
			normal.setCoords(0, 0, 1);

		LookAt();
	}

	void CustomCamera::LookAt()
	{
		//������� ��������� ������
		gluLookAt(pos.X(), pos.Y(), pos.Z(), lookPoint.X(), lookPoint.Y(), lookPoint.Z(), normal.X(), normal.Y(), normal.Z());
	}



}  camera;   //������� ������ ������


//����� ��� ��������� �����
class CustomLight : public Light
{
public:
	CustomLight()
	{
		//��������� ������� �����
		pos = Vector3(1, 1, 3);
	}

	
	//������ ����� � ����� ��� ���������� �����, ���������� �������
	void  DrawLightGhismo()
	{
		glDisable(GL_LIGHTING);

		
		glColor3d(0.9, 0.8, 0);
		Sphere s;
		s.pos = pos;
		s.scale = s.scale*0.08;
		s.Show();
		
		if (OpenGL::isKeyPressed('G'))
		{
			glColor3d(0, 0, 0);
			//����� �� ��������� ����� �� ����������
			glBegin(GL_LINES);
			glVertex3d(pos.X(), pos.Y(), pos.Z());
			glVertex3d(pos.X(), pos.Y(), 0);
			glEnd();

			//������ ���������
			Circle c;
			c.pos.setCoords(pos.X(), pos.Y(), 0);
			c.scale = c.scale*1.5;
			c.Show();
		}

	}

	void SetUpLight()
	{
		GLfloat amb[] = { 0.2, 0.2, 0.2, 0 };
		GLfloat dif[] = { 1.0, 1.0, 1.0, 0 };
		GLfloat spec[] = { .7, .7, .7, 0 };
		GLfloat position[] = { pos.X(), pos.Y(), pos.Z(), 1. };

		// ��������� ��������� �����
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		// �������������� ����������� �����
		// ������� ��������� (���������� ����)
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		// ��������� ������������ �����
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		// ��������� ���������� ������������ �����
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

		glEnable(GL_LIGHT0);
	}


} light;  //������� �������� �����




//������ ���������� ����
int mouseX = 0, mouseY = 0;

void mouseEvent(OpenGL *ogl, int mX, int mY)
{
	int dx = mouseX - mX;
	int dy = mouseY - mY;
	mouseX = mX;
	mouseY = mY;

	//������ ���� ������ ��� ������� ����� ������ ����
	if (OpenGL::isKeyPressed(VK_RBUTTON))
	{
		camera.fi1 += 0.01*dx;
		camera.fi2 += -0.01*dy;
	}

	
	//������� ���� �� ���������, � ����� ��� ����
	if (OpenGL::isKeyPressed('G') && !OpenGL::isKeyPressed(VK_LBUTTON))
	{
		LPPOINT POINT = new tagPOINT();
		GetCursorPos(POINT);
		ScreenToClient(ogl->getHwnd(), POINT);
		POINT->y = ogl->getHeight() - POINT->y;

		Ray r = camera.getLookRay(POINT->x, POINT->y);

		double z = light.pos.Z();

		double k = 0, x = 0, y = 0;
		if (r.direction.Z() == 0)
			k = 0;
		else
			k = (z - r.origin.Z()) / r.direction.Z();

		x = k*r.direction.X() + r.origin.X();
		y = k*r.direction.Y() + r.origin.Y();

		light.pos = Vector3(x, y, z);
	}

	if (OpenGL::isKeyPressed('G') && OpenGL::isKeyPressed(VK_LBUTTON))
	{
		light.pos = light.pos + Vector3(0, 0, 0.02*dy);
	}

	
}

void mouseWheelEvent(OpenGL *ogl, int delta)
{

	if (delta < 0 && camera.camDist <= 1)
		return;
	if (delta > 0 && camera.camDist >= 100)
		return;

	camera.camDist += 0.01*delta;

}

void keyDownEvent(OpenGL *ogl, int key)
{
	if (key == 'L')
	{
		lightMode = !lightMode;
	}

	if (key == 'T')
	{
		textureMode = !textureMode;
	}

	if (key == 'R')
	{
		camera.fi1 = 1;
		camera.fi2 = 1;
		camera.camDist = 15;

		light.pos = Vector3(1, 1, 3);
	}

	if (key == 'F')
	{
		light.pos = camera.pos;
	}
}

void keyUpEvent(OpenGL *ogl, int key)
{
	
}



GLuint texId;

//����������� ����� ������ ��������
void initRender(OpenGL *ogl)
{
	//��������� �������

	//4 ����� �� �������� �������
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//��������� ������ ��������� �������
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//�������� ��������
	glEnable(GL_TEXTURE_2D);
	

	//������ ����������� ���������  (R G B)
	RGBTRIPLE *texarray;

	//������ ��������, (������*������*4      4, ���������   ����, �� ������� ������������ �� 4 ����� �� ������� �������� - R G B A)
	char *texCharArray;
	int texW, texH;
	OpenGL::LoadBMP("texture.bmp", &texW, &texH, &texarray);
	OpenGL::RGBtoChar(texarray, texW, texH, &texCharArray);

	
	
	//���������� �� ��� ��������
	glGenTextures(1, &texId);
	//������ ��������, ��� ��� ����� ����������� � ���������, ����� ����������� �� ����� ��
	glBindTexture(GL_TEXTURE_2D, texId);

	//��������� �������� � �����������, � ���������� ��� ������  ��� �� �����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texCharArray);

	//�������� ������
	free(texCharArray);
	free(texarray);

	//������� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//������ � ���� ����������� � "������"
	ogl->mainCamera = &camera;
	ogl->mainLight = &light;

	// ������������ �������� : �� ����� ����� ����� 1
	glEnable(GL_NORMALIZE);

	// ���������� ������������� ��� �����
	glEnable(GL_LINE_SMOOTH); 


	//   ������ ��������� ���������
	//  �������� GL_LIGHT_MODEL_TWO_SIDE - 
	//                0 -  ������� � ���������� �������� ���������(�� ���������), 
	//                1 - ������� � ���������� �������������� ������� ��������       
	//                �������������� ������� � ���������� ��������� ����������.    
	//  �������� GL_LIGHT_MODEL_AMBIENT - ������ ������� ���������, 
	//                �� ��������� �� ���������
	// �� ��������� (0.2, 0.2, 0.2, 1.0)

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

	camera.fi1 = -1.3;
	camera.fi2 = 0.8;
}




void Render(OpenGL *ogl)
{


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	if (textureMode)
		glEnable(GL_TEXTURE_2D);

	if (lightMode)
		glEnable(GL_LIGHTING);


	//��������������
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//��������� ���������
	GLfloat amb[] = { 0.2, 0.2, 0.1, 1. };
	GLfloat dif[] = { 0.4, 0.65, 0.5, 1. };
	GLfloat spec[] = { 0.9, 0.8, 0.3, 1. };
	GLfloat sh = 0.1f * 256;


	//�������
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	//��������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	//����������
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec); 
		//������ �����
		glMaterialf(GL_FRONT, GL_SHININESS, sh);

	//���� ���� �������, ��� ����������� (����������� ���������)
	glShadeModel(GL_SMOOTH);
	//===================================
	//������� ���  


	//������ ��������� ���������� ��������

	//glBindTexture(GL_TEXTURE_2D, texId);

	//glColor3d(0.6, 0.6, 0.6);

	glScaled(0.3, 0.3, 0.3);
	prizma(0, 5, 200);


   //��������� ������ ������

	
	glMatrixMode(GL_PROJECTION);	//������ �������� ������� ��������. 
	                                //(���� ��������� ��������, ����� �� ������������.)
	glPushMatrix();   //��������� ������� ������� ������������� (������� ��������� ������������� ��������) � ���� 				    
	glLoadIdentity();	  //��������� ��������� �������
	glOrtho(0, ogl->getWidth(), 0, ogl->getHeight(), 0, 1);	 //������� ����� ������������� ��������

	glMatrixMode(GL_MODELVIEW);		//������������� �� �����-��� �������
	glPushMatrix();			  //��������� ������� ������� � ���� (��������� ������, ����������)
	glLoadIdentity();		  //���������� �� � ������

	glDisable(GL_LIGHTING);



	GuiTextRectangle rec;		   //������� ����� ��������� ��� ������� ������ � �������� ������.
	rec.setSize(300, 150);
	rec.setPosition(10, ogl->getHeight() - 150 - 10);


	std::stringstream ss;
	ss << "T - ���/���� �������" << std::endl;
	ss << "L - ���/���� ���������" << std::endl;
	ss << "F - ���� �� ������" << std::endl;
	ss << "G - ������� ���� �� �����������" << std::endl;
	ss << "G+��� ������� ���� �� ���������" << std::endl;
	ss << "�����. �����: (" << light.pos.X() << ", " << light.pos.Y() << ", " << light.pos.Z() << ")" << std::endl;
	ss << "�����. ������: (" << camera.pos.X() << ", " << camera.pos.Y() << ", " << camera.pos.Z() << ")" << std::endl;
	ss << "��������� ������: R="  << camera.camDist << ", fi1=" << camera.fi1 << ", fi2=" << camera.fi2 << std::endl;
	
	rec.setText(ss.str().c_str());
	rec.Draw();

	glMatrixMode(GL_PROJECTION);	  //��������������� ������� �������� � �����-��� �������� �� �����.
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}