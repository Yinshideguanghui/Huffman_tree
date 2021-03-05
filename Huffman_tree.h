#pragma once

#include"Binary_tree_linked.h"
#include"Binary_tree_linked.cpp"
#include"list_simply_linked_no_remembering.h"
#include"list_simply_linked_no_remembering.cpp"
using namespace std;

class Huffman_tree : public Binary_tree<Record>
{
public:
	//���캯��
	Huffman_tree() {}						//Ĭ�Ϲ��캯��
	Huffman_tree(Record nodes[], int n);	//��һ���㹹���������
	//��ʾ��ǰ�������
	void Huffman_display();
	//����
	string encode(string chars);
	//����
	string decode(string bits);
private:
	//�ݹ���ʾ��ǰ�������ĸ�������
	void recursive_Huffman_display(const Binary_node<Record>* sub_node);
	//���ڵݹ������㲢�ڽ���ж��Ƿ����ĸ�������
	void recursive_encode_per_node(const Binary_node<Record>* sub_node, char this_char, string& result_bits, bool& expected);
	//�õݹ鷽�������������Ҷ�ӽ�����ĸ�������
	void recursive_set_bits(Binary_node<Record>* current_node);
};