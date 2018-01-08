#include <iostream>
#include <stdio.h>
#include <fstream>
/*#include <sstream>
#include"adj_list_dir_graph.h"
#include"adj_list_graph_vex_node.h"
#include"lk_list.h"
#include"lk_queue.h"
#include"node.h"*/
#include"schedule.h"
//#include"utility.h"
using namespace std;

int main(int argc, char *argv[])
{
	try														// 用try封装可能出现异常的代码
	{
		char inFileName[256], outFileName[256];

		if (argc > 1) strcpy(inFileName, argv[1]);			// 存在命令行参数
		else strcpy(inFileName, "1.txt");			// 无命令行参数
		ifstream inFile(inFileName);						// 输入流文件

															//if (inFile == 0) throw Error("不能打开课程信息文件!");	// 抛出异常

		if (argc > 2) strcpy(outFileName, argv[2]);			// 存在命令行参数
		else strcpy(outFileName, "2.txt");	// 无命令行参数
		ofstream outFile(outFileName);						// 输出流文件
															//if (outFile == 0)  throw Error("不能打开课程表文件!");	// 抛出异常

		cout << "课程信息文件为: " << inFileName << endl << endl;
		cout << "正在排课，请稍候..." << endl << endl;

		Schedule<8> rc(&inFile, &outFile);					// 表示排8学期课(从第1学期到第8学期)
		rc.Read();								// 输入课程信息
		rc.TopologicalOrder();					// 用拓扑排的思进行排课
		rc.Write();								// 输出课表

		cout << "排课结束，课表文件为: " << outFileName << endl;
	}
	catch (Error err)							// 捕捉并处理异常
	{
		err.Show();								// 显示异常信息
	}

	system("PAUSE");							// 调用库函数system()
	return 0;									// 返回值0, 返回操作系统
}
	/*char line[256];
	string arr[6];
	int linenum = 1;
	ifstream ifile("1.txt");
	while (ifile.good())
	{
		ifile.getline(line, 256);
		istringstream iss(line);
		iss >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4] >>arr[5];
		for (int i = 0; i < 6; i++)
		{
			cout << arr[i] << "\t";
		}
		cout << endl;
	}
	system("PAUSE");*/
	/*char line[256];
	int intarr[5];
	int linenum = 1;
	ifstream ifile("1.txt");
	while (ifile.good())
	{
		int sum = 0;
		ifile.getline(line, 256);
		istringstream iss(line);
		iss >> intarr[0] >> intarr[1] >> intarr[2] >> intarr[3] >> intarr[4];
		cout << "第" << linenum << "行" << endl;
		for (int i = 0; i < 5; ++i)
		{
			sum += intarr[i];
			cout << intarr[i] << endl;
		}
		cout << "第" << linenum << "行和：" << sum << endl;
	}
	system("PAUSE");
	return 0;*/