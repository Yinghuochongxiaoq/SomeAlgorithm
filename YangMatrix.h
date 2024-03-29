#pragma once
/*
杨氏矩阵：
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递
增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含
有该整数。
例如下面的二维数组就是每行、每列都递增排序。如果在这个数组中查找数字 6，则返
回 true；如果查找数字 5，由于数组不含有该数字，则返回 false。
1	2	8	9
2	4	9	12
4	7	10	13
6	8	11	15

1、分治法，分为四个矩形，配以二分查找，如果要找的数是 6 介于对角线上相邻的两个数 4、 10， 可以排除掉左上和右下的两个矩形， 而递归在左下和右上的两个矩形继续找

2、首先直接定位到最右上角的元素，再配以二分查找，比要找的数（6）大就往左走，比要找数（6）的小就往下走，直到找到要找的数字（6）为止
*/
class YangMatrix
{
public:
	bool DealYangMatrix(int search);
	void GetInputSearchValue();
};

