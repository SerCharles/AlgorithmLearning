/*
filename: Sorts.h
description:definations of insert, merge, quick, shell and radix sort for uint
date: 3/25/2019
*/

#ifndef SORTS_H
#define SORTS_H

#include <iostream>

#define MAX 10000
#define MAX_UINT 4294967295
extern unsigned int g_NumList[MAX];
extern unsigned int auxiliary[MAX];
extern int remain[80000000];

extern void g_GenerateRandomNumbers(unsigned int num_list[], int num);

extern void g_InsertSort(unsigned int num_list[], int num);

extern void g_ShellSort(unsigned int num_list[], int num);

extern void g_MergeSort(unsigned int num_list[], int num);

extern void g_QuickSort(unsigned int num_list[], int num);

extern void g_RadixSort(unsigned int num_list[], int num);

extern int Partition(unsigned int num_list[], int start, int end);
#endif
