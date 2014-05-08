/*************************************************************************
	> File Name: chinese_edit.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 18时43分09秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include "EncodingConverter.h"

using namespace std;

inline int min(int a, int b, int c)
{
	int t = a < b ? a : b;
	return t < c ? t : c;
}

int count_size(const string &str)
{
	int size = 0;
	string::size_type ix = 0;
	while(ix != str.length())
	{
		if(str[ix] & 0x80)	//第一位为1，说明是gbk码
		{
			ix = ix + 2;	//两个字节为一个汉字
			size ++;
		}
		else	//第一位为0,说明是ascii码
		{
			ix ++;
			size ++;
		}
	}
	return size;
}

uint16_t * change_to_short(const string &str, int len)
{
	uint16_t *arr = new uint16_t[len];	//申请一段字符长度的空间
	int count = 0;
	string::size_type ix = 0;
	while(ix != str.length() && count != len)
	{
		if(str[ix] & 0x80)	//gbk码
		{
			arr[count ++] = (str[ix] << 8) + str[ix + 1];
			ix = ix + 2;
		}
		else	//ascii码
		{
			arr[count ++] = str[ix];
			ix ++;
		}
	}
	return arr;
}


int edit_distance(const string &a, const string &b)
{
	int len1 = count_size(a);
	int len2 = count_size(b);
	uint16_t *short_a = change_to_short(a, len1);
	uint16_t *short_b = change_to_short(b, len2);

	int **mem = new int *[len1 + 1];
	for(int k = 0; k <= len1; ++k)
	{
		mem[k] = new int[len2 + 1];
	}
	//initilize
	for(int i = 0; i <= len1; ++i)
	{
		mem[i][0] = i;
	}
	for(int j = 0; j <= len2; ++j)
	{
		mem[0][j] = j;
	}

	//DP
	for(int i = 1; i <= len1; ++i)
	{
		for(int j = 1; j <= len2; ++j)
		{
			int cost = (short_a[i-1] == short_b[j-1] ? 0 : 1);
			int deletion = mem[i-1][j] + 1;
			int insertion = mem[i][j-1] + 1;
			int substitution = mem[i-1][j-1] + cost;
			mem[i][j] = min(deletion, insertion, substitution);
		}
	}
	int ret = mem[len1][len2];
	for(int k = 0; k <= len1; ++k)
	{
		delete [] mem[k];
	}
	//delete [] short_a;
	//delete [] short_b;
	delete [] mem;
	return ret;
}

int main()
{
	string s1, s2;
	EncodingConverter trans;
	while(cin >> s1 >> s2)
	{
		cout << "edit distance:" << edit_distance(trans.utf8_to_gbk(s1), trans.utf8_to_gbk(s2)) << endl;
	}
	return 0;
}