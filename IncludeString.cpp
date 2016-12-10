#include "stdafx.h"
#include "IncludeString.h"
#include <string>
#include <iostream>
#include "BigInt.h"
using namespace std;  
IncludeString::IncludeString(void)
{
}	  
IncludeString::~IncludeString(void)
{
}

#pragma region 轮询方法
/*
1.1、O（n*m）的轮询方法 
判断 string2 中的字符是否在 string1 中?： 
String 1: ABCDEFGHLMNOPQRS 
String 2: DCGSRQPOM 
判断一个字符串是否在另一个字符串中，最直观也是最简单的思路是，针对第二个字符
串 string2 中每一个字符， 一一与第一个字符串 string1 中每个字符依次轮询比较， 看它是否
在第一个字符串 string1 中。 
假设 n 是字符串 string1 的长度， m 是字符串 string2 的长度， 那么此算法， 需要 O （n*m）
次操作，拿上面的例子来说，最坏的情况下将会有 16*8 = 128 次操作。 
*/
//轮询方法
void ComparePoll(string LongString ,string ShortString)
{
	for (int i = 0; i < ShortString.length(); i++)
	{
		int j=0;
		//O(n*m)
		for (j = 0; j < LongString.length(); j++)
		{
			if(LongString[j]==ShortString[i]) break;
		}
		if(j==LongString.length()){
			cout<<"false"<<endl;
			return;
		}
	}
	cout<<"true"<<endl;
	return;
}
#pragma endregion	

#pragma region O(mlogm)+O(nlogn)+O(m+n)的排序方法
/*
1.2、O(mlogm)+O(nlogn)+O(m+n)的排序方法 
一个稍微好一点的方案是先对这两个字符串的字母进行排序，然后同时对两个字串依次
轮询。两个字串的排序需要(常规情况)O(m log m) + O(n log n)次操作，之后的线性扫描需
要 O(m+n)次操作。 
同样拿上面的字串做例子，将会需要 16*4 + 8*3 = 88 加上对两个字串线性扫描的 16 + 8 
= 24 的操作。(随着字串长度的增长，你会发现这个算法的效果会越来越好)
排序使用何种办法，一般采用快速排序方法。
*/
//取中值
int Partition(string &str,int lo,int hi)
{
	while (lo<hi)
	{
		if(str[hi]<str[lo])
		{
			swap(str[hi],str[lo]);
			lo++;
		}
		else
		{
			hi--;
		}
	}
	return lo;
}

//递归调用上述Partition过程，完成排序
void QuickSort(string &str,int lo,int hi)
{
	if(lo<hi)
	{
		//取中值位置
		int k=Partition(str,lo,hi);
		//左边排序
		QuickSort(str,lo,k-1);
		//右边排序
		QuickSort(str,k+1,hi);
	}
}

//比较有序序列
void CompareStr(string str1,string str2)
{
	int posOne=0;
	int posTwo=0;
	while (posTwo<str2.length() && posOne<str1.length())
	{
		//比较两个有序序列大小
		while (str1[posOne]<str2[posTwo] && posOne<str1.length()-1)
		{
			posOne++;
		}
		//如果存在不相等则证明str2[posTwo]>=str1[posOne] str2序列后移
		if(str1[posOne]==str2[posTwo]) posTwo++;
		else break;
	}
	if(posTwo==str2.length()) cout<<"true"<<endl;
	else cout<<"false"<<endl;
}
#pragma endregion

#pragma region O（n+m）的计数排序方法，空间复杂度为 O（n+m）
/*
1.3 使用计数排序O（n+m）
*/
//计数排序
void CountSort(string str,string &help_str)
{
	//辅助计数数组
	int help[26]={0};
	//help[index]存放了等于index+'A'的元素个数
	for (int i = 0; i < str.length(); i++)
	{
		int index=str[i]-'A';
		help[index]++;
	}
	//求出每个元素对应的最终位置
	for (int j = 1; j < 26; j++)
	{
		help[j]+=help[j-1];
	}
	//把每个元素放到其对应的最终位置
	for (int k=str.length()-1; k>=0;k--)
	{
		int index=str[k]-'A';
		int pos=help[index]-1;
		help_str[pos]=str[k];
		help[index]--;
	}
}
#pragma endregion

#pragma region O（n+m）的 hashtable 的方法 
/*
我们可以对短字串进行轮询（此思路的叙述可能与网上的一些叙述有出入，因为我们最
好是应该把短的先存储，那样，会降低题目的时间复杂度），把其中的每个字母都放入一个
Hashtable 里(我们始终设 m 为短字符串的长度，那么此项操作成本是 O(m)或 8 次操作)。
然后轮询长字符串，在 Hashtable 里查询短字符串的每个字符，看能否找到。如果找不到，
说明没有匹配成功，轮询长字符串将消耗掉 16 次操作，这样两项操作加起来一共只有
8+16=24 次。

 1、hash[26]，先全部清零，然后扫描短的字符串，若有相应的置 1， 
 2、计算 hash[26]中 1 的个数，记为 m  
 3、扫描长字符串的每个字符 a；若原来 hash[a] == 1 ，则修改 hash[a] = 0，并将 m 减 1；
若 hash[a] == 0，则不做处理  
 4、若 m == 0 or 扫描结束，退出循环。 
*/
//使用hashTable排序
void HashTableCompare(string longStr,string shortStr)
{
	string str1=longStr;
	string str2=shortStr;
	if(longStr.length()<shortStr.length())
	{
		str1=shortStr;
		str2=longStr;
	}
	//开辟一个辅助数组并清零
	int hash[26]={0};
	//num为辅助数组中元素个数
	int num=0;
	//扫描短字符串
	for (int i = 0; i < str2.length(); i++)
	{
		//将字符转换成对应辅助数组中的索引
		int index=str2[i]-'A';
		//如果辅助数字中该索引对应元素为0，则置1，且num++
		if(hash[index]==0)
		{
			hash[index]=1;
			num++;
		}
	}
	//扫描长字符串
	for (int j = 0; j < str1.length(); j++)
	{
		int index=str1[j]-'A';
		//如果辅助数组中该索引对应元素为1，则num--；为零不做处理
		if(hash[index]==1)
		{
			hash[index]=0;
			num--;
			if(num==0) break;
		}
	}
	if(num==0)
	{
		cout<<"true"<<endl;
	}
	else
	{
		cout<<"false"<<endl;
	}
}
#pragma endregion

#pragma region O（n）到 O（n+m）的素数方法 
/*
你可能会这么想：O(n+m)是你能得到的最好的结果了，至少要对每个字母至少访问一次
才能完成这项操作，而上一节最后的俩个方案是刚好是对每个字母只访问一次。
ok，下面给出一个更好的方案： 
    假设我们有一个一定个数的字母组成字串，我给每个字母分配一个素数，从 2 开始，往
后类推。这样 A 将会是 2，B 将会是 3，C 将会是 5，等等。现在我遍历第一个字串，把每
个字母代表的素数相乘。你最终会得到一个很大的整数，对吧？ 
    然后——轮询第二个字符串，用每个字母除它。如果除的结果有余数，这说明有不匹配
的字母。如果整个过程中没有余数，你应该知道它是第一个字串恰好的子集了。 
思路总结如下： 
1.定义最小的 26 个素数分别与字符'A'到'Z'对应。 
2.遍历长字符串，求得每个字符对应素数的乘积。 
3.遍历短字符串，判断乘积能否被短字符串中的字符对应的素数整除。 
4.输出结果。
	上述算法的时间复杂度为 O(m+n)，时间复杂度最好的情况为 O(n)（遍
历短的字符串的第一个数，与长字符串素数的乘积相除，即出现余数，便可退出程序，返回
false），n 为长字串的长度，空间复杂度为 O(1)。如你所见，我们已经优化到了最好的程
度。
*/
void PrimeNumberMoth(string strOne,string strTwo)
{
	//素数数组
	Bignum primeNumber[26]={2,3,5,7,11,13,19,23,29,31,37,41,43,47,53,59,61,67,71,73,83,89,97,101};
	//需要使用大整数
	Bignum product=1;
	//遍历长字符串，得到每个字符对应素数的乘积
	for (int i = 0; i < strOne.length(); i++)
	{
		int index=strOne[i]-'A';
		product=product * primeNumber[index];		
		product.display();
	}
	//遍历短字符串
	int j=0;
	for (j = 0; j < strTwo.length(); j++)
	{
		int index=strTwo[j]-'A';
		//如果余数不为0，说明不包含短字符串中的字符，跳出循环
		if(product%primeNumber[index]!=Bignum(0)) break;
	}
	if(strTwo.length()==j) cout<<"true"<<endl;
	else cout<<"false"<<endl;
}
#pragma endregion

#pragma region Bit-Map 方法
/*
所谓的 Bit-map 就是用一个 bit 位来标记某个元素对应的 Value， 而 Key 即是该
元素。由于采用了 Bit 为单位来存储数据，因此在存储空间方面，可以大大节省。 
    如果看了以上说的还没明白什么是 Bit-map， 那么我们来看一个具体的例子， 假设我们要
对 0-7 内的 5 个元素(4,7,2,5,3)排序（这里假设这些元素没有重复）。那么我们就可以采用
Bit-map 的方法来达到排序的目的。要表示 8 个数，我们就只需要 8 个 Bit（1Bytes），首
先我们开辟 1Byte 的空间，将这些空间的所有 Bit 位都置为 0，接着再处理第二个元素 7，将第八位置为 1,，接着再处理第三个元素，一直到最后处理
完所有的元素，将相应的位置为 1 最后我们现在遍历一遍 Bit 区域，将该位是一的位的编号输出（2，3，4，5，7），这样
就达到了排序的目的。
*/
#define BYTYSIZE 8
void SetBit(char *p,int posi)
{
	for (int i = 0; i < (posi/BYTYSIZE); i++)
	{
		p++;
	}
	//将该Bit为赋值1
	*p=*p|(0x01<<(posi%BYTYSIZE));
}

//位图处理
void BitMapSortDemo()
{
	//不考虑负数
	int num[]={3,5,2,10,6,12,8,14,9};
	//BufferLen这个值是根据带排序的数据中最大的值确定的
	//待排序中的最大值是14，因此只需要2个Bytes（16个Bit）
	const int BufferLen=2;
	char *pBuffer=new char[BufferLen];
	//要将所有的Bit位置置为0
	memset(pBuffer,0,BufferLen);
	for (int i = 0; i < 9; i++)
	{
		//首先将相应的Bit位置1
		SetBit(pBuffer,num[i]);
	}
	//输出排序结果
	for (int i = 0; i < BufferLen; i++)
	{
		//处理该字节中的每个Bit位
		for (int j = 0; j < BYTYSIZE; j++)
		{
			//判断该位上是否是1，进行输出，这里的判断比较笨，首先得到改第j位的掩码（0x01<<j）,将内存区中的位和此掩码作与操作。最后判断掩码是否和处理后的结果一样
			if((*pBuffer&(0x01<<j))==(0x01<<j)) cout<<i*BYTYSIZE+j;

		}
		pBuffer++;
	}
}

#pragma endregion

//字符串包含处理
void IncludeString::IncludeStringDeal()
{
	//轮询方法
	string LongString="ABCDEFGHLMNOPQR";
	string ShortString="DCGSQPOMT";
	//ComparePoll(LongString,ShortString);

	//快排+比较
	/*QuickSort(LongString,0,LongString.length()-1);
	QuickSort(ShortString,0,ShortString.length()-1);
	CompareStr(LongString,ShortString);*/

	//计数排序+比较
	//string strOne="ABCDAK";
	//string strTwo="A";
	//string long_str=strOne;
	//string short_str=strTwo;
	////对字符进行计数排序
	//CountSort(strOne,long_str);
	//CountSort(strTwo,short_str);
	//CompareStr(long_str,short_str);

	//使用hashTable方法
	//HashTableCompare(LongString,ShortString);

	//使用大整数素数法
	//PrimeNumberMoth(LongString,ShortString);
	BitMapSortDemo();
}
