#pragma once
/*题目描述*/
/*
定义字符串的左旋转操作：把字符串前面的若干个字符移动到字符串的尾部。
如把字符串 abcdef 左旋转 2 位得到字符串 cdefab。
请实现字符串左旋转的函数，要求对长度为 n 的字符串操作的时间复杂度为
O(n)，空间复杂度为 O(1)。

解决方法：
1、三次翻转，直接线性
2、两个指针逐步翻转，线性
3、stl的rotate算法，线性
*/

class LeftRotateString
{
public:
	LeftRotateString();
	~LeftRotateString();
	void LeftRotateStringDeal();
};
