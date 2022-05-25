/*
filename: NGenerateRandomPoint.cpp
description: define point in two_dimension point and Generate random points
*/

#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

#include "NGenerateRandomPoint.h"

bool visit[RAND_MAX + 1][RAND_MAX + 1] = { 0 };

void g_GenerateRandomPoint(vector<NPoint>& point_list, int total_num, int range_x, int range_y)
{
	for (int i = 1; i <= total_num; i++)
	{
		if (i % 100 == 1)
		{
			srand((int)time(0));                      //change the seed, avoid repetation
		}

		int rand_x = 0, rand_y = 0;
		do
		{
			rand_x = rand();
			rand_y = rand();
		} while (visit[rand_x][rand_y] == 1);
		visit[rand_x][rand_y] = 1;

		double dx = double(range_x) / double(RAND_MAX);
		double dy = double(range_y) / double(RAND_MAX);

		NPoint new_point(rand_x * dx, rand_y * dy);
		point_list.push_back(new_point);
	}
}