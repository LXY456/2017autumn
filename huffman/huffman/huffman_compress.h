#pragma once
#include"huffman_tree.h"
#include"utility.h"
#include"string.h"

#include<stdio.h>
struct BufferType
{
	char ch;//�ַ�
	unsigned int bits;//ʵ�ʱ�����
};
class HuffmanCompress
{
protected:
	//������ѹ��������ݳ�Ա��
	HuffmanTree<char, unsigned long>*pHuffmanTree;
	FILE *infp, *outfp;//����/����ļ�
	BufferType buf;//�ַ�����
	//����������
	void Write(unsigned int bit);//��Ŀ���ļ���д��һ������
	void WriteToOutfp();//ǿ�н��ַ�����д��Ŀ���ļ�
public:
	//������ѹ���෽�����������ر���ϵͳĬ�Ϸ�������
	HuffmanCompress();//�޲����Ĺ��캯��
	~HuffmanCompress();//��������
	void Compress();//ѹ���㷨
	void DeCompress();//��ѹ���㷨
	HuffmanCompress(const HuffmanCompress &copy);//���ƹ��캯��
	HuffmanCompress &operator=(const HuffmanCompress &copy);//��ֵ���������
};
HuffmanCompress::HuffmanCompress()
{
	pHuffmanTree = NULL;
}
HuffmanCompress::~HuffmanCompress()
{
	if (pHuffmanTree != NULL)delete[]pHuffmanTree;
}
void HuffmanCompress::Write(unsigned int bit)
//�����������Ŀ���ļ���д��һ������
{
	buf.bits++;//�������������1
	buf.ch = (buf.ch << 1) | bit;//��bit���뵽�����ַ���
	if (buf.bits == 8)
	{//������������д��Ŀ���ļ�
		fputc(buf.ch, outfp);//д��Ŀ���ļ�
		buf.bits = 0;//��ʼ��bits
		buf.ch = 0;//��ʼ��ch
	}
}
void HuffmanCompress::WriteToOutfp()
//���������ǿ�н��ַ�����д��Ŀ���ļ�
{
	unsigned int len = buf.bits;//����ʵ�ʱ�����
	if (len > 0)
	{//����ǿգ�������ı��ظ������ӵ�8���Զ�д��Ŀ���ļ�
		for (unsigned int i = 0; i < 8 - len; i++)Write(0);
	}
}
void HuffmanCompress::Compress()
//����������ù���������ѹ���ļ�
{
	char infName[256], outfName[256];//���루Դ��/�����Ŀ�꣩�ļ���
	cout << "������Դ�ļ������ļ�С��4GB����";//��ѹ���ļ�С��4GB
	cin >> infName;//����Դ�ļ���
	if ((infp = fopen(infName, "rb")) == NULL)
		throw Error("��Դ�ļ�ʧ�ܣ�");//�׳��쳣
	//char cha1;
	fgetc(infp);//ȡ��Դ�ļ���һ���ַ�
	if (feof(infp))
		throw Error("��Դ�ļ���");//�׳��쳣
	cout << "������Ŀ���ļ���";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
		throw Error("��Ŀ���ļ�ʧ�ܣ�");//�׳��쳣
	cout << "���ڴ������Ժ󡭡�" << endl;
	const unsigned long n = 256;//�ַ�����
	char ch[n];//�ַ�����
	unsigned long w[n];//�ַ�����Ƶ�ȣ�Ȩ��
	unsigned long i, size = 0;
	char cha;
	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;//��ʼ����[i]
		w[i] = 0;//��ʼ��w[i]
	}
	rewind(infp);//ʹԴ�ļ�ָ��ָ���ļ���ʼ��
	cha = fgetc(infp);//ȡ��Դ�ļ���һ���ַ�
	while (!feof(infp))
	{//ͳ���ַ�����Ƶ��
		w[(unsigned char)cha]++;//�ַ�cha����Ƶ���Լ�1
		size++;//�ļ���С�Լ�1
		cha = fgetc(infp);//ȡ��Դ�ļ���һ���ַ�
	}
	if (pHuffmanTree != NULL)delete[]pHuffmanTree;//�ͷſռ�
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);//���ɹ�������
	rewind(outfp);//ʹĿ���ļ�ָ��ָ���ļ���ʼ��
	fwrite(&size, sizeof(unsigned long), 1, outfp);//��Ŀ���ļ�д��Դ�ļ���С
	for (i = 0; i < n; i++)
	{//��Ŀ���ļ�д���ַ�����Ƶ��
		fwrite(&w[i], sizeof(unsigned long), 1, outfp);
	}
	buf.bits = 0;//��ʼ��bits
	buf.ch = 0;//��ʼ��ch
	rewind(infp);//ʹԴ�ļ�ָ��ָ���ļ���ʼ��
	cha = fgetc(infp);//ȡ��Դ�ļ��ĵ�һ���ַ�
	while (!feof(infp))
	{//��Դ�ļ��ַ����б��룬��������д��Ŀ���ļ�
		String strTmp = pHuffmanTree->Encode(cha);//�ַ�����
		for (int i = 0; i < strTmp.Length(); i++)
		{//��Ŀ���ļ�д�����
			if (strTmp[i] == '0')Write(0);//��Ŀ���ļ�д��0
			else Write(1);//��Ŀ���ļ�д��1
		}
		cha = fgetc(infp);//ȡ��Դ�ļ�����һ���ַ�
	}
	WriteToOutfp();//ǿ��д��Ŀ���ļ�
	fclose(infp); fclose(outfp);//�ر��ļ�
	cout << "���������" << endl;
}
void HuffmanCompress::DeCompress()
{
	char infName[256], outfName[256];//���루ѹ����/�����Ŀ�꣩�ļ���
	cout << "������ѹ���ļ�����";
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)
		throw Error("��ѹ���ļ�ʧ�ܣ�");//�׳��쳣
	fgetc(infp);//ȡ��ѹ���ļ���һ���ַ�
	if (feof(infp))
		throw Error("ѹ���ļ�Ϊ�գ�");//�׳��쳣
	cout << "������Ŀ���ļ�����";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
		throw Error("��Ŀ���ļ�ʧ�ܣ�");//�׳��쳣
	cout << "���ڴ������Ժ󡭡�" << endl;
	const unsigned long n = 256;//�ַ�����
	char ch[n];//�ַ�����
	unsigned long w[n];//Ȩ
	unsigned long i, size = 0;
	char cha;
	rewind(infp);//ʹԴ�ļ�ָ��ָ���ļ���ʼ��
	fread(&size, sizeof(unsigned long), 1, infp);//��ȡĿ���ļ��Ĵ�С
	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;//��ʼ��ch[i]
		fread(&w[i], sizeof(unsigned long), 1, infp);//��ȡ�ַ�Ƶ��
	}
	if (pHuffmanTree != NULL)delete[]pHuffmanTree;//�ͷſռ�
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);//���ɹ�������
	unsigned long len = 0;//��ѹ���ַ���
	cha = fgetc(infp);//ȡ��Դ�ļ��ĵ�һ���ַ�
	while (!feof(infp))
	{
		String strTmp = "";//��chaת����������ʽ�Ĵ�
		unsigned char c = (unsigned char)cha;//��chaת����unsigned char����
		for (i = 0; i < 8; i++)
		{//��cת���ɶ����ƴ�
			if (c < 128)Concat(strTmp, "0");//���λΪ0
			else Concat(strTmp, "1");//���λΪ1
			c = c << 1;//����һλ
		}
		String strTemp(pHuffmanTree->Decode(strTmp));//����
		for (int i = 1; i <= strTemp.Length(); i++)
		{//��Ŀ���ļ�д���ַ�
			len++;//Ŀ���ļ������Լ�1
			fputc(strTemp[i - 1], outfp);//���ַ�д��Ŀ���ļ���
			if (len == size)break;//��ѹ����˳���ѭ��
		}
		if (len == size)break;//��ѹ����˳���ѭ��
		cha = fgetc(infp);//ȡ��Դ�ļ�����һ���ַ�
	}
	fclose(infp); fclose(outfp);//�ر��ļ�
	cout << "���������" << endl;
}