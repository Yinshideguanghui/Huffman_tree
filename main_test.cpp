#include"Huffman_tree.h"
#define MAX_characters 65535		//最大读入字符数

//读入txt文件并统计字符频率，建立Huffman树
Huffman_tree read_txt()
{
	int max_characters = MAX_characters;			//最大读入字符数
	ifstream dataIn;
	char* content = new char[max_characters + 1];	//用来存储读入内容，最后加一个空字符作为结尾
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//初始化为空字符
	string filename;	//文件名
	cout << "请输入要打开的txt文件名：";
	cin >> filename;
	dataIn.open(filename.c_str());	//打开文件
	if (dataIn.is_open())	//如果打开成功
	{
		cout << "打开成功，正在读取..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//如果打开失败
		cout << "\n打开失败" << endl;
	dataIn.close();			//关闭文件
	//循环求文本长度
	int txt_length = 0;
	while (content[txt_length] != '\0')
		txt_length++;
	//初始化统计变量
	cout << "开始统计...\n";
	Record* Records = new Record[txt_length];	//储存字符Record
	int ii = 0;									//当前在文本中位置
	int count_of_kinds = 0;						//有几种字符
	bool duplication = false;					//当前字符是否已有Record
	int duplication_pos = 0;					//重复的字符在已有Record中的位置
	//统计出现次数
	while (content[ii] != '\0')
	{
		//找有没有已有当前字符的记录
		for (int jj = 0; jj < count_of_kinds; jj++)
			if (Records[jj].retrieve_item() == content[ii])
			{
				duplication = true;
				duplication_pos = jj;
				break;
			}
		//根据是否重复来处理
		if (duplication)	//已有该字符的Record
		{
			Records[duplication_pos].weight_plus(1.0);
			duplication = false;
		}
		else				//没有该字符的Record
		{
			Records[count_of_kinds].set_item(content[ii]);
			Records[count_of_kinds].weight_plus(1.0);
			count_of_kinds++;
		}
		ii++;
	}
	//生成统计结果
	Record* result = new Record[count_of_kinds];
	for (int jj = 0; jj < count_of_kinds; jj++)
	{
		result[jj] = Records[jj];
		result[jj].weight_divide(txt_length);
	}
	//建立哈夫曼树并返回
	Huffman_tree result_tree(result, count_of_kinds);
	return result_tree;
}

//用Huffman树编码指定的txt文件并输出到encode_result.txt
void encode_out_test(Huffman_tree& test_Huffman_tree)
{
	//读入字符串
	int max_characters = MAX_characters;			//最大读入字符数
	ifstream dataIn;
	ofstream dataOut;
	char* content = new char[max_characters + 1];	//用来存储读入内容，最后加一个空字符作为结尾
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//初始化为空字符
	string filename;	//文件名
	cout << "请输入要打开的txt文件名：";
	cin >> filename;
	dataIn.open(filename.c_str());	//打开文件
	if (dataIn.is_open())	//如果打开成功
	{
		cout << "打开成功，正在读取..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//如果打开失败
		cout << "\n打开失败" << endl;
	dataIn.close();			//关闭文件
	//编码
	string txt_content = content;
	string result = test_Huffman_tree.encode(txt_content);
	//输出
	dataOut.open("encode_result.txt");
	dataOut << result;
	dataOut.close();
}

//用Huffman树解码encode_result.txt并输出到decode_result.txt
void decode_out_test(Huffman_tree& test_Huffman_tree)
{
	//读入字符串
	int max_characters = MAX_characters;			//最大读入字符数
	ifstream dataIn;
	ofstream dataOut;
	char* content = new char[max_characters + 1];	//用来存储读入内容，最后加一个空字符作为结尾
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//初始化为空字符
	dataIn.open("encode_result.txt");	//打开文件
	if (dataIn.is_open())	//如果打开成功
	{
		cout << "打开成功，正在读取..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//如果打开失败
		cout << "\n打开失败" << endl;
	dataIn.close();			//关闭文件
	//编码
	string txt_content = content;
	string result = test_Huffman_tree.decode(txt_content);
	//输出
	dataOut.open("decode_result.txt");
	dataOut << result;
	dataOut.close();
}

//帮助界面
void help()
{
	cout << endl
		<< "该程序允许用户每次输入一个字母命令（仅限一个）\n"
		<< "有效命令包括：\n"
		<< "W-用当前树编码指定的txt文件并输出到encode_result.txt\n"
		<< "w-读入encode_result.txt并用当前树译码到decode_result.txt\n"
		<< "X-显示当前哈夫曼树编码\n"
		<< "E-将接下来输入的字符串（仅限ABFDEFGH构成）编码\n"
		<< "D-将接下来输入的比特流（仅限01构成）译码\n"
		<< "H-显示本帮助\n"
		<< "Q-退出\n"
		<< "按一次 <Enter> 以继续" << flush;
	char c;
	do { cin.get(c); } while (c != '\n');
}
//接收命令
char get_command()
{
	char command;
	bool waiting = true;
	cout << "\n输入命令后按 <Enter>:";
	while (waiting)
	{
		cin.get(command);
		if (command == 'W' || command == 'w' || command == 'X' ||
			command == 'E' || command == 'D' || command == 'H' ||
			command == 'Q')
			waiting = false;
		else
			cout << "请输入有效命令: ";
	}
	while ((getchar()) != '\n');	//吸收多余输入
	return command;
}
//执行命令
bool do_command(char c, Huffman_tree& test_Huffman_tree)
{
	bool continue_input = true;
	switch (c)
	{
	case'W':
	{
		encode_out_test(test_Huffman_tree);
		cout << "编码完成" << endl;
		cin.get();		//吸收回车
		break;
	}
	case'w':
	{
		decode_out_test(test_Huffman_tree);
		cout << "译码完成" << endl;
		break;
	}
	case 'X':
		test_Huffman_tree.Huffman_display();
		break;
	case 'E':
	{
		string chars;
		cout << "请输入要编码的字符串：";
		cin >> chars;
		cin.get();		//吸收回车
		cout << "编码结果：" << test_Huffman_tree.encode(chars) << endl;
		break;
	}
	case 'D':
	{
		string bits;
		cout << "请输入要译码的比特流：";
		cin >> bits;
		cin.get();		//吸收回车
		cout << "译码结果：" << test_Huffman_tree.decode(bits) << endl;
		break;
	}
	case 'H':
		help();
		break;
	case 'Q':
		cout << "测试结束" << endl;
		continue_input = false;
		break;
	}
	return continue_input;
}

int main()
{
	//进入测试
	cout << "开始测试...\n";
	//读入txt文件并建立Huffman树
	Huffman_tree test_Huffman_tree = read_txt();
	//指令测试
	help();
	while (do_command(get_command(), test_Huffman_tree)) {}
	return 0;
}