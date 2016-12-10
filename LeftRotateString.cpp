#include "stdafx.h"
#include "LeftRotateString.h"
#include <string>
#include <iostream>
using namespace std;

//构造函数
LeftRotateString::LeftRotateString()
{
}

//析构函数
LeftRotateString::~LeftRotateString()
{
}

/*
方案1：
将一个字符串分成两部分，X 和 Y 两个部分，在字符串上定义反转的操作 X^T，即把 X 的
所有字符反转（如，X="abc"，那么 X^T="cba"），那么我们可以得到下面的结论：
(X^TY^T)^T=YX。显然我们这就可以转化为字符串的反转的问题了。
不是么?ok,就拿 abcdef 这个例子来说（非常简短的三句，请细看，一看就懂）：
1、首先分为俩部分，X:abc，Y:def；
2、X->X^T，abc->cba， Y->Y^T，def->fed。
3、(X^TY^T)^T=YX，cbafed->defabc，即整个翻转。
*/

//交换两个数组引用
char * Invert(char *start, char *end){
	char temp, *ptmp = start;
	while (start != NULL && end != NULL && start < end){
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
	return ptmp;
}

// 翻转方法 pos为要旋转的字符个数，或长度，下面测试使用
char *left(char *s, int pos){
	int len = strlen(s);
	//如上，X->X^T，即 abc->cba
	Invert(s, s + (pos - 1));
	//如上，Y->Y^T，即 def->fed
	Invert(s + pos, s + (len - 1));
	//如上，Y->Y^T，即 def->fed  
	Invert(s, s + (len - 1));
	return s;
}

/*
1.2两个指针逐步翻转
左旋转字符串以abcdef为例
1、ab->ba
2、cdef->fedc 原字符串变为bafedc
3、整个翻转：cdefab
只要两次翻转，时间复杂度也为O（n）

另一种思路
abc defghi，要abc移动至最后
abc defghi->def abcghi->def ghiabc

定义两个指针，平p1指向ch[0]，p2指向ch[m]
一下过程循环m次，交换p1和p2所指元素，然后p1++，p2++

第一步，交换 abc 和 def ，
abc defghi->def abcghi
第二步，交换 abc 和 ghi，
def abcghi->def ghiabc
整个过程，看起来，就是 abc 一步一步 向后移动
abc defghi
def abcghi
def ghi abc
//最后的 复杂度是 O（m+n）

由于元素是9个元素的序列，当m=3时，p2恰好指到数组最后一个元素，如果i后面还有一个元素列
即， 如果是要左旋十个元素的序列： abcdefghij， ok， 下面， 就举这个例子， 对 abcdefghij
序列进行左旋转操作：
如果 abcdef ghij 要变成 defghij abc：
abcdef ghij
1. def abc ghij
2. def ghi abc j      //接下来，j 步步前移
3. def ghi ab jc
4. def ghi a j bc
5. def ghi j abc

处理方案：
1、首先让 p1=ch[0]，p2=ch[m]，即让 p1，p2 相隔 m 的距离；
2、判断 p2+m-1 是否越界，如果没有越界转到 3，否则转到 4（abcdefgh 这 8 个字母的字符
串，以 4 左旋，那么初始时 p2 指向 e，p2+4 越界了，但事实上 p2 至 p2+m-1 是 m 个字符，
可以再做一个交换）。
3、不断交换*p1 与*p2，然后 p1++，p2++，循环 m 次，然后转到 2。
4、此时 p2+m-1 已经越界，在此只需处理尾巴。过程如下：
4.1 通过 n-p2 得到 p2 与尾部之间元素个数 r，即我们要前移的元素个数。
4.2 以下过程执行 r 次：
ch[p2]<->ch[p2-1]，ch[p2-1]<->ch[p2-2]，....，ch[p1+1]<->ch[p1]；p1++；
p2++；
当 p1 指向 a，p2 指向 j 时，由于 p2+m 越界，那么此时 p1，p2 不要变
这里 p1 之后（abcjk)就是尾巴，处理尾巴只需将 j,k 移到 abc 之前
*/
//两个指针方法
void Rotate(string &str, int m){
	if (str.length() == 0 || m <= 0) return;

	int n = str.length();

	if (m%n <= 0) return;

	int p1 = 0, p2 = m;
	//计算交换次数
	int k = (n - m) - n%m;
	//交换p1，p2指向的元素，然后移动p1，p2
	while (k--){
		swap(str[p1], str[p2]);
		p1++;
		p2++;
	}

	//处理尾部，r为尾部左移次数
	int r = n - p2;
	while (r--){
		int i = p2;
		while (i > p1){
			swap(str[i], str[i - 1]);
			i--;
		}
		p1++;
		p2++;
	}
	//比如一个例子，abcdefghijk   
	//                    p1    p2   
	//当执行到这里时，defghi a b c j k   
	//p2+m 出界 了，   
	//r=n-p2=2，所以以下过程，要执行循环俩次。   
	//第一次：j 步步前移，abcjk->abjck->ajbck->jabck   
	//然后，p1++，p2++，p1 指 a，p2 指 k。   
	//               p1    p2   
	//第二次：defghi j a b c k   
	//同理，此后，k 步步前移，abck->abkc->akbc->kabc。
}

/*
方法二
def ghi abc jk
当p1指向a，p2指向j时，那么交换p1和p2
此时为
def ghi jbc ak
p1++，p2++，p1指向b，p2指向k，继续上面的步骤得
def gui jkc ab
p1++，p2不懂，p1指向c，p2指向b，p1和p2之间（cab）也就是尾巴
那么处理尾巴（cab）需要循环左移一定次数
*/

void RotateTwo(string &str, int m){
	if (str.length() == 0 || m <= 0) return;
	//初始化p1，p2
	int p1 = 0, p2 = m;
	int n = str.length();

	//处理m大于n
	if (m%n == 0) return;

	//循环直至p2到达字符串末尾
	while (true){
		swap(str[p1], str[p2]);
		p1++;
		if (p2 < n - 1)
			p2++;
		else break;
	}

	//处理尾部，r为尾部循环左移次数
	int r = m - n%m;
	while (r--){
		int i = p1;
		char temp = str[p1];
		while (i < p2){
			str[i] = str[i + 1];
			i++;
		}
		str[p2] = temp;
	}
	//举一个例子   
	//abcdefghijk   
	//当执行到这里的时候，defghiabcjk   
	//      p1    p2   
	//defghi a b c j k，a 与 j 交换，jbcak，然后，p1++，p2++   
	//        p1    p2   
	//       j b c a k，b 与 k 交换，jkcab，然后，p1++，p2 不动，   

	//r = m - n % m= 3-11%3=1，即循环移位 1 次。   
	//          p1  p2   
	//       j k c a b   
	//p1 所指元素 c 实现保存在 temp 里，   
	//然后执行此条语句：str[i] = str[i+1]; 即 a 跑到 c 的位置处，a_b   
	//i++，再次执行：str[i] = str[i+1]，ab_   
	//最后，保存好的 c 填入，为 abc，所以，最终序列为 defghi jk abc。
}

/*
假设m>n,这样在循环m的倍数时就还原到原来的位置。
*/
//左旋转字符串str，m为负数时表示右旋abs（m）个字母
#define positiveMod(m,n) ((m)%(n)+(n))%(n)
void RotateThree(string &str, int m){
	if (str.length() == 0) return;
	int n = str.length();
	//处理大于str长度及m为负数的情况，positiveMod可以取得m为负数时对n取余得到正数
	m = positiveMod(m, n);
	if (m == 0) return;
	int p1 = 0, p2 = m;
	int round;
	//p2当前所指和之后的m-1个字母共m个字母，就可以和p2前面的m个字母交换。
	while (p2 + m - 1 < n){
		round = m;
		while (round--){
			swap(str[p1], str[p2]);
			p1++;
			p2++;
		}
	}
	//剩下的不足m个字母逐个交换
	int r = n - p2;
	while (r--){
		int i = p2;
		while (i > p1){
			swap(str[i], str[i - 1]);
			i--;
		}
		p2++;
		p1++;
	}
}

/*
方法三：通过递归转换，缩小问题之规模
就是说，把一个规模为N的问题化解为规模为M（M<N）的问题；
举例来说，设字符串总长度为L，左侧要旋转的部分长度为s1，那么当从左向右循环交换长度为s1的小段，直到最后，由于剩余的部分长度为s2（s2==L%s1）而不能直接交换。
该问题可以递归转化成规模为s1+s2的，方向相反（从右向左）的同一个问题。随着递归的进行，左右反复回荡，知道某一次满足条件L%s1==0而交换结束。

举例解释一下：
设原始问题为：将“123abcdefg”左旋转为“abcdefg123”，即总长度为 10，旋转部("123")
长度为 3 的左旋转。按照思路二的运算，演变过程为
“123abcdefg”->"abc123defg"->"abcdef123g"。这时，"123"无法和"g"作对调，该问题递归
转化为：将“123g”右旋转为"g123"，即总长度为 4，旋转部("g")长度为 1 的右旋转。

举个具体事例说明，如下：
1、对于字符串 abc def ghi gk，
将 abc 右移到 def ghi gk 后面，此时 n = 11，m = 3，m’ = n % m = 2;
abc def ghi gk -> def ghi abc gk
2、问题变成 gk 左移到 abc 前面，此时 n = m’ + m = 5，m = 2，
m’ = n % m=1;
abc gk -> a gk bc
3、问题变成 a 右移到 gk 后面，此时 n = m’ + m = 3，m = 1，
m’ = n % m = 0;
a gk bc-> gk a bc。 由于此刻，n % m = 0，满足结束条件，返回结果。

即从左至右， 后从右至左， 再从左至右， 如此反反复复， 直到满足条件，
返回退出。
*/

//n 待处理部分的字符串长度，m：待处理部分的旋转长度
//head：待处理部分的头指针，tail：待处理部分的尾指针
//flag = true 进行左旋，flag = false 进行右旋
void RotateRecurse(string &str, int n, int m, int head, int tail, bool flag){
	//返回条件
	if (head == tail || m <= 0) return;
	if (flag){
		//初始化p1，p2
		int p1 = head;
		int p2 = head + m;
		//1、左旋：对于字符串abc def ghi gk
		//将abc右移到def ghi gk后面，此时n=11,m=3,m'=m%m=2;
		//abc def ghi gk->def ghi abc gk
		//p1,p2移动距离，向右移6步
		int k = (n - m) - n%m;
		/*---------------------
		解释下上面的 k = (n - m) - n % m 的由来：
		以 p2 为移动的参照系：
		n-m 是开始时 p2 到末尾的长度，n%m 是尾巴长度
		(n-m)-n%m 就是 p2 移动的距离
		比如 abc def efg hi
		开始时 p2->d,那么 n-m 为 def efg hi 的长度 8，
		n%m 为尾巴 hi 的长度 2，
		因为我知道 abc 要移动到 hi 的前面，所以移动长度是
		(n-m)-n%m = 8-2 = 6。
		*/
		for (int i = 0; i < k; i++, p1++, p2++) swap(str[p1], str[p2]);
		//结束左旋，进行右旋
		RotateRecurse(str, n - k, n%m, p1, tail, false);
	}
	else{
		//右旋：问题变成gk左移到abc前面，此时n=m'+m=5,m=2,m'=n%m=1;
		//abc gk ->a gk bc
		int p1 = tail;
		int p2 = tail - m;
		//p1,p2移动距离，向左移动两步
		int k = (n - m) - n%m;
		for (int i = 0; i < k; i++, p1--, p2--) swap(str[p1], str[p2]);
		//结束左旋，进行右旋
		RotateRecurse(str, n - k, n%m, head, p1, true);
	}
}

//stl:rotate算法
/*
所有序号为 (j+i *m) % n (j 表示每个循环链起始位置，i 为计数变量，m 表示左旋转
位数，n 表示字符串长度)，会构成一个循环链（共有 gcd(n,m)个，gcd 为 n、m 的最大公
约数），每个循环链上的元素只要移动一个位置即可，最后整个过程总共交换了 n 次（每一
次循环链，是交换 n/gcd(n,m)次，总共 gcd(n,m)个循环链。所以，总共交换 n 次）。
*/
//最大公约数算法
int Gcd(int m, int n){
	while (n!=0){
		int r = m%n;
		m = n;
		n = r;
	}
	return m;
}
//rotate算法
void StlRotate(string &str, int m){
	int lenOfStr = str.length();
	int numOfGroup = Gcd(lenOfStr, m);
	int elemInSub = lenOfStr / numOfGroup;
	for (int j = 0; j < numOfGroup; j++){
		//对应上面的文字描述，外循环次数 j 为循环链的个数，即 gcd(n, m)个循环链
		char tmp = str[j];
		for (int i = 0; i < elemInSub - 1; i++){
			//内循环次数 i 为，每个循环链上的元素个数，n/gcd(m,n)次 
			str[(j + i*m) % lenOfStr] = str[(j + (i + 1)*m) % lenOfStr];
		}
		str[(j + (elemInSub - 1)*m) % lenOfStr] = tmp;
	}
}

//调用
void LeftRotateString::LeftRotateStringDeal(){
	//翻转方法
	char s[] = "abcdefghij";
	cout << left(s, 3) << endl;

	//使用两个指针方式处理
	string ch = "abcdefghijk";
	Rotate(ch, 3);
	cout << ch << endl;

	string chTwo = "abcdefghijk";
	RotateTwo(chTwo, 3);
	cout << chTwo << endl;

	string chThree = "abcdefg";
	int len = chThree.length();
	for (int m = -2 * len; m <= len * 2; m++){
		string s = "abcdefg";
		RotateThree(s, m);
		cout << positiveMod(m, len) << ":" << s << endl;
	}

	int recursei = 3;
	string securseStr = "abcdefghijk";
	int recurselen = securseStr.length();
	RotateRecurse(securseStr, recurselen, recursei%recurselen, 0, recurselen - 1, true);
	cout << securseStr << endl;

	string stlStr = "abcdefjk";
	StlRotate(stlStr, 3);
	cout << stlStr << endl;
	return;
}
