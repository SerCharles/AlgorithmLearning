/*
description: string match functions, include naive, rabin-karp,kmp,DFA,boy-moore
filename:StringMatch.cpp
date:4/30/2019
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;

#include "StringMatch.h"

char g_CharList[SIZE_N + 1] = { 0 };
char g_Model[SIZE_M + 1] = { 0 };

int g_Delta[SIZE_M + 1][CHARACTER] = { 0 };
int g_Pi[SIZE_M + 1] = { 0 };

vector<int> result_place_naive;
vector<int> result_place_rabin_karp;
vector<int> result_place_kmp;
vector<int> result_place_dfa;
vector<int> result_place_boyer_moore;


char g_Char(int num)
{
	if (num >= 0 && num <= 9)
	{
		return '0' + num;
	}
	else if (num >= 10 && num <= 35)
	{
		return num - 10 + 'a';
	}
	else if (num >= 36 && num <= 61)
	{
		return num - 36 + 'A';
	}
	else if (num == 62) return '(';
	else if (num == 63) return ')';
	else if (num == 64) return '[';
	else if (num == 65) return ']';
	else if (num == 66) return '{';
	else if (num == 67) return '}';
	else if (num == 68) return ',';
	else if (num == 69) return '.';
	else if (num == 70) return ';';
	else if (num == 71) return '-';
}

int g_Int(char c)
{
	if ('0' <= c && c <= '9')
	{
		return c - '0';
	}
	else if ('a' <= c && c <= 'z')
	{
		return 10 + c - 'a';
	}
	else if ('A' <= c && c <= 'Z')
	{
		return 36 + c - 'A';
	}
	else if (c == '(') return 62;
	else if (c == ')') return 63;
	else if (c == '[') return 64;
	else if (c == ']') return 65;
	else if (c == '{') return 66;
	else if (c == '}') return 67;
	else if (c == ',') return 68;
	else if (c == '.') return 69;
	else if (c == ';') return 70;
	else if (c == '-') return 71;
    else return -1;
}

void g_GenerateRandomString(int num, char list[])
{
	for (int i = 1; i <= num; i++)
	{
		int rd = rand() % CHARACTER;
		list[i] = g_Char(rd);
	}
}

bool g_JudgeSame(char list[], char model[], int num)
{
	for (int i = 0; i < num; i++)
	{
		if (list[i] != model[i])
		{
			return 0;
		}
	}
	return 1;
}

void g_MatchNaive(int num_list, int num_model)
{
	result_place_naive.clear();
	int i = 0, j = 0;
	for (int i = 1; i <= num_list - num_model + 1; i++)
	{
		bool whether_success = g_JudgeSame(&g_CharList[i], &g_Model[1], num_model);
		if (whether_success == 1)
		{
			result_place_naive.push_back(i);
		}
	}
}

void g_MatchRabinKarp(int num_list, int num_model)
{
	result_place_rabin_karp.clear();
	//calculate the key of the model
	int key_model = 0;
	int list_model = 0;
	int indicator = 1;
	for (int i = 1; i <= num_model; i++)
	{
		key_model *= CHARACTER;
		key_model += g_Int(g_Model[i]);
		list_model *= CHARACTER;
		list_model += g_Int(g_CharList[i]);
		if (i != 1) indicator = (indicator * CHARACTER);
	}
	for (int i = 1; i <= num_list - num_model + 1; i++)
	{
		if (key_model == list_model)
		{
			bool whether_success = g_JudgeSame(&g_CharList[i], &g_Model[1], num_model);
			if (whether_success == 1)
			{
				result_place_rabin_karp.push_back(i);
			}
		}
		int minus = (g_Int(g_CharList[i]) * indicator);
		list_model -= minus;
		list_model *= CHARACTER;
		list_model += g_Int(g_CharList[i + num_model]);
	}
}

void g_GetPi(int num)
{
	g_Pi[1] = 0;
	int k = 0;
	for (int q = 2; q <= num; q++)
	{
		while (k > 0 && g_Model[k + 1] != g_Model[q])
		{
			k = g_Pi[k];
		}
		if (g_Model[k + 1] == g_Model[q])
		{
			k++;
		}
		g_Pi[q] = k;
	}
}

void g_GetDelta(int num)
{
	g_GetPi(num);
	for (int i = 0; i < CHARACTER; i++)
	{
		if (g_Int(g_Model[1]) == i)
		{
			g_Delta[0][i] = 1;
		}
		else
		{
			g_Delta[0][i] = 0;
		}
	}
	for (int i = 1; i <= num; i++)
	{
		for (int j = 0; j < CHARACTER; j++)
		{
			if (i != num && g_Int(g_Model[i + 1]) == j)
			{
				g_Delta[i][j] = i + 1;
			}
			else
			{
				g_Delta[i][j] = g_Delta[g_Pi[i]][j];
			}
		}
	}
}

void g_MatchDFA(int num_list, int num_model)
{
	result_place_dfa.clear();
	g_GetDelta(num_model);
	int status = 0;
	for (int i = 1; i <= num_list; i++)
	{
		status = g_Delta[status][g_Int(g_CharList[i])];
		if (status == num_model)
		{
			result_place_dfa.push_back(i - num_model + 1);
		}
	}
}

void g_MatchKMP(int num_list, int num_model)
{
	result_place_kmp.clear();
	g_GetPi(num_model);
	int q = 0;
	for (int i = 1; i <= num_list; i++)
	{
		while (q > 0 && g_Model[q + 1] != g_CharList[i])
		{
			q = g_Pi[q];
		}
		if (g_Model[q + 1] == g_CharList[i])
		{
			q++;
		}
		if (q == num_model)
		{
			result_place_kmp.push_back(i - num_model + 1);
			q = g_Pi[q];
		}
	}
}


int g_OSuff[SIZE_M + 1] = { 0 };
int g_BMBC[CHARACTER] = { 0 };
int g_BMGS[SIZE_M + 1] = { 0 };

void g_GetBMBC(int num_model)
{
	for (int i = 0; i < CHARACTER; i++)
	{
		g_BMBC[i] = num_model;
	}
	for (int i = 1; i <= num_model - 1; i++)
	{
		g_BMBC[g_Int(g_Model[i])] = num_model - i;
	}
}

void g_GetOSuff(int num_model)
{
	int f, g;
	g_OSuff[num_model] = num_model;
	g = num_model;
	f = num_model - 1;
	for (int i = num_model - 1; i >= 1; i--)
	{
		if (i > g && g_OSuff[i + num_model - f] < i - g)
		{
			g_OSuff[i] = g_OSuff[i + num_model - f];
		}
		else
		{
			if (i < g)
			{
				g = i;
			}
			f = i;
			while (g >= 0 && g_Model[g] == g_Model[g + num_model - f])
			{
				g--;
			}
			g_OSuff[i] = f - g;
		}
	}
}

void g_GetBMGS(int num_model)
{
	g_GetOSuff(num_model);
	for (int i = 1; i <= num_model; i++)
	{
		g_BMGS[i] = num_model;
	}
	int j = 1;
	for (int i = num_model - 1; i >= 1; i--)
	{
		if (g_OSuff[i] == i)
		{
			while (j <= num_model - i)
			{
				if (g_BMGS[j] == num_model)
				{
					g_BMGS[j] -= i;
				}
				j++;
			}
		}
	}
	for (int i = 1; i <= num_model - 1; i++)
	{
		g_BMGS[num_model - g_OSuff[i]] = num_model - i;
	}
}

void g_MatchBoyerMoore(int num_list, int num_model)
{
	result_place_boyer_moore.clear();
	g_GetBMBC(num_model);
	g_GetBMGS(num_model);
	int s = 0;
	while (s <= num_list - num_model)
	{
		int i = num_model;
		while (g_Model[i] == g_CharList[s + i])
		{
			if (i == 1)
			{
				result_place_boyer_moore.push_back(s + 1);
				break;
			}
			else
			{
				i--;
			}
		}
		s = s + max(g_BMGS[i], g_BMBC[g_Int(g_CharList[s+i])] + i - num_model);
	}
}




bool g_JudgeSuccess()
{
	if (result_place_naive.size() != result_place_rabin_karp.size())
	{
		return 0;
	}
	if (result_place_naive.size() != result_place_dfa.size())
	{
		return 0;
	}
	if (result_place_naive.size() != result_place_kmp.size())
	{
		return 0;
	}
	if (result_place_naive.size() != result_place_boyer_moore.size())
	{
		return 0;
	}
	for (int i = 0; i < result_place_naive.size(); i++)
	{
		if (result_place_naive[i] != result_place_rabin_karp[i])
		{
			return 0;
		}
		if (result_place_naive[i] != result_place_dfa[i])
		{
			return 0;
		}
		if (result_place_naive[i] != result_place_kmp[i])
		{
			return 0;
		}
		if (result_place_naive[i] != result_place_boyer_moore[i])
		{
			return 0;
		}
	}
	return 1;
}
