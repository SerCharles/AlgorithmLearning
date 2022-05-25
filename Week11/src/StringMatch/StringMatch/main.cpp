#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;

#include "StringMatch.h"

#define TEST_TIME 5

int test_size_n[8] = { 10,100,1000,10000,100000,1000000,10000000,100000000 };
int test_size_m[8] = { 2,5,10,20,50,100,300,1000 };

void g_TestRandom(int size_n, int size_m)
{
	int test_time = TEST_TIME;
	double time[5] = { 0 };


	bool whether_success = 1;
	for (int i = 1; i <= test_time; i++)
	{
		g_GenerateRandomString(size_n, g_CharList);
		g_GenerateRandomString(size_m, g_Model);
		time_t start, end;
		cout << "The size_n is " << size_n << endl;
		if (size_n <= 100)
		{
			cout << "The string is ";
			for (int i = 1; i <= size_n; i++) cout << g_CharList[i];
			cout << endl;
		}
		cout << "The size_m is " << size_m << endl;
		cout << "The model is ";
		for (int i = 1; i <= size_m; i++) cout << g_Model[i];
		cout << endl;

		{
			start = clock();
			g_MatchNaive(size_n, size_m);
			end = clock();
			double t = double(end - start) / double(test_time);
			time[0] += t;
			cout << "Naive Algorithm" << endl;
			cout << "Match Place: ";
			for (int i = 0; i < result_place_naive.size(); i++) cout << result_place_naive[i] << " ";
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
		}

		{
			start = clock();
			g_MatchRabinKarp(size_n, size_m);
			end = clock();
			double t = double(end - start) / double(test_time);
			time[1] += t;
			cout << "Rabin Karp Algorithm" << endl;
			cout << "Match Place: ";
			for (int i = 0; i < result_place_rabin_karp.size(); i++) cout << result_place_rabin_karp[i] << " ";
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
		}

		{
			start = clock();
			g_MatchDFA(size_n, size_m);
			end = clock();
			double t = double(end - start) / double(test_time);
			time[2] += t;
			cout << "DFA Algorithm" << endl;
			cout << "Match Place: ";
			for (int i = 0; i < result_place_dfa.size(); i++) cout << result_place_dfa[i] << " ";
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
		}

		{
			start = clock();
			g_MatchKMP(size_n, size_m);
			end = clock();
			double t = double(end - start) / double(test_time);
			time[3] += t;
			cout << "KMP Algorithm" << endl;
			cout << "Match Place: ";
			for (int i = 0; i < result_place_kmp.size(); i++) cout << result_place_kmp[i] << " ";
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
		}
		{
			start = clock();
			g_MatchBoyerMoore(size_n, size_m);
			end = clock();
			double t = double(end - start) / double(test_time);
			time[4] += t;
			cout << "Boyer-Moore Algorithm" << endl;
			cout << "Match Place: ";
			for (int i = 0; i < result_place_boyer_moore.size(); i++) cout << result_place_boyer_moore[i] << " ";
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
		}
		if (!g_JudgeSuccess())
		{
			whether_success = 0;
		}
	}
	cout << "Naive Algorithm uses average time of " << time[0] << " ms" << endl;
	cout << "Rabin Karp Algorithm uses average time of " << time[1] << " ms" << endl;
	cout << "DFA Algorithm uses average time of " << time[2] << " ms" << endl;
	cout << "KMP Algorithm uses average time of " << time[3] << " ms" << endl;
	cout << "Boyer-Moore Algorithm uses average time of " << time[4] << " ms" << endl;
	if (whether_success == 1)
	{
		cout << "The answers are all right" << endl;
	}
	else
	{
		cout << "The answers are wrong" << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------" << endl;

}


int main()
{
	for (int i = 0; i < 8; i++)
	{
		g_TestRandom(test_size_n[i], test_size_m[1]);
	}
	for (int i = 0; i < 8; i++)
	{
		g_TestRandom(test_size_n[6], test_size_m[i]);
	}
	cout << "The program is end now, you can quit it manually" << endl;
	while (1);
}