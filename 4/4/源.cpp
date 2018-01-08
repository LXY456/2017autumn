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
	try														// ��try��װ���ܳ����쳣�Ĵ���
	{
		char inFileName[256], outFileName[256];

		if (argc > 1) strcpy(inFileName, argv[1]);			// ���������в���
		else strcpy(inFileName, "1.txt");			// �������в���
		ifstream inFile(inFileName);						// �������ļ�

															//if (inFile == 0) throw Error("���ܴ򿪿γ���Ϣ�ļ�!");	// �׳��쳣

		if (argc > 2) strcpy(outFileName, argv[2]);			// ���������в���
		else strcpy(outFileName, "2.txt");	// �������в���
		ofstream outFile(outFileName);						// ������ļ�
															//if (outFile == 0)  throw Error("���ܴ򿪿γ̱��ļ�!");	// �׳��쳣

		cout << "�γ���Ϣ�ļ�Ϊ: " << inFileName << endl << endl;
		cout << "�����ſΣ����Ժ�..." << endl << endl;

		Schedule<8> rc(&inFile, &outFile);					// ��ʾ��8ѧ�ڿ�(�ӵ�1ѧ�ڵ���8ѧ��)
		rc.Read();								// ����γ���Ϣ
		rc.TopologicalOrder();					// �������ŵ�˼�����ſ�
		rc.Write();								// ����α�

		cout << "�ſν������α��ļ�Ϊ: " << outFileName << endl;
	}
	catch (Error err)							// ��׽�������쳣
	{
		err.Show();								// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");							// ���ÿ⺯��system()
	return 0;									// ����ֵ0, ���ز���ϵͳ
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
		cout << "��" << linenum << "��" << endl;
		for (int i = 0; i < 5; ++i)
		{
			sum += intarr[i];
			cout << intarr[i] << endl;
		}
		cout << "��" << linenum << "�кͣ�" << sum << endl;
	}
	system("PAUSE");
	return 0;*/