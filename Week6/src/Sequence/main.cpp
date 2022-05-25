#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;

#include "cp_integer.h"

#define MAX 100000000
#define MAX_NUM 2147483647
int g_NumList[MAX + 1];
int g_Min[MAX + 1];
int g_Sequence[MAX + 1] = { 0 };
int g_Previous[MAX + 1] = { 0 };
vector<int> g_AnsList;
//return the first i > number, list is increasing
int g_BinarySearch(int list[], int start, int end,int number)
{
	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (list[mid] > number)
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}
	return end + 1;
}

void g_GenerateRandomNumbers(int num_list[], int num)
{
	//srand((int)time);
	for (int i = 0; i < num; i++)
	{
		unsigned int trigger_1 = 1 << 15, trigger_2 = 1 << 30;
		num_list[i] = rand() * trigger_2 + rand() * trigger_1 + rand();
		if (num_list[i] == MAX_NUM) num_list[i] = 0;
	}
}

int g_Nums[9] = { 0,10,100,1000,10000,100000,1000000,10000000,100000000};
#define TEST_TIME 5

int main()
{
	int ans = 0;
	cout << "Please input an integer of 0 or 1" << endl;
	cout << "Input 0 to enter time test with randomly generated numbers"<<endl;
	cout << "Input 1 to input your own data to test" << endl;
	cp_integer a;
	a.input(0, 1);
	if (a.get() == 0)
	{
		cout << "Please input an integer i between 1 and 8, which means the size of the random test is 10^i" << endl;
		cp_integer pp;
		pp.input(1, 8);
		int n;
		n = g_Nums[pp.get()];
		time_t start, end;
		start = clock();
		cout << "The size of the data is " << n << endl;
		for (int ii = 0; ii < TEST_TIME; ii++)
		{
			g_GenerateRandomNumbers(g_NumList, n);
			for (int i = 1; i <= n; i++)
			{
				g_Min[i] = MAX_NUM;
			}
			for (int i = 1; i <= n; i++)
			{
				int place = g_BinarySearch(g_Min, 1, i, g_NumList[i]);
				g_Min[place] = g_NumList[i];
			}
			for (int i = n; i >= 1; i--)
			{
				if (g_Min[i] != MAX_NUM)
				{
					ans = i;
					break;
				}
			}
			cout << "The max length of the " << ii << " th data is " << ans << endl;
		}
		end = clock();
		cout << "The average time is " << double(end - start) / TEST_TIME << " ms" << endl;
	}
	else
	{
		int n;
		cout << "Please input a positive integer between 1 and 100000, which is the number of the num list" << endl;
		cp_integer nn;
		nn.input(1, 100000);
		n = nn.get();
		cout << "Now please input n integers, which are separated by one space." << endl;
		cout << "Additionally, please not input 2147483647" << endl;
		for (int i = 1; i <= n; i++)
		{
			cin >> g_NumList[i];
			g_Min[i] = MAX_NUM;
		}


		for (int i = 1; i <= n; i++)
		{
			int place = g_BinarySearch(g_Min, 1, i, g_NumList[i]);
			g_Min[place] = g_NumList[i];
			g_Sequence[place] = i;
			g_Previous[i] = g_Sequence[place - 1];
		}
		for (int i = n; i >= 1; i--)
		{
			if (g_Min[i] != MAX_NUM)
			{
				ans = i;
				break;
			}
		}
		int current = g_Sequence[ans];
		while (current >= 1)
		{
			g_AnsList.push_back(g_NumList[current]);
			current = g_Previous[current];
		}
		cout << "The max length of the sequence you want is "<< ans << endl;
		cout << "One sequence is below" << endl;
		for (int i = g_AnsList.size() - 1; i >= 0; i--)
		{
			cout << g_AnsList[i] << " ";
		}
		cout << "\n" << endl;
		g_AnsList.clear();
	}
	cout << "The program will be quit in 10 seconds" << endl;
	Sleep(10000);
	return 0;
}