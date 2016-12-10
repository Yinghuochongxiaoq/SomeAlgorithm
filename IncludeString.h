#pragma once

/*
题目描述： 
假设这有一个各种字母组成的字符串， 假设这还有另外一个字符串， 而且这个字符串里的字
母数相对少一些。 从算法是讲， 什么方法能最快的查出所有小字符串里的字母在大字符串里
都有？ 
比如，如果是下面两个字符串： 
String 1: ABCDEFGHLMNOPQRS 
String 2: DCGSRQPOM 
答案是 true，所有在 string2 里的字母 string1 也都有。 
   
如果是下面两个字符串：   
String 1: ABCDEFGHLMNOPQRS    
String 2: DCGSRQPOZ   
答案是 false，因为第二个字符串里的 Z 字母不在第一个字符串里。
*/
class IncludeString
{
public:
	IncludeString(void);
	~IncludeString(void);
	void IncludeStringDeal();
};

