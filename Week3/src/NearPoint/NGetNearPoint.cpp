/*
filename: NGetNearPoint.cpp
description: two algorithms of getting the nearest two points:n^2 or nlgn
*/

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
using namespace std;

#include "NGenerateRandomPoint.h"
#include "NGetNearPoint.h"

#define MAX 1145141919810

#define MIN_NUM 20

vector<int> PlaceX, PlaceY;

int min(int a, int b)
{
	if (a <= b) return a;
	else return b;
}

void g_GetNearPointBrutal(vector<NPoint>& point_list, double& place_x_1, double& place_y_1, double& place_x_2, double& place_y_2, double& distance)
{
	double min_dist = MAX;
	for (int i = 0; i < point_list.size() - 1; i++)
	{
		for (int j = i + 1; j < point_list.size(); j++)
		{
			double the_dist = g_GetDistance(point_list[i], point_list[j]);
			if (the_dist < min_dist)
			{
				point_list[i].m_GetPlace(place_x_1, place_y_1);
				point_list[j].m_GetPlace(place_x_2, place_y_2);
				min_dist = the_dist;
			}
		}
	}
	distance = sqrt(min_dist);
}

vector<int> stack_begin,stack_end,stack_middle;



void SortByX(vector<NPoint>& point_list, vector<int> & place_x)
{
	stack_begin.clear(); stack_end.clear(); stack_middle.clear();
	int start = 0, end = point_list.size() - 1;

	while (1)
	{
		if (start < end && start >= 0 && end >= 0 && start < point_list.size() && end < point_list.size())
		{
			NPoint criterion = point_list[place_x[start]];
			int criterion_x = place_x[start];

			int low = start, high = end;
			while (low < high)
			{
				while (point_list[place_x[high]].m_Compare_x(criterion) >= 0 && low < high)
				{
					high--;
				}
				if (low < high)
				{
					place_x[low] = place_x[high];
					low++;
				}
				while (point_list[place_x[low]].m_Compare_x(criterion) <= 0 && low < high)
				{
					low++;
				}
				if (low < high)
				{
					place_x[high] = place_x[low];
					high--;
				}
			}
			place_x[high] = criterion_x;
			stack_begin.push_back(start);
			stack_middle.push_back(high);
			stack_end.push_back(end);
			start = start;
			end = high - 1;
		}
		else
		{
			if (stack_begin.empty()) break;
			else
			{
				start = stack_middle[stack_middle.size () - 1] + 1;
				end = stack_end[stack_middle.size() - 1];
				stack_begin.pop_back();
				stack_end.pop_back();
				stack_middle.pop_back();
			}
		}
	}
}

void SortByY(vector<NPoint>& point_list, vector<int> & place_y)
{
	stack_begin.clear(); stack_end.clear(); stack_middle.clear();
	int start = 0, end = point_list.size() - 1;

	while (1)
	{
		if (start < end && start >= 0 && end >= 0 && start < point_list.size() && end < point_list.size())
		{
			NPoint criterion = point_list[place_y[start]];
			int criterion_y = place_y[start];
			int low = start, high = end;
			while (low < high)
			{
				while (point_list[place_y[high]].m_Compare_y(criterion) >= 0 && low < high)
				{
					high--;
				}
				if (low < high)
				{
					place_y[low] = place_y[high];
					low++;
				}
				while (point_list[place_y[low]].m_Compare_y(criterion) <= 0 && low < high)
				{
					low++;
				}
				if (low < high)
				{
					place_y[high] = place_y[low];
					high--;
				}
			}
			place_y[high] = criterion_y;
			stack_begin.push_back(start);
			stack_middle.push_back(high);
			stack_end.push_back(end);
			start = start;
			end = high - 1;
		}
		else
		{
			if (stack_begin.empty()) break;
			else
			{
				start = stack_middle.back() + 1;
				end = stack_end.back();
				stack_begin.pop_back();
				stack_end.pop_back();
				stack_middle.pop_back();
			}
		}
	}
}

void GetNearPoint(vector<NPoint>& point_list, vector<int> place_x, vector<int> place_y, int start, int end, 
	int& place_in_pointlist_1,int& place_in_pointlist_2, double& distance)
{
	if (end - start + 1 <= MIN_NUM)
	{
		double min_dist = MAX;
		//brutalforce
		for (int i = start; i < end; i++)
		{
			for (int j = i + 1; j <= end; j++)
			{
				double the_dist = g_GetDistance(point_list[place_x[i]], point_list[place_x[j]]);
				if (the_dist < min_dist)
				{
					place_in_pointlist_1 = place_x[i];
					place_in_pointlist_2 = place_x[j];
					min_dist = the_dist;
				}
			}
		}
		distance = min_dist;
	}
	else
	{
		//recursion
		int place_left_1 = 0, place_left_2 = 0, place_right_1 = 0, place_right_2 = 0,
			place_middle_1 = 0, place_middle_2 = 0;
		double min_dist_left = MAX, min_dist_right = MAX, min_dist_middle = MAX;
		int middle = (start + end) / 2;
		double min_dist = MAX;

		//divide and conquer
		GetNearPoint(point_list, place_x, place_y, start, middle, place_left_1, place_left_2, min_dist_left);
		GetNearPoint(point_list, place_x, place_y, middle + 1, end, place_right_1, place_right_2, min_dist_right);


		//merge
		for (int i = 0; i < point_list.size(); i++)
		{
			int stop = min(i + 7, point_list.size() - 1);
			for (int j = i + 1; j <= stop; j++)
			{
				double dist = g_GetDistance(point_list[place_y[i]], point_list[place_y[j]]);
				if (dist < min_dist_middle)
				{
					min_dist_middle = dist;
					place_middle_1 = place_y[i];
					place_middle_2 = place_y[j];
				}
			}
		}

		if (min_dist_left < min_dist_right)
		{
			min_dist = min_dist_left;
			place_in_pointlist_1 = place_left_1;
			place_in_pointlist_2 = place_left_2;
		}
		else
		{
			min_dist = min_dist_right;
			place_in_pointlist_1 = place_right_1;
			place_in_pointlist_2 = place_right_2;
		}

		if (min_dist_middle < min_dist)
		{
			min_dist = min_dist_middle;
			place_in_pointlist_1 = place_middle_1;
			place_in_pointlist_2 = place_middle_2;
		}
		distance = min_dist;
	}
}

void g_GetNearPointRecursion(vector<NPoint>& point_list, double& place_x_1, double& place_y_1, 
	double& place_x_2, double& place_y_2, double& distance)
{
	PlaceX.clear(); PlaceY.clear();
	for (int i = 0; i < point_list.size(); i++)
	{
		PlaceX.push_back(i);
		PlaceY.push_back(i);
	}
	SortByX(point_list, PlaceX);
	SortByY(point_list, PlaceY);

	int place_in_pointlist_1 = 0, place_in_pointlist_2 = 0;
	double dist = MAX;
	GetNearPoint(point_list,PlaceX, PlaceY, 0 ,point_list.size() - 1,
		place_in_pointlist_1, place_in_pointlist_2, dist);
	point_list[place_in_pointlist_1].m_GetPlace(place_x_1, place_y_1);
	point_list[place_in_pointlist_2].m_GetPlace(place_x_2, place_y_2);
	distance = sqrt(dist);
}
