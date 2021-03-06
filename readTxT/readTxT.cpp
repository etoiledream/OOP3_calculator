// readTxT.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
istream *input;
vector<string> fileName;
int parseCommandLine(int argc, char* argv[])
{
	if (argc == 1)
	{
		input = &cin;
		return 0;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
			fileNames.push_back(argv[i]);
		// 接着先打开第1个输入文件
		input = new ifstream(fileNames[0]);
		//接着判断文件是否成功打开了—这个检测的方法较多，如：
		//为true时就表示成功打开了
		if (input->good())
		{
			//若成功打开则 接着可将第1个文件名剔除：
			input = &cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else
			return 1;

		//最后若成功打开则返回0，否则返回非0值并报错。
	}
}

int lexer::switch_input()
{
	if (fileNames.empty())
	{
		return 1;
	}  /*没有文件了*/
	else
	{
		delete input; //关闭上个文件，接着打开下个文件
		input = new ifstream(fileNames[0]);
		//接着判断文件是否成功打开了—这个检测的方法较多，如：
		//为true时就表示成功打开了
		if (input->good()) {
			//若成功打开则 接着可将第1个文件名剔除：
			input = &cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else {
			return 1;
		}

		//最后若成功打开则返回0，否则返回非0值并报错。
	}
}
int main(int argc, char* argv[])
{
	if (parseCommandLine(argc, argv) != 0)
	{
		cout << "文件无法打开" << endl;
		return 1;
	}
    return 0;
}

