#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <Windows.h>

//opengl
#include <GL/GL.h>
#include <GL/GLU.h>
#include <gl/glut.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glut32.lib")
using namespace std;

#include "NGenerateRandomPoint.h"
#include "NGetNearPoint.h"

#define TEST_TIME 10
#define NUM 300
#define RANGE_X 1920
#define RANGE_Y 1080
#define SHOW_X 800
#define SHOW_Y 800



vector<NPoint> PointList;
int g_MouseX, g_MouseY;
bool g_MouseDown = 0;
bool visit[SHOW_X + 1][SHOW_Y + 1] = { 0 };
bool JudgeSame(double x1, double y1, double x2, double y2,
	double x3, double y3, double x4, double y4, double ans1, double ans2)
{
	if (ans1 != ans2) return 0;
	return 1;
}

void GetShowPlace(double x0, double y0, double& x1, double& y1)
{
	x1 = double(x0 - SHOW_X / 2) / double(SHOW_X / 2);
	y1 = double(SHOW_X/ 2 - y0) / double(SHOW_X / 2);
}

void RandomProcess()
{
	g_GenerateRandomPoint(PointList, NUM, RANGE_X, RANGE_Y);
	bool whether_right = 1;

	time_t recur_start, recur_end, brutal_start, brutal_end;
	double time_recur = 0, time_brutal = 0;
	double place_x_1_crit = 0, place_y_1_crit = 0,
		place_x_2_crit = 0, place_y_2_crit = 0, distance_crit = 0;

	{
		cout << "Now begin recurrence" << endl;
		recur_start = clock();
		for (int i = 0; i < TEST_TIME; i++)
		{
			cout << "Recurrence group " << i + 1 << endl;
			double place_x_1 = 0, place_y_1 = 0,
				place_x_2 = 0, place_y_2 = 0, distance = 0;
			g_GetNearPointRecursion(PointList, place_x_1, place_y_1, place_x_2, place_y_2, distance);
			cout << "The two points are (" << place_x_1 << ", " << place_y_1 << ") and ("
				<< place_x_2 << ", " << place_y_2 << ")\n";
			cout << "The minimum distance is " << distance << endl;
			if (i == 0)
			{
				place_x_1_crit = place_x_1;
				place_x_2_crit = place_x_2;
				place_y_1_crit = place_y_1;
				place_y_2_crit = place_y_2;
				distance_crit = distance;
			}
			else
			{
				if (!JudgeSame(place_x_1, place_y_1, place_x_2, place_y_2, place_x_1_crit,
					place_y_1_crit, place_x_2_crit, place_y_2_crit, distance, distance_crit))
				{
					whether_right = 0;
				}
			}
		}
		recur_end = clock();
		time_recur = double(recur_end - recur_start) / double(TEST_TIME);
		cout << "Recurrence spends " << time_recur << " time in average" << endl;
		cout << "\n";
	}

	{
		cout << "Now begin brutal" << endl;
		brutal_start = clock();
		for (int i = 0; i < TEST_TIME; i++)
		{
			cout << "Brutal group " << i + 1 << endl;
			double place_x_1 = 0, place_y_1 = 0,
				place_x_2 = 0, place_y_2 = 0, distance = 0;
			g_GetNearPointBrutal(PointList, place_x_1, place_y_1, place_x_2, place_y_2, distance);
			cout << "The two points are (" << place_x_1 << ", " << place_y_1 << ") and ("
				<< place_x_2 << ", " << place_y_2 << ")\n";
			cout << "The minimum distance is " << distance << endl;

			if (!JudgeSame(place_x_1, place_y_1, place_x_2, place_y_2, place_x_1_crit,
				place_y_1_crit, place_x_2_crit, place_y_2_crit, distance, distance_crit))
			{
				whether_right = 0;
			}
		}
		brutal_end = clock();
		time_brutal = double(brutal_end - brutal_start) / double(TEST_TIME);
		cout << "Brutal spends " << time_brutal << " time in average" << endl;
		cout << "\n";
	}
	if (whether_right == 1) cout << "The answer is right." << endl;
	else cout << "The answer is wrong." << endl;
	cout << "The program will end in 10 seconds" << endl;
	Sleep(10000);


}

void g_ControlClick(int button, int state, int x, int y)
{
	g_MouseX = x;
	g_MouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			g_MouseDown = true;
			if (visit[x][y] == 0)
			{
				visit[x][y] = 1;
				NPoint new_point(x, y);
				PointList.push_back(new_point);


				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				for (int i = 0; i < PointList.size(); i++)
				{
					NPoint current = PointList[i];
					double a = 0, b = 0;
					double show_a = 0, show_b = 0;
					current.m_GetPlace(a, b);
					GetShowPlace(a, b, show_a, show_b);
					glColor3f(1.0f, 1.0f, 1.0f);


					glTranslatef(show_a, show_b, 0);
					glutSolidCube(0.01);
					glTranslatef(-show_a, -show_b, 0);
				}


				if (PointList.size() >= 2)
				{
					double place_x_1 = 0, place_y_1 = 0,
						place_x_2 = 0, place_y_2 = 0, distance = 0;
					double show_x_1 = 0, show_y_1 = 0,
						show_x_2 = 0, show_y_2 = 0;
					g_GetNearPointRecursion(PointList, place_x_1, place_y_1, place_x_2, place_y_2, distance);
					GetShowPlace(place_x_1, place_y_1, show_x_1, show_y_1);
					GetShowPlace(place_x_2, place_y_2, show_x_2, show_y_2);

					glColor3f(1.0f, 0.0f, 0.0f);
					glTranslatef(show_x_1, show_y_1, 0);
					glutSolidCube(0.01);
					glTranslatef(-show_x_1, -show_y_1, 0);

					glTranslatef(show_x_2, show_y_2, 0);
					glutSolidCube(0.01);
					glTranslatef(-show_x_2, -show_y_2, 0);

					glBegin(GL_LINE);
					glVertex3d(show_x_1, show_y_1,0);
					glVertex3d(show_x_2, show_y_2,0);
					glEnd();

				}
				//Sleep(100);
				glutSwapBuffers();
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			for (int i = 0; i < SHOW_X + 1; i++)
			{
				for (int j = 0; j < SHOW_Y + 1; j++)
				{
					visit[i][j] = 0;
				}
			}
			PointList.clear();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSwapBuffers();
		}
		else
		{
			g_MouseDown = 0;
		}
	}
	else
	{
		g_MouseDown = 0;
	}
}


void MyDisplay()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	for (int i = 0; i < PointList.size(); i++)
	{
		NPoint current = PointList[i];
		double a = 0, b = 0;
		double show_a = 0, show_b = 0;
		current.m_GetPlace(a, b);
		GetShowPlace(a, b, show_a, show_b);
		glColor3f(1.0f, 1.0f, 1.0f);

		
		glTranslatef(show_a, show_b, 0);
		glutSolidCube(0.01);
		glTranslatef(-show_a, -show_b, 0);
	}

	
	if (PointList.size() >= 2)
	{
		double place_x_1 = 0, place_y_1 = 0,
			place_x_2 = 0, place_y_2 = 0, distance = 0;
		double show_x_1 = 0, show_y_1 = 0,
			show_x_2 = 0, show_y_2 = 0;
		g_GetNearPointRecursion(PointList, place_x_1, place_y_1, place_x_2, place_y_2, distance);
		GetShowPlace(place_x_1, place_y_1, show_x_1, show_y_1);
		GetShowPlace(place_x_2, place_y_2, show_x_2, show_y_2);

		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(show_x_1, show_y_1, 0);
		glutSolidCube(0.01);
		glTranslatef(-show_x_1, -show_y_1, 0);

		glTranslatef(show_x_2, show_y_2, 0);
		glutSolidCube(0.01);
		glTranslatef(-show_x_2, -show_y_2, 0);

		glBegin(GL_LINE);
		glVertex2d(show_x_1, show_y_1);
		glVertex2d(show_x_2, show_y_2);
		glEnd();

	}
	//Sleep(100);
	glutSwapBuffers();
}

int main(int argc, char * argv[])
{
	bool whether_enter;
	cout << "Input 0 to start random testing, or input 1 to start the OpenGL menu" << endl;
	cin >> whether_enter;
	if (whether_enter)
	{
		//g_GenerateRandomPoint(PointList, NUM, SHOW_X, SHOW_Y);

		//initiate opengl
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowPosition(300, 0);
		glutInitWindowSize(SHOW_X, SHOW_Y);
		glutCreateWindow("GetNearestPoint");
		glutDisplayFunc(&MyDisplay);
		glutMouseFunc(&g_ControlClick);

		glutMainLoop();
	}
	else
	{
		RandomProcess();
	}
	return 0;
}