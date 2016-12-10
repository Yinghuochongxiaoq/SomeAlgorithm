// SomeAlgorithm.Console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LeftRotateString.h"
#include "IncludeString.h"
#include "FirstMaxKNumber.h"
#include "FindSumNumber.h"
#include "AmicableNumbers.h"
#include "MaxSumChildArrar.h"
#include "VirtualClassNote.h"
#include "FileDataSort.h"
#include "LongestCommonSubSequence.h"
#include "LZWCompress.h"
#include "HuffmanTreeCompress.h"
#include "ShannonFanoCompress.h"
#include "FirstNotRepeatChar.h"
#include "YangMatrix.h"
#include "StringHash.h"
#include "BinarySearch.h"
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
#pragma region 1、左旋转字符
	//(LeftRotateString()).LeftRotateStringDeal();
#pragma endregion

#pragma region 2、字符串是否包含问题
	//(IncludeString()).IncludeStringDeal();
#pragma endregion

#pragma region 3、求最小k个数
	//(FirstMaxKNumber()).FirstMaxKNumberDeal();
#pragma endregion

#pragma region 4、求满足条件的两个或多个数
	//(FindSumNumber()).DealFindSum();
#pragma endregion

#pragma region 5、求500W以内的亲和数
	//(AmicableNumbers()).AmicableNumbersDeal();
#pragma endregion

#pragma region 6、求最大字数组之和
	//(MaxSumChildArrar()).GetMaxSumChildArrar();
#pragma endregion

#pragma region 7、虚函数解析
	//(VirtualClassNote()).VirtualMathRead();
#pragma endregion

#pragma region 8、对1000W的数据排序，去掉重复值
	//(FileDataSort()).DealFileDataSort();
#pragma endregion

#pragma region 9、求最大子序列问题
	//(LongestCommonSubSequence()).DealLongestCommonSubString();
#pragma endregion

#pragma region 10、LZW压缩解压算法
	//(LZWCompress()).DealLZWCompress();
#pragma endregion

#pragma region 11、Huffman压缩解压算法
	//(HuffmanTreeCompress()).DealHuffmanTree();
#pragma endregion

#pragma region 12、ShannonFano压缩解压算法
	//(ShannonFanoCompress()).DealShannonFano();
#pragma endregion

#pragma region 13、查找首次出现一次的字符
	//(FirstNotRepeatChar()).DealFirstNotRepeatChar();
#pragma endregion

#pragma region 14、杨氏三角查找指定数
	//(YangMatrix()).GetInputSearchValue();
#pragma endregion

#pragma region 15、暴雪hash函数
	//StringHash sss = StringHash();
	//获得hash值
	//(sss.HashString("jdianina", 0));
	//查找是需要重新初始化方法
	//(sss.Hashed("jdianina"));
#pragma endregion

#pragma region 16、传说中的二分查找10分钟内正确写出
	(BinarySearch().DealBinarySearch());
#pragma endregion
	string s;
	cin >> s;
	return 0;
}

