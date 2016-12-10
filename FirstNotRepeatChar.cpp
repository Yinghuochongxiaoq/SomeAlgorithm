#include "stdafx.h"
#include "FirstNotRepeatChar.h"
#include <iostream>
#include <string>
using namespace std;

char FindFirstUniqueChar(char *str);

//处理首个出现一次的字符串
void FirstNotRepeatChar::DealFirstNotRepeatChar()
{
	char *str = "afacshetgsagwgvw5gtwrvfvsrgwfvsgwgwhtejnggwhejmnrybgbrehecde";
	cout << FindFirstUniqueChar(str) << endl;
}

//查找首次出现一次的字符
char FindFirstUniqueChar(char *str)
{
	int data[256];
	char *p;
	if (str == NULL) return '\0';
	//数组初始化为0
	memset(data, 0, sizeof(data));
	p = str;
	while (*p != '\0')
	{
		data[(unsigned char)*p++]++;
	}
	while (*str != '\0')
	{
		if (data[(unsigned char)*str] == 1) return *str;
		str++;
	}
	return '\0';
}
