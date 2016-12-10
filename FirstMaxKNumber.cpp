#include "stdafx.h"
#include "FirstMaxKNumber.h"
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

/*
0、   咱们先简单的理解，要求一个序列中最小的 k 个数，按照惯有的思维方式，很
简单，先对这个序列从小到大排序，然后输出前面的最小的 k 个数即可。 

1、   至于选取什么的排序方法，我想你可能会第一时间想到快速排序，我们知道，
快速排序平均所费时间为 n*logn，然后再遍历序列中前 k 个元素输出，即可，总的
时间复杂度为 O（n*logn+k）=O（n*logn） 。

2、   咱们再进一步想想，题目并没有要求要查找的 k 个数，甚至后 n-k 个数是有序
的，既然如此，咱们又何必对所有的 n 个数都进行排序列? 
       这时，咱们想到了用选择或交换排序，即遍历 n 个数，先把最先遍历到得 k 个
数存入大小为 k 的数组之中，对这 k 个数，利用选择或交换排序，找到 k 个数中的
最大数 kmax（kmax 设为 k 个元素的数组中最大元素） ，用时 O（k） （你应该知道，
插入或选择排序查找操作需要 O （k） 的时间） ， 后再继续遍历后 n-k 个数， x 与 kmax
比较：如果 x<kmax，则 x 代替 kmax，并再次重新找出 k 个元素的数组中最大元素
kmax‘（多谢 kk791159796 提醒修正） ；如果 x>kmax，则不更新数组。这样，每次 
更新或不更新数组的所用的时间为 O（k）或 O（0） ，整趟下来，总的时间复杂度平
均下来为：n*O（k）=O（n*k） 。

3、   当然，更好的办法是维护 k 个元素的最大堆，原理与上述第 2 个方案一致，
即用容量为 k 的最大堆存储最先遍历到的 k 个数，并假设它们即是最小的 k 个数，
建堆费时 O（k）后，有 k1<k2<...<kmax（kmax 设为大顶堆中最大元素） 。继续遍
历数列，每次遍历一个元素 x，与堆顶元素比较，x<kmax，更新堆（用时 logk） ，
否则不更新堆。这样下来，总费时 O（k+（n-k）*logk）=O（n*logk） 。此方法得益
于在堆中，查找等各项操作时间复杂度均为 logk（不然，就如上述思路 2 所述：直
接用数组也可以找出前 k 个小的元素，用时 O（n*k） ） 。 

4、 按编程之美第 141 页上解法二的所述，类似快速排序的划分方法，N 个数存储
在数组 S 中，再从数组中随机选取一个数 X（随机选取枢纽元，可做到线性期望时
间 O （N） 的复杂度， 在第二节论述） ， 把数组划分为 Sa 和 Sb 俩部分， Sa<=X<=Sb，
如果要查找的 k 个元素小于 Sa 的元素个数，则返回 Sa 中较小的 k 个元素，否则返
回 Sa 中 k 个小的元素+Sb 中小的 k-|Sa|个元素。 像上述过程一样， 这个运用类似快
速排序的 partition 的快速选择 SELECT 算法寻找最小的 k 个元素， 在最坏情况下亦
能做到 O（N）的复杂度。不过值得一提的是，这个快速选择 SELECT 算法是选取
数组中“中位数的中位数”作为枢纽元，而非随机选取枢纽元。
*/

#pragma region 小根堆处理
/*
处理小根堆
先对元素数组原地建最小堆，O(n)。然后提取 K 次，但是每次提取时，   
换到顶部的元素只需要下移顶多 k 次就足够了，下移次数逐次减少。此种方法的复杂度为 O
（n+k^2） 
*/
#define MAXLEN 12
#define K 2
//初始建堆
void HeapAdjust(int arraytemp[],int i ,int length)
{
	int child;
	for (int tmep=arraytemp[i] ;2*i+1<length; i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child+1]<arraytemp[child])
		{
			child++;
		}
		if(tmep>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=tmep;
	}
}

void Swap(int* a,int* b)
{
	*a=*a^*b;
	*b=*a^*b;
	*a=*a^*b;
}

int GetMin(int arraytemp[],int length,int k)
{
	int min=arraytemp[0];
	Swap(&arraytemp[0],&arraytemp[length-1]);

	int child,temp;
	int i=0,j=k-1;
	for (temp= arraytemp[0]; j>0 && 2*i+1<length; --j,i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child=1]<arraytemp[child])
		{
			child++;
		}
		if(temp>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=temp;
		return min;
	}
}

void Kmin(int arraytemp[],int length,int k)
{
	for (int i=length/2-1;i>=0;--i)
	{
		//初始建堆，时间复杂度为O（n）
		//HeapAdjust(arraytemp,i,length);
		int child;
	for (int tmep=arraytemp[i] ;2*i+1<length; i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child+1]<arraytemp[child])
		{
			child++;
		}
		if(tmep>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=tmep;
	}

	}
	int j=length;
	for (;k>0;--k,--j)
	{
		//k次循环，每次循环的复杂度最多为k次交换，复杂度为O（k^2）
		int min=GetMin(arraytemp,j,k);
		cout<<min<<endl;
	}
}
#pragma endregion


//处理最小k个数的方法
void FirstMaxKNumber::FirstMaxKNumberDeal(void)
{
	//小根堆处理
	int array[MAXLEN];
	for (int i=MAXLEN;i>0;--i)
	{
		array[MAXLEN-i]=rand()%MAXLEN;
	}
	Kmin(array,MAXLEN,K);
}
