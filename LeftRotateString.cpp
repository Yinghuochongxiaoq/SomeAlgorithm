#include "stdafx.h"
#include "LeftRotateString.h"
#include <string>
#include <iostream>
using namespace std;

//���캯��
LeftRotateString::LeftRotateString()
{
}

//��������
LeftRotateString::~LeftRotateString()
{
}

/*
����1��
��һ���ַ����ֳ������֣�X �� Y �������֣����ַ����϶��巴ת�Ĳ��� X^T������ X ��
�����ַ���ת���磬X="abc"����ô X^T="cba"������ô���ǿ��Եõ�����Ľ��ۣ�
(X^TY^T)^T=YX����Ȼ������Ϳ���ת��Ϊ�ַ����ķ�ת�������ˡ�
����ô?ok,���� abcdef ���������˵���ǳ���̵����䣬��ϸ����һ���Ͷ�����
1�����ȷ�Ϊ�����֣�X:abc��Y:def��
2��X->X^T��abc->cba�� Y->Y^T��def->fed��
3��(X^TY^T)^T=YX��cbafed->defabc����������ת��
*/

//����������������
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

// ��ת���� posΪҪ��ת���ַ��������򳤶ȣ��������ʹ��
char *left(char *s, int pos){
	int len = strlen(s);
	//���ϣ�X->X^T���� abc->cba
	Invert(s, s + (pos - 1));
	//���ϣ�Y->Y^T���� def->fed
	Invert(s + pos, s + (len - 1));
	//���ϣ�Y->Y^T���� def->fed  
	Invert(s, s + (len - 1));
	return s;
}

/*
1.2����ָ���𲽷�ת
����ת�ַ�����abcdefΪ��
1��ab->ba
2��cdef->fedc ԭ�ַ�����Ϊbafedc
3��������ת��cdefab
ֻҪ���η�ת��ʱ�临�Ӷ�ҲΪO��n��

��һ��˼·
abc defghi��Ҫabc�ƶ������
abc defghi->def abcghi->def ghiabc

��������ָ�룬ƽp1ָ��ch[0]��p2ָ��ch[m]
һ�¹���ѭ��m�Σ�����p1��p2��ָԪ�أ�Ȼ��p1++��p2++

��һ�������� abc �� def ��
abc defghi->def abcghi
�ڶ��������� abc �� ghi��
def abcghi->def ghiabc
�������̣������������� abc һ��һ�� ����ƶ�
abc defghi
def abcghi
def ghi abc
//���� ���Ӷ��� O��m+n��

����Ԫ����9��Ԫ�ص����У���m=3ʱ��p2ǡ��ָ���������һ��Ԫ�أ����i���滹��һ��Ԫ����
���� �����Ҫ����ʮ��Ԫ�ص����У� abcdefghij�� ok�� ���棬 �;�������ӣ� �� abcdefghij
���н�������ת������
��� abcdef ghij Ҫ��� defghij abc��
abcdef ghij
1. def abc ghij
2. def ghi abc j      //��������j ����ǰ��
3. def ghi ab jc
4. def ghi a j bc
5. def ghi j abc

��������
1�������� p1=ch[0]��p2=ch[m]������ p1��p2 ��� m �ľ��룻
2���ж� p2+m-1 �Ƿ�Խ�磬���û��Խ��ת�� 3������ת�� 4��abcdefgh �� 8 ����ĸ���ַ�
������ 4 ��������ô��ʼʱ p2 ָ�� e��p2+4 Խ���ˣ�����ʵ�� p2 �� p2+m-1 �� m ���ַ���
��������һ����������
3�����Ͻ���*p1 ��*p2��Ȼ�� p1++��p2++��ѭ�� m �Σ�Ȼ��ת�� 2��
4����ʱ p2+m-1 �Ѿ�Խ�磬�ڴ�ֻ�账��β�͡��������£�
4.1 ͨ�� n-p2 �õ� p2 ��β��֮��Ԫ�ظ��� r��������Ҫǰ�Ƶ�Ԫ�ظ�����
4.2 ���¹���ִ�� r �Σ�
ch[p2]<->ch[p2-1]��ch[p2-1]<->ch[p2-2]��....��ch[p1+1]<->ch[p1]��p1++��
p2++��
�� p1 ָ�� a��p2 ָ�� j ʱ������ p2+m Խ�磬��ô��ʱ p1��p2 ��Ҫ��
���� p1 ֮��abcjk)����β�ͣ�����β��ֻ�轫 j,k �Ƶ� abc ֮ǰ
*/
//����ָ�뷽��
void Rotate(string &str, int m){
	if (str.length() == 0 || m <= 0) return;

	int n = str.length();

	if (m%n <= 0) return;

	int p1 = 0, p2 = m;
	//���㽻������
	int k = (n - m) - n%m;
	//����p1��p2ָ���Ԫ�أ�Ȼ���ƶ�p1��p2
	while (k--){
		swap(str[p1], str[p2]);
		p1++;
		p2++;
	}

	//����β����rΪβ�����ƴ���
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
	//����һ�����ӣ�abcdefghijk   
	//                    p1    p2   
	//��ִ�е�����ʱ��defghi a b c j k   
	//p2+m ���� �ˣ�   
	//r=n-p2=2���������¹��̣�Ҫִ��ѭ�����Ρ�   
	//��һ�Σ�j ����ǰ�ƣ�abcjk->abjck->ajbck->jabck   
	//Ȼ��p1++��p2++��p1 ָ a��p2 ָ k��   
	//               p1    p2   
	//�ڶ��Σ�defghi j a b c k   
	//ͬ���˺�k ����ǰ�ƣ�abck->abkc->akbc->kabc��
}

/*
������
def ghi abc jk
��p1ָ��a��p2ָ��jʱ����ô����p1��p2
��ʱΪ
def ghi jbc ak
p1++��p2++��p1ָ��b��p2ָ��k����������Ĳ����
def gui jkc ab
p1++��p2������p1ָ��c��p2ָ��b��p1��p2֮�䣨cab��Ҳ����β��
��ô����β�ͣ�cab����Ҫѭ������һ������
*/

void RotateTwo(string &str, int m){
	if (str.length() == 0 || m <= 0) return;
	//��ʼ��p1��p2
	int p1 = 0, p2 = m;
	int n = str.length();

	//����m����n
	if (m%n == 0) return;

	//ѭ��ֱ��p2�����ַ���ĩβ
	while (true){
		swap(str[p1], str[p2]);
		p1++;
		if (p2 < n - 1)
			p2++;
		else break;
	}

	//����β����rΪβ��ѭ�����ƴ���
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
	//��һ������   
	//abcdefghijk   
	//��ִ�е������ʱ��defghiabcjk   
	//      p1    p2   
	//defghi a b c j k��a �� j ������jbcak��Ȼ��p1++��p2++   
	//        p1    p2   
	//       j b c a k��b �� k ������jkcab��Ȼ��p1++��p2 ������   

	//r = m - n % m= 3-11%3=1����ѭ����λ 1 �Ρ�   
	//          p1  p2   
	//       j k c a b   
	//p1 ��ָԪ�� c ʵ�ֱ����� temp �   
	//Ȼ��ִ�д�����䣺str[i] = str[i+1]; �� a �ܵ� c ��λ�ô���a_b   
	//i++���ٴ�ִ�У�str[i] = str[i+1]��ab_   
	//��󣬱���õ� c ���룬Ϊ abc�����ԣ���������Ϊ defghi jk abc��
}

/*
����m>n,������ѭ��m�ı���ʱ�ͻ�ԭ��ԭ����λ�á�
*/
//����ת�ַ���str��mΪ����ʱ��ʾ����abs��m������ĸ
#define positiveMod(m,n) ((m)%(n)+(n))%(n)
void RotateThree(string &str, int m){
	if (str.length() == 0) return;
	int n = str.length();
	//�������str���ȼ�mΪ�����������positiveMod����ȡ��mΪ����ʱ��nȡ��õ�����
	m = positiveMod(m, n);
	if (m == 0) return;
	int p1 = 0, p2 = m;
	int round;
	//p2��ǰ��ָ��֮���m-1����ĸ��m����ĸ���Ϳ��Ժ�p2ǰ���m����ĸ������
	while (p2 + m - 1 < n){
		round = m;
		while (round--){
			swap(str[p1], str[p2]);
			p1++;
			p2++;
		}
	}
	//ʣ�µĲ���m����ĸ�������
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
��������ͨ���ݹ�ת������С����֮��ģ
����˵����һ����ģΪN�����⻯��Ϊ��ģΪM��M<N�������⣻
������˵�����ַ����ܳ���ΪL�����Ҫ��ת�Ĳ��ֳ���Ϊs1����ô����������ѭ����������Ϊs1��С�Σ�ֱ���������ʣ��Ĳ��ֳ���Ϊs2��s2==L%s1��������ֱ�ӽ�����
��������Եݹ�ת���ɹ�ģΪs1+s2�ģ������෴���������󣩵�ͬһ�����⡣���ŵݹ�Ľ��У����ҷ����ص���֪��ĳһ����������L%s1==0������������

��������һ�£�
��ԭʼ����Ϊ������123abcdefg������תΪ��abcdefg123�������ܳ���Ϊ 10����ת��("123")
����Ϊ 3 ������ת������˼·�������㣬�ݱ����Ϊ
��123abcdefg��->"abc123defg"->"abcdef123g"����ʱ��"123"�޷���"g"���Ե���������ݹ�
ת��Ϊ������123g������תΪ"g123"�����ܳ���Ϊ 4����ת��("g")����Ϊ 1 ������ת��

�ٸ���������˵�������£�
1�������ַ��� abc def ghi gk��
�� abc ���Ƶ� def ghi gk ���棬��ʱ n = 11��m = 3��m�� = n % m = 2;
abc def ghi gk -> def ghi abc gk
2�������� gk ���Ƶ� abc ǰ�棬��ʱ n = m�� + m = 5��m = 2��
m�� = n % m=1;
abc gk -> a gk bc
3�������� a ���Ƶ� gk ���棬��ʱ n = m�� + m = 3��m = 1��
m�� = n % m = 0;
a gk bc-> gk a bc�� ���ڴ˿̣�n % m = 0������������������ؽ����

���������ң� ��������� �ٴ������ң� ��˷��������� ֱ������������
�����˳���
*/

//n �������ֵ��ַ������ȣ�m���������ֵ���ת����
//head���������ֵ�ͷָ�룬tail���������ֵ�βָ��
//flag = true ����������flag = false ��������
void RotateRecurse(string &str, int n, int m, int head, int tail, bool flag){
	//��������
	if (head == tail || m <= 0) return;
	if (flag){
		//��ʼ��p1��p2
		int p1 = head;
		int p2 = head + m;
		//1�������������ַ���abc def ghi gk
		//��abc���Ƶ�def ghi gk���棬��ʱn=11,m=3,m'=m%m=2;
		//abc def ghi gk->def ghi abc gk
		//p1,p2�ƶ����룬������6��
		int k = (n - m) - n%m;
		/*---------------------
		����������� k = (n - m) - n % m ��������
		�� p2 Ϊ�ƶ��Ĳ���ϵ��
		n-m �ǿ�ʼʱ p2 ��ĩβ�ĳ��ȣ�n%m ��β�ͳ���
		(n-m)-n%m ���� p2 �ƶ��ľ���
		���� abc def efg hi
		��ʼʱ p2->d,��ô n-m Ϊ def efg hi �ĳ��� 8��
		n%m Ϊβ�� hi �ĳ��� 2��
		��Ϊ��֪�� abc Ҫ�ƶ��� hi ��ǰ�棬�����ƶ�������
		(n-m)-n%m = 8-2 = 6��
		*/
		for (int i = 0; i < k; i++, p1++, p2++) swap(str[p1], str[p2]);
		//������������������
		RotateRecurse(str, n - k, n%m, p1, tail, false);
	}
	else{
		//������������gk���Ƶ�abcǰ�棬��ʱn=m'+m=5,m=2,m'=n%m=1;
		//abc gk ->a gk bc
		int p1 = tail;
		int p2 = tail - m;
		//p1,p2�ƶ����룬�����ƶ�����
		int k = (n - m) - n%m;
		for (int i = 0; i < k; i++, p1--, p2--) swap(str[p1], str[p2]);
		//������������������
		RotateRecurse(str, n - k, n%m, head, p1, true);
	}
}

//stl:rotate�㷨
/*
�������Ϊ (j+i *m) % n (j ��ʾÿ��ѭ������ʼλ�ã�i Ϊ����������m ��ʾ����ת
λ����n ��ʾ�ַ�������)���ṹ��һ��ѭ���������� gcd(n,m)����gcd Ϊ n��m �����
Լ������ÿ��ѭ�����ϵ�Ԫ��ֻҪ�ƶ�һ��λ�ü��ɣ�������������ܹ������� n �Σ�ÿһ
��ѭ�������ǽ��� n/gcd(n,m)�Σ��ܹ� gcd(n,m)��ѭ���������ԣ��ܹ����� n �Σ���
*/
//���Լ���㷨
int Gcd(int m, int n){
	while (n!=0){
		int r = m%n;
		m = n;
		n = r;
	}
	return m;
}
//rotate�㷨
void StlRotate(string &str, int m){
	int lenOfStr = str.length();
	int numOfGroup = Gcd(lenOfStr, m);
	int elemInSub = lenOfStr / numOfGroup;
	for (int j = 0; j < numOfGroup; j++){
		//��Ӧ�����������������ѭ������ j Ϊѭ�����ĸ������� gcd(n, m)��ѭ����
		char tmp = str[j];
		for (int i = 0; i < elemInSub - 1; i++){
			//��ѭ������ i Ϊ��ÿ��ѭ�����ϵ�Ԫ�ظ�����n/gcd(m,n)�� 
			str[(j + i*m) % lenOfStr] = str[(j + (i + 1)*m) % lenOfStr];
		}
		str[(j + (elemInSub - 1)*m) % lenOfStr] = tmp;
	}
}

//����
void LeftRotateString::LeftRotateStringDeal(){
	//��ת����
	char s[] = "abcdefghij";
	cout << left(s, 3) << endl;

	//ʹ������ָ�뷽ʽ����
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
