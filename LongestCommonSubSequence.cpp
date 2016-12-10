#include "stdafx.h"
#include "LongestCommonSubSequence.h"
#include <string>
#include <math.h>
#include <ctime>
#include <iostream>
using namespace std;

string GetRandomString(int length);
//����������з���
void LongestCommonSubSequence::DealLongestCommonSubString()
{
	clock_t start = clock(), finish;
	//�����ַ����ĳ��� ���������ƣ�ԭ���������ɶ�ά����ʱ��Ҫһ�������Ŀռ䣬���ܳ������
	const int subStringLengthOne = 500;
	const int subStringLengthTwo = 500;

	//��������ַ���
	string x=GetRandomString(subStringLengthOne);
	string y = GetRandomString(subStringLengthTwo);

	//�����ά�����¼������x[i]��y[i]��LCS�ĳ���
	int opt[subStringLengthOne + 1][subStringLengthTwo + 2] = { 0 };

	//��̬�滮��������������
	for (int i = subStringLengthOne-1; i >=0; i--)
	{
		for (int j = subStringLengthTwo - 1; j >= 0; j--)
		{
			if (x[i] == y[j])
			{
				opt[i][j] = opt[i + 1][j + 1] + 1;
			}
			else
			{
				opt[i][j] = fmax(opt[i+1][j], opt[i][j+1]);
			}
		}
	}
	cout << "��һ������:" << x << "\n" << "�ڶ�������:" << y << "\n���������£�";

	int i = 0, j = 0;
	while (i<subStringLengthOne && j<subStringLengthTwo)
	{
		if (x[i] == y[j])
		{
			cout << x[i];
			i++;
			j++;
		}
		else if (opt[i + 1][j] >= opt[i][j + 1])
		{
			i++;
		}
		else
		{
			j++;
		}
	}
	finish = clock();
	cout << "\n�����ʱ�� " << (finish - start) << "/" << CLOCKS_PER_SEC << "(s)" << endl;
}

//��������ַ���
string GetRandomString(int length)
{
	string  outRandomString;
	char * buffer = { "abcdefghijklmnopqrstuvwxyz" };
	srand(rand());
	for (int i = 0; i < length; i++)
	{
		int index = rand() % 26;
		outRandomString += buffer[index];
	}
	return outRandomString;
}
