#pragma once

#include"Binary_tree_linked.h"
#include"Binary_tree_linked.cpp"
#include"list_simply_linked_no_remembering.h"
#include"list_simply_linked_no_remembering.cpp"
using namespace std;

class Huffman_tree : public Binary_tree<Record>
{
public:
	//构造函数
	Huffman_tree() {}						//默认构造函数
	Huffman_tree(Record nodes[], int n);	//从一组结点构造哈夫曼树
	//显示当前编码规则
	void Huffman_display();
	//编码
	string encode(string chars);
	//译码
	string decode(string bits);
private:
	//递归显示当前编码规则的辅助函数
	void recursive_Huffman_display(const Binary_node<Record>* sub_node);
	//用于递归遍历结点并在结点判断是否编码的辅助函数
	void recursive_encode_per_node(const Binary_node<Record>* sub_node, char this_char, string& result_bits, bool& expected);
	//用递归方法赋予哈夫曼树叶子结点编码的辅助函数
	void recursive_set_bits(Binary_node<Record>* current_node);
};