#include"Huffman_tree.h"
#define MAX_characters 65535		//�������ַ���

//����txt�ļ���ͳ���ַ�Ƶ�ʣ�����Huffman��
Huffman_tree read_txt()
{
	int max_characters = MAX_characters;			//�������ַ���
	ifstream dataIn;
	char* content = new char[max_characters + 1];	//�����洢�������ݣ�����һ�����ַ���Ϊ��β
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//��ʼ��Ϊ���ַ�
	string filename;	//�ļ���
	cout << "������Ҫ�򿪵�txt�ļ�����";
	cin >> filename;
	dataIn.open(filename.c_str());	//���ļ�
	if (dataIn.is_open())	//����򿪳ɹ�
	{
		cout << "�򿪳ɹ������ڶ�ȡ..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//�����ʧ��
		cout << "\n��ʧ��" << endl;
	dataIn.close();			//�ر��ļ�
	//ѭ�����ı�����
	int txt_length = 0;
	while (content[txt_length] != '\0')
		txt_length++;
	//��ʼ��ͳ�Ʊ���
	cout << "��ʼͳ��...\n";
	Record* Records = new Record[txt_length];	//�����ַ�Record
	int ii = 0;									//��ǰ���ı���λ��
	int count_of_kinds = 0;						//�м����ַ�
	bool duplication = false;					//��ǰ�ַ��Ƿ�����Record
	int duplication_pos = 0;					//�ظ����ַ�������Record�е�λ��
	//ͳ�Ƴ��ִ���
	while (content[ii] != '\0')
	{
		//����û�����е�ǰ�ַ��ļ�¼
		for (int jj = 0; jj < count_of_kinds; jj++)
			if (Records[jj].retrieve_item() == content[ii])
			{
				duplication = true;
				duplication_pos = jj;
				break;
			}
		//�����Ƿ��ظ�������
		if (duplication)	//���и��ַ���Record
		{
			Records[duplication_pos].weight_plus(1.0);
			duplication = false;
		}
		else				//û�и��ַ���Record
		{
			Records[count_of_kinds].set_item(content[ii]);
			Records[count_of_kinds].weight_plus(1.0);
			count_of_kinds++;
		}
		ii++;
	}
	//����ͳ�ƽ��
	Record* result = new Record[count_of_kinds];
	for (int jj = 0; jj < count_of_kinds; jj++)
	{
		result[jj] = Records[jj];
		result[jj].weight_divide(txt_length);
	}
	//������������������
	Huffman_tree result_tree(result, count_of_kinds);
	return result_tree;
}

//��Huffman������ָ����txt�ļ��������encode_result.txt
void encode_out_test(Huffman_tree& test_Huffman_tree)
{
	//�����ַ���
	int max_characters = MAX_characters;			//�������ַ���
	ifstream dataIn;
	ofstream dataOut;
	char* content = new char[max_characters + 1];	//�����洢�������ݣ�����һ�����ַ���Ϊ��β
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//��ʼ��Ϊ���ַ�
	string filename;	//�ļ���
	cout << "������Ҫ�򿪵�txt�ļ�����";
	cin >> filename;
	dataIn.open(filename.c_str());	//���ļ�
	if (dataIn.is_open())	//����򿪳ɹ�
	{
		cout << "�򿪳ɹ������ڶ�ȡ..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//�����ʧ��
		cout << "\n��ʧ��" << endl;
	dataIn.close();			//�ر��ļ�
	//����
	string txt_content = content;
	string result = test_Huffman_tree.encode(txt_content);
	//���
	dataOut.open("encode_result.txt");
	dataOut << result;
	dataOut.close();
}

//��Huffman������encode_result.txt�������decode_result.txt
void decode_out_test(Huffman_tree& test_Huffman_tree)
{
	//�����ַ���
	int max_characters = MAX_characters;			//�������ַ���
	ifstream dataIn;
	ofstream dataOut;
	char* content = new char[max_characters + 1];	//�����洢�������ݣ�����һ�����ַ���Ϊ��β
	for (int i = 0; i < max_characters + 1; i++)content[i] = '\0';	//��ʼ��Ϊ���ַ�
	dataIn.open("encode_result.txt");	//���ļ�
	if (dataIn.is_open())	//����򿪳ɹ�
	{
		cout << "�򿪳ɹ������ڶ�ȡ..." << endl;
		dataIn.getline(content, max_characters);
	}
	else					//�����ʧ��
		cout << "\n��ʧ��" << endl;
	dataIn.close();			//�ر��ļ�
	//����
	string txt_content = content;
	string result = test_Huffman_tree.decode(txt_content);
	//���
	dataOut.open("decode_result.txt");
	dataOut << result;
	dataOut.close();
}

//��������
void help()
{
	cout << endl
		<< "�ó��������û�ÿ������һ����ĸ�������һ����\n"
		<< "��Ч���������\n"
		<< "W-�õ�ǰ������ָ����txt�ļ��������encode_result.txt\n"
		<< "w-����encode_result.txt���õ�ǰ�����뵽decode_result.txt\n"
		<< "X-��ʾ��ǰ������������\n"
		<< "E-��������������ַ���������ABFDEFGH���ɣ�����\n"
		<< "D-������������ı�����������01���ɣ�����\n"
		<< "H-��ʾ������\n"
		<< "Q-�˳�\n"
		<< "��һ�� <Enter> �Լ���" << flush;
	char c;
	do { cin.get(c); } while (c != '\n');
}
//��������
char get_command()
{
	char command;
	bool waiting = true;
	cout << "\n��������� <Enter>:";
	while (waiting)
	{
		cin.get(command);
		if (command == 'W' || command == 'w' || command == 'X' ||
			command == 'E' || command == 'D' || command == 'H' ||
			command == 'Q')
			waiting = false;
		else
			cout << "��������Ч����: ";
	}
	while ((getchar()) != '\n');	//���ն�������
	return command;
}
//ִ������
bool do_command(char c, Huffman_tree& test_Huffman_tree)
{
	bool continue_input = true;
	switch (c)
	{
	case'W':
	{
		encode_out_test(test_Huffman_tree);
		cout << "�������" << endl;
		cin.get();		//���ջس�
		break;
	}
	case'w':
	{
		decode_out_test(test_Huffman_tree);
		cout << "�������" << endl;
		break;
	}
	case 'X':
		test_Huffman_tree.Huffman_display();
		break;
	case 'E':
	{
		string chars;
		cout << "������Ҫ������ַ�����";
		cin >> chars;
		cin.get();		//���ջس�
		cout << "��������" << test_Huffman_tree.encode(chars) << endl;
		break;
	}
	case 'D':
	{
		string bits;
		cout << "������Ҫ����ı�������";
		cin >> bits;
		cin.get();		//���ջس�
		cout << "��������" << test_Huffman_tree.decode(bits) << endl;
		break;
	}
	case 'H':
		help();
		break;
	case 'Q':
		cout << "���Խ���" << endl;
		continue_input = false;
		break;
	}
	return continue_input;
}

int main()
{
	//�������
	cout << "��ʼ����...\n";
	//����txt�ļ�������Huffman��
	Huffman_tree test_Huffman_tree = read_txt();
	//ָ�����
	help();
	while (do_command(get_command(), test_Huffman_tree)) {}
	return 0;
}