/*
description: string match functions, include naive, rabin-karp,kmp,DFA,boy-moore
filename:StringMatch.h
date:4/30/2019
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define SIZE_N 100000000
#define SIZE_M 1000
#define CHARACTER 72
#define MOD 1000000007


extern char g_Char(int num); //0-9还是0-9，小写字母是10-35，大写字母是36-61，()[]{},.-;分别为62-71
extern int g_Int(char c);

extern char g_CharList[SIZE_N + 1];
extern char g_Model[SIZE_M + 1];

extern int g_Delta[SIZE_M + 1][CHARACTER];
extern int g_Pi[SIZE_M + 1];

extern std::vector<int> result_place_naive;
extern std::vector<int> result_place_rabin_karp;
extern std::vector<int> result_place_kmp;
extern std::vector<int> result_place_dfa;
extern std::vector<int> result_place_boyer_moore;

extern void g_GenerateRandomString(int num, char list[]);

extern bool g_JudgeSame(char list[], char model[], int num);

extern void g_GetPi(int num);

extern void g_GetDelta(int num);

extern void g_MatchNaive(int num_list, int num_model);

extern void g_MatchRabinKarp(int num_list, int num_model);

extern void g_MatchDFA(int num_list, int num_model);

extern void g_MatchKMP(int num_list, int num_model);

extern void g_MatchBoyerMoore(int num_list, int num_model);

extern bool g_JudgeSuccess();

