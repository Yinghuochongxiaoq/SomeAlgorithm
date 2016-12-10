#pragma once
class HuffmanTreeCompress
{
public:
	void DealHuffmanTree();
};

#define MAX 100

//树结构体
typedef struct
{
	//权重
	int weight;
	//字符值
	char value;
	//父节点
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;

//编码结点
typedef struct
{
	char * HfmCode;
	char value;
}code, *HuffmanCode;

