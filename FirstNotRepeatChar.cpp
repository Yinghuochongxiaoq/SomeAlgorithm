#include "stdafx.h"
#include "FirstNotRepeatChar.h"
#include <iostream>
#include <string>
using namespace std;

char FindFirstUniqueChar(char *str);

//�����׸�����һ�ε��ַ���
void FirstNotRepeatChar::DealFirstNotRepeatChar()
{
	char *str = "afacshetgsagwgvw5gtwrvfvsrgwfvsgwgwhtejnggwhejmnrybgbrehecde";
	cout << FindFirstUniqueChar(str) << endl;
}

//�����״γ���һ�ε��ַ�
char FindFirstUniqueChar(char *str)
{
	int data[256];
	char *p;
	if (str == NULL) return '\0';
	//�����ʼ��Ϊ0
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
