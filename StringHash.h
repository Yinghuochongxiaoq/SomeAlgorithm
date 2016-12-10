/*********************************StringHash.h*********************************/

#pragma once
#include <string>
using namespace std;
#define MAXTABLELEN 1024 // 默认哈希索引表大小 
////////////////////////////////////////////////////////////////////////// 
// 哈希索引表定义 
typedef struct _HASHTABLE
{
	long nHashA;
	long nHashB;
	bool bExists;
}HASHTABLE, *PHASHTABLE;

//一种可能的结构体定义？
typedef struct{
	char *pkey;
	int weight;
}KEYNODE, *key_list;

class StringHash
{
public:
	StringHash(const long nTableLength = MAXTABLELEN);
	~StringHash(void);
private:
	unsigned long cryptTable[0x500];
	unsigned long m_tablelength; // 哈希索引表长度 
	HASHTABLE *m_HashIndexTable;
private:
	void InitCryptTable(); // 对哈希索引表预处理 
public:
	bool Hash(string url);
	unsigned long Hashed(string url); // 检测url是否被hash过
	unsigned long HashString(const string& lpszString, unsigned long dwHashType);// 求取哈希值
	int InsertString(const string inputString);
};
