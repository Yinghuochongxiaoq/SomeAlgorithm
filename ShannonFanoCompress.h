#pragma once
/*
Shannon-Fano的树是根据旨在定义一个有效的代码表的规范而建立的。实际的算法很简单：

对于一个给定的符号列表，制定了概率相应的列表或频率计数，使每个符号的相对发生频率是已知。
排序根据频率的符号列表，最常出现的符号在左边，最少出现的符号在右边。
清单分为两部分，使左边部分的总频率和尽可能接近右边部分的总频率和。
该列表的左半边分配二进制数字0，右半边是分配的数字1。这意味着，在第一半符号代都是将所有从0开始，第二半的代码都从1开始。
对左、右半部分递归应用步骤3和4，细分群体，并添加位的代码，直到每个符号已成为一个相应的代码树的叶。

示例


香农-范诺编码算法
这个例子展示了一组字母的香浓编码结构（如图a所示）这五个可被编码的字母有如下出现次数:

Symbol	A	B	C	D	E
Count	15	7	6	6	5
Probabilities	0.38461538	0.17948718	0.15384615	0.15384615	0.12820513
从左到右，所有的符号以它们出现的次数划分。在字母B与C之间划定分割线，得到了左右两组，总次数分别为22,17。 这样就把两组的差别降到最小。通过这样的分割, A与B同时拥有了一个以0为开头的码字, C，D，E的码子则为1,如图b所示。 随后, 在树的左半边，于A，B间建立新的分割线，这样A就成为了码字为00的叶子节点，B的码子01。经过四次分割, 得到了一个树形编码。 如下表所示，在最终得到的树中, 拥有最大频率的符号被两位编码, 其他两个频率较低的符号被三位编码。
*/
//8位的字符代码
#include <map>

class ShannonFanoCompress
{
	void Optimize_Tree(int a, int b, ShannonFanoCompress& root);
	ShannonFanoCompress* BuildTree(int* freqency);
public:
	ShannonFanoCompress* left;
	ShannonFanoCompress* right;
	char ch;
	int weight;
	bool IsLeaf();
	//香浓编码
	void DealShannonFano();
	ShannonFanoCompress();
	ShannonFanoCompress(ShannonFanoCompress* l, ShannonFanoCompress* r, int w, char c);
	~ShannonFanoCompress();

};

