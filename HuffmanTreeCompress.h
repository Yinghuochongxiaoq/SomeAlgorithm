#pragma once
class HuffmanTreeCompress
{
public:
	void DealHuffmanTree();
};

#define MAX 100

//���ṹ��
typedef struct
{
	//Ȩ��
	int weight;
	//�ַ�ֵ
	char value;
	//���ڵ�
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;

//������
typedef struct
{
	char * HfmCode;
	char value;
}code, *HuffmanCode;

