/*
filename: NGetNearPoint.h
description: two algorithms of getting the nearest two points:n^2 or nlgn
*/

#ifndef NGETNEARPOINT_H
#define NGETNEARPOINT_H


extern void g_GetNearPointBrutal(vector<NPoint>& point_list, double& place_x_1, double& place_y_1,
	double& place_x_2, double& place_y_2, double& distance);


extern void g_GetNearPointRecursion(vector<NPoint>& point_list, double& place_x_1, double& place_y_1,
	double& place_x_2, double& place_y_2, double& distance);




#endif