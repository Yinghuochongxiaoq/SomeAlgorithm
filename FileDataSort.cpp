#include "stdafx.h"
#include "FileDataSort.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include <bitset>
#include <io.h>
using namespace std;

const int max_each_scan = 100000;
const int size = 2 * max_each_scan;

//���ɲ��������ļ�
void ProductTestDataFile()
{
	int num[size] = {0};
	int n;
	//�ж��ļ��Ƿ���ڣ��������Զ�����
	//if (_access("data.txt", 0) == 0) return;
	FILE *fp = fopen("data.txt", "w");
	assert(fp);
	for (n = 1; n < size; n++)
	{
		num[n] = n;
	}
	srand((unsigned)time(NULL));
	int i, j;
	for (n = 0; n < size; n++)
	{
		i = (rand()*RAND_MAX + rand()) % size;
		j = (rand()*RAND_MAX + rand()) % size;
		swap(num[i], num[j]);
	}
	for (n = 0; n < size-1; n++)
	{
		fprintf(fp, "%d\n", num[n]);
	}
	fclose(fp);
}

//λͼ������� 10^7 �����������ļ�����������
//������ظ������ݣ���ôֻ����ʾ����һ�� �����Ľ������� 
void FileDataSort::DealFileDataSort()
{
	//�����ļ�
	ProductTestDataFile();
	//��ʱ��ʼ
	clock_t begin = clock();
	//����λͼ����
	bitset<max_each_scan> bit_map;
	//����λͼ
	bit_map.reset();
	//���ļ��ж�ȡ����
	FILE *fp_unsort_file = fopen("data.txt","r");
	//�ļ��п�
	assert(fp_unsort_file);
	int num;

	//�ļ�ɨ��
	while (fscanf(fp_unsort_file,"%d\n",&num)!=EOF)
	{
		if (num < max_each_scan)
		{
			bit_map.set(num, 1);
		}
	}

	FILE *fp_sort_file = fopen("sort.txt","w");
	assert(fp_sort_file);
	int i;

	//�ļ���д
	for (i = 0; i < max_each_scan; i++)
	{
		if (bit_map[i] == 1) fprintf(fp_sort_file,"%d\n",i);
	}
	//���ϴ�����500W������ʣ��500W
	int result = fseek(fp_unsort_file,0,SEEK_SET);
	if (result)
	{
		cout << "fseek ʧ��" << endl;
	}
	else
	{
		bit_map.reset();
		int maxNumber = 2 * max_each_scan;
		while (fscanf(fp_unsort_file, "%d\n", &num) != EOF)
		{
			if (num >= max_each_scan && num<maxNumber)
			{
				num -= max_each_scan;
				bit_map.set(num, 1);
			}
		}
		for (i = 0; i < max_each_scan; i++)
		{
			if (bit_map[i] == 1) fprintf(fp_sort_file, "%d\n", i+max_each_scan);
		}
	}
	clock_t end = clock();
	cout << "λͼ������ʱ��" << (end - begin) / CLK_TCK << "s" << endl;
	//�ر��ļ�
	fclose(fp_unsort_file);
	fclose(fp_sort_file);
}
