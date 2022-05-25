/*
filename: MultiSorts.h
description:definations of merge and quick sort of multithread
date: 6/3/2019
*/

#ifndef MULTISORTS_H
#define MULTISORTS_H

#include <iostream>
#include <omp.h>

#define LEAST_RECUR_SIZE 5



extern void g_MergeSortMultiThread(unsigned int num_list[], int num);

extern void g_QuickSortMultiThread(unsigned int num_list[], int num);
#endif

