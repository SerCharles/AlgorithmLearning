/*
filename: NGenerateRandomPoint.h
description: define point in two_dimension point and Generate random points
*/
#ifndef NGENERATERANDOMPOINT_H
#define NGENERATERANDOMPOINT_H




class NPoint
{
private:
	double m_Place_x{ 0 }, m_Place_y{ 0 };
public:
	NPoint(double x, double y) :m_Place_x(x), m_Place_y(y) {}
	friend double g_GetDistance(NPoint a, NPoint b)
	{
		double dx = a.m_Place_x - b.m_Place_x;
		double dy = a.m_Place_y - b.m_Place_y;
		return (dx * dx + dy * dy);
	}
	int m_Compare_x(NPoint b)
	{
		if (m_Place_x < b.m_Place_x) return -1;
		else if (m_Place_x == b.m_Place_x) return 0;
		else return 1;
	}
	int m_Compare_y(NPoint b)
	{
		if (m_Place_y < b.m_Place_y) return -1;
		else if (m_Place_y == b.m_Place_y) return 0;
		else return 1;
	}
	void m_GetPlace(double& x, double& y)
	{
		x = m_Place_x;
		y = m_Place_y;
	}
};


//generate random points of total num in(0,0) to (range_x,range_y)
extern void g_GenerateRandomPoint(vector<NPoint>& point_list, int total_num, int range_x, int range_y);




#endif