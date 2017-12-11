#pragma once
#include"huffman_tree.h"
#include"utility.h"
#include"string.h"

#include<stdio.h>
struct BufferType
{
	char ch;//字符
	unsigned int bits;//实际比特数
};
class HuffmanCompress
{
protected:
	//哈夫曼压缩类的数据成员：
	HuffmanTree<char, unsigned long>*pHuffmanTree;
	FILE *infp, *outfp;//输入/输出文件
	BufferType buf;//字符缓存
	//辅助函数：
	void Write(unsigned int bit);//向目标文件中写入一个比特
	void WriteToOutfp();//强行将字符缓存写入目标文件
public:
	//哈夫曼压缩类方法声明及重载编译系统默认方法声明
	HuffmanCompress();//无参数的构造函数
	~HuffmanCompress();//析构函数
	void Compress();//压缩算法
	void DeCompress();//解压缩算法
	HuffmanCompress(const HuffmanCompress &copy);//复制构造函数
	HuffmanCompress &operator=(const HuffmanCompress &copy);//赋值运算符重载
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
//操作结果：向目标文件中写入一个比特
{
	buf.bits++;//缓存比特数自增1
	buf.ch = (buf.ch << 1) | bit;//将bit加入到缓存字符中
	if (buf.bits == 8)
	{//缓存区已满，写入目标文件
		fputc(buf.ch, outfp);//写入目标文件
		buf.bits = 0;//初始化bits
		buf.ch = 0;//初始化ch
	}
}
void HuffmanCompress::WriteToOutfp()
//操作结果：强行将字符缓存写入目标文件
{
	unsigned int len = buf.bits;//缓存实际比特数
	if (len > 0)
	{//缓存非空，将缓存的比特个数增加到8，自动写入目标文件
		for (unsigned int i = 0; i < 8 - len; i++)Write(0);
	}
}
void HuffmanCompress::Compress()
//操作结果：用哈夫曼编码压缩文件
{
	char infName[256], outfName[256];//输入（源）/输出（目标）文件名
	cout << "请输入源文件名（文件小于4GB）：";//被压缩文件小于4GB
	cin >> infName;//输入源文件名
	if ((infp = fopen(infName, "rb")) == NULL)
		throw Error("打开源文件失败！");//抛出异常
	//char cha1;
	fgetc(infp);//取出源文件第一个字符
	if (feof(infp))
		throw Error("空源文件！");//抛出异常
	cout << "请输入目标文件：";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
		throw Error("打开目标文件失败！");//抛出异常
	cout << "正在处理，请稍后……" << endl;
	const unsigned long n = 256;//字符个数
	char ch[n];//字符数组
	unsigned long w[n];//字符出现频度（权）
	unsigned long i, size = 0;
	char cha;
	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;//初始化吃[i]
		w[i] = 0;//初始化w[i]
	}
	rewind(infp);//使源文件指针指向文件开始处
	cha = fgetc(infp);//取出源文件第一个字符
	while (!feof(infp))
	{//统计字符出现频度
		w[(unsigned char)cha]++;//字符cha出现频度自加1
		size++;//文件大小自加1
		cha = fgetc(infp);//取出源文件下一个字符
	}
	if (pHuffmanTree != NULL)delete[]pHuffmanTree;//释放空间
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);//生成哈夫曼树
	rewind(outfp);//使目标文件指针指向文件开始处
	fwrite(&size, sizeof(unsigned long), 1, outfp);//向目标文件写入源文件大小
	for (i = 0; i < n; i++)
	{//向目标文件写入字符出现频度
		fwrite(&w[i], sizeof(unsigned long), 1, outfp);
	}
	buf.bits = 0;//初始化bits
	buf.ch = 0;//初始化ch
	rewind(infp);//使源文件指针指向文件开始处
	cha = fgetc(infp);//取出源文件的第一个字符
	while (!feof(infp))
	{//对源文件字符进行编码，并将编码写入目标文件
		String strTmp = pHuffmanTree->Encode(cha);//字符编码
		for (int i = 0; i < strTmp.Length(); i++)
		{//向目标文件写入编码
			if (strTmp[i] == '0')Write(0);//向目标文件写入0
			else Write(1);//向目标文件写入1
		}
		cha = fgetc(infp);//取出源文件的下一个字符
	}
	WriteToOutfp();//强行写入目标文件
	fclose(infp); fclose(outfp);//关闭文件
	cout << "处理结束。" << endl;
}
void HuffmanCompress::DeCompress()
{
	char infName[256], outfName[256];//输入（压缩）/输出（目标）文件名
	cout << "请输入压缩文件名：";
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)
		throw Error("打开压缩文件失败！");//抛出异常
	fgetc(infp);//取出压缩文件第一个字符
	if (feof(infp))
		throw Error("压缩文件为空！");//抛出异常
	cout << "请输入目标文件名：";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
		throw Error("打开目标文件失败！");//抛出异常
	cout << "正在处理，请稍后……" << endl;
	const unsigned long n = 256;//字符个数
	char ch[n];//字符数组
	unsigned long w[n];//权
	unsigned long i, size = 0;
	char cha;
	rewind(infp);//使源文件指针指向文件开始处
	fread(&size, sizeof(unsigned long), 1, infp);//读取目标文件的大小
	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;//初始化ch[i]
		fread(&w[i], sizeof(unsigned long), 1, infp);//读取字符频度
	}
	if (pHuffmanTree != NULL)delete[]pHuffmanTree;//释放空间
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);//生成哈夫曼树
	unsigned long len = 0;//解压的字符数
	cha = fgetc(infp);//取出源文件的第一个字符
	while (!feof(infp))
	{
		String strTmp = "";//将cha转换二进制形式的串
		unsigned char c = (unsigned char)cha;//将cha转换成unsigned char类型
		for (i = 0; i < 8; i++)
		{//将c转换成二进制串
			if (c < 128)Concat(strTmp, "0");//最高位为0
			else Concat(strTmp, "1");//最高位为1
			c = c << 1;//左移一位
		}
		String strTemp(pHuffmanTree->Decode(strTmp));//译码
		for (int i = 1; i <= strTemp.Length(); i++)
		{//向目标文件写入字符
			len++;//目标文件长度自加1
			fputc(strTemp[i - 1], outfp);//将字符写入目标文件中
			if (len == size)break;//解压完毕退出内循环
		}
		if (len == size)break;//解压完毕退出外循环
		cha = fgetc(infp);//取出源文件的下一个字符
	}
	fclose(infp); fclose(outfp);//关闭文件
	cout << "处理结束。" << endl;
}