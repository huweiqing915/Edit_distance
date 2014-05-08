/*************************************************************************
	> File Name: test_dic.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月07日 星期三 22时09分03秒
 ************************************************************************/

#include "Dictionary.h"

int main()
{
	Dictionary dict;
	dict.traversal_dir("/home/hwq/src/0507/data");
//	dict.read_file("/home/hwq/src/0507/demo/in.txt");
	dict.write_dictionary("/home/hwq/src/0507/demo/dictionary.txt");
	return 0;
}
