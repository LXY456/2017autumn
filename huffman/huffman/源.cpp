#include"huffman_compress.h"
int main(void)
{
	try
	{
		int i = 0;
	loop1:
		cout << "1.Huffman compress" << endl;
		cout << "2.Huffman decompress" << endl;
			cout << "3.Exit" << endl;
			cout << "Please select:";
			cin >> i;
			if (i == 1)
			{
				HuffmanCompress a;
				a.Compress();
				cout << endl;
				goto loop1;
			}
			if (i == 2)
			{
				HuffmanCompress b;
				b.DeCompress();
				cout << endl;
				goto loop1;
			}
			if (i == 3)
			{
				system("PAUSE");
			}
			if (i != 1 && i != 2 && i != 3)
			{
				cout << endl;
				cout << "Please input 1 or 2 or 3"<<endl<<endl;
				goto loop1;
			}
	}
	catch(Error err)
	{
		err.Show();
	}
	return 0;
}