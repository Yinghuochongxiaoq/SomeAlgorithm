#include "stdafx.h"
#include "HuffmanTreeCompress.h"
#include <string>
#include <iostream>
using namespace std;

//��������
void Select(HuffmanTree &ht, int n, int *s1, int *s2);
void Creat_HuffmanTree(HuffmanTree &ht, int *w, char *st, int n);
void outputHuffman(HuffmanTree &ht, int m);
void Creat_HuffmanCode(HuffmanTree &ht, HuffmanCode &hc, int n);
void Decoding_HuffmanTree(HuffmanTree &ht, char code[], char result[]);

//����Huffman����
void HuffmanTreeCompress::DealHuffmanTree()
{
	HuffmanTree HT;
	HuffmanCode HC;
	//��̬���飬��Ÿ��ַ���Ȩ��
	int *w;
	//�ַ�������Žڵ��ֵ
	char *st;
	//nΪҶ�ӽڵ����
	int i, n;
	int m;

	cout << "�����ַ���:" << endl;
	cin >> n;
	//0�ŵ�Ԫ����
	w = (int *)malloc((n + 1)*sizeof(int));
	//0�ŵ�Ԫ����
	st = (char *)malloc((n + 1)*sizeof(char));

	FILE *fin = fopen("test.txt", "r");
	for (i = 1; i <= n; i++)
	{
		fscanf(fin, "%c%d", &st[i], &w[i]);
	}
	/*����H��*/
	Creat_HuffmanTree(HT, w, st, n);

	m = 2 * n - 1;
	/*��ʾH��*/
	outputHuffman(HT, m);
	cout << endl;
	/*����H��,��ÿ���ַ��ı���,����HC��*/
	Creat_HuffmanCode(HT, HC, n);
	/*�������*/
	for (i = 1; i <= n; i++)
	{
		cout << HC[i].value << "  " << HC[i].HfmCode << endl;
	}

	//����
	//char *code = "01101110101010001110110110011100";
	char *code = "000001111001";
	char *result;
	result = (char *)malloc(100 * sizeof(char));
	//result[]��Ž�����
	Decoding_HuffmanTree(HT, code, result);
	for (i = 0; result[i]; i++)
		cout << result[i] << "  ";
}

//ѡ����СȨ�ص�������
void Select(HuffmanTree &ht, int n, int *s1, int *s2)
{
	/*ht,Ϊ�����������ͷָ��,nΪ������ҵ�������,s1,s2,������С���������*/
	int p1 = MAX;
	int p2 = MAX;
	int pn1 = 0;
	int pn2 = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (ht[i].weight<p1 && ht[i].parent == 0)//ht[i].parent=0��������ȥ���Ѿ�ѡ���Ľڵ�
		{
			pn2 = pn1;
			p2 = p1;
			pn1 = i;
			p1 = ht[i].weight;
		}
		else if (ht[i].weight<p2 && ht[i].parent == 0)
		{
			pn2 = i;
			p2 = ht[i].weight;
		}
	}
	*s1 = pn1;    //��ֵ����
	*s2 = pn2;
}

//������������
void Creat_HuffmanTree(HuffmanTree &ht, int *w, char *st, int n)
{
	//��Ҫ�Ľ������
	int m = 2 * n - 1;
	//����ռ� 0�ŵ�Ԫ����
	ht = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));
	HuffmanTree p;
	int i;
	//��Ϊw[]��0�ŵ�Ԫû����
	w = w + 1;
	st = st + 1;
	//1-n�ŷ�Ҷ�ӽ�㣬��ʼ��
	for (p = ht + 1, i = 1; i <= n; i++, p++, w++, st++)
	{
		(*p).weight = *w;
		(*p).value = *st;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)        //��Ҷ�ӽ���ʼ��
	{
		(*p).weight = 0;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	//��select������ʹ��,�����洢��СȨ�Ľ������
	int s1, s2;
	for (i = n + 1; i <= m; ++i)//������Ҷ�ӽ��,����������
	{
		//��ht[1]~ht[i-1]�ķ�Χ��ѡ������parentΪ0��weight��С�Ľ�㣬����ŷֱ�ֵ��s1��s2����
		Select(ht, i - 1, &s1, &s2);
		ht[s1].parent = i;
		ht[s2].parent = i;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[i].weight = ht[s1].weight + ht[s2].weight;
	}
}//���������������

//������нڵ�Ȩ��
void outputHuffman(HuffmanTree &ht, int m)
{
	for (int i = 1; i <= m; i++)
		cout << ht[i].weight << " ";
}

//��Ҷ�ӽ�㵽����������ÿ��Ҷ�ӽ���Ӧ�Ĺ���������
void Creat_HuffmanCode(HuffmanTree &ht, HuffmanCode &hc, int n)
{
	char *cd;
	int start;
	//cָ��ǰ�ڵ�
	int c;
	//pָ��ǰ�ڵ��˫�׽��
	int p;
	int i;
	//����n�������ͷָ��
	hc = (HuffmanCode)malloc((n + 1)*sizeof(code));
	//������ǰ����Ĺ����ռ�
	cd = (char *)malloc(n * sizeof(char));
	//����������λ��ű��룬���ȴ�ű��������
	cd[n - 1] = '\0';
	//��n��Ҷ�ӽ���Ӧ�Ĺ���������
	for (i = 1; i <= n; i++)
	{
		hc[i].value = ht[i].value;
		//��ʼ��������ʼָ��
		start = n - 1;
		//��Ҷ�ӵ�����������
		for (c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent)
		{
			if (ht[p].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		//Ϊ��i���������ռ�
		hc[i].HfmCode = (char *)malloc(n*sizeof(char));
		strcpy(hc[i].HfmCode, &cd[start]);
	}
	free(cd);
}

//����
void Decoding_HuffmanTree(HuffmanTree &ht, char code[], char result[])
{
	int i, k = 0;
	int p = 0, root;
	//root�ǻ��������ĸ� 
	for (root = 1; ht[root].parent != 0; root = ht[root].parent);
	for (i = 0, p = root; code[i] != '\0'; i++)
	{
		if (code[i] == '0')
			p = ht[p].lchild;
		else
			p = ht[p].rchild;
		if (ht[p].lchild == NULL && ht[p].rchild == NULL)
		{
			result[k++] = ht[p].value;
			p = root;
		}
	}
	result[k] = '\0';
}
