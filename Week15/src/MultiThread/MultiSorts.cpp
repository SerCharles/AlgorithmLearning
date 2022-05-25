/*
filename: MultiSorts.cpp
description:definations of merge and quick sort in multithread mode
date: 6/3/2019
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <omp.h>
using namespace std;

#include "Sorts.h"
#include "MultiSorts.h"


void g_MergeSortMultiThread(unsigned int num_list[], int num)
{
	if (num <= LEAST_RECUR_SIZE)
	{
		//brute force
		for (int i = 0; i < num - 1; i++)
		{
			for (int j = i + 1; j < num; j++)
			{
				if (num_list[i] > num_list[j])
				{
					unsigned int temp = num_list[i];
					num_list[i] = num_list[j];
					num_list[j] = temp;
				}
			}
		}
	}
	else
	{
		int middle = num / 2;
		int size_1 = middle;
		int size_2 = num - middle;

		unsigned int* array_1 = new unsigned int[size_1];
		unsigned int* array_2 = new unsigned int[size_2];

		for (int i = 0; i < size_1; i++)
		{
			array_1[i] = num_list[i];
		}
		for (int i = 0; i < size_2; i++)
		{
			array_2[i] = num_list[middle + i];
		}

		#pragma omp parallel default(none) shared(array_1,array_2,size_1,size_2) 
		{
			g_MergeSortMultiThread(array_1, size_1);

			g_MergeSortMultiThread(array_2, size_2);
			#pragma omp barrier

		}

		//merge
		int flag_1 = 0, flag_2 = 0;
		int i = 0;
		while(i < num)
		{
			int nova = 0;
			if (flag_1 >= size_1)
			{
				nova = array_2[flag_2];
				flag_2++;
			}
			else if (flag_2 >= size_2)
			{
				nova = array_1[flag_1];
				flag_1++;
			}
			else if (array_1[flag_1] < array_2[flag_2])
			{
				nova = array_1[flag_1];
				flag_1++;
			}
			else
			{
				nova = array_2[flag_2];
				flag_2++;
			}
			num_list[i] = nova;
			i++;
		}

		delete(array_1);
		delete(array_2);
	}
}

void g_QuickSortMultiThread(unsigned int num_list[], int num)
{
	
	int middle = 0;
	if (num <= LEAST_RECUR_SIZE)
	{
		//brute force
		for (int i = 0; i < num - 1; i++)
		{
			for (int j = i + 1; j < num; j++)
			{
				if (num_list[i] > num_list[j])
				{
					unsigned int temp = num_list[i];
					num_list[i] = num_list[j];
					num_list[j] = temp;
				}
			}
		}
	}
	else
	{


		middle = Partition(num_list, 0, num - 1);
		int size_1 = middle;
		int size_2 = num - 1 - middle;
		unsigned int* array_1 = new unsigned int[size_1];
		unsigned int* array_2 = new unsigned int[size_2];
		
		//#pragma omp parallel for
		for (int i = 0; i < size_1; i++)
		{
			array_1[i] = num_list[i];
		}
		//#pragma omp parallel for
		for (int i = 0; i < size_2; i++)
		{
			array_2[i] = num_list[middle + 1 + i];
		}


		#pragma omp parallel default(none) shared(array_1,array_2,size_1,size_2) 
		{
			g_QuickSortMultiThread(array_1, size_1);

			g_QuickSortMultiThread(array_2, size_2);
			#pragma omp barrier

		}

		//#pragma omp parallel for
		for (int i = 0; i < size_1; i++)
		{
			num_list[i] = array_1[i];
		}
		//#pragma omp parallel for
		for (int i = 0; i < size_2; i++)
		{
			num_list[middle + 1 + i] = array_2[i];
		}
		delete(array_1); delete(array_2);
	}


}