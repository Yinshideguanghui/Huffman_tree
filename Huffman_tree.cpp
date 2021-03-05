#include"Huffman_tree.h"

//从一组结点构造哈夫曼树
Huffman_tree::Huffman_tree(Record records[], int n)
{
	int count_of_trees = n;					//记录当前森林中树数目
	List<Binary_node<Record>> forest;		//森林
	for (int i = 0; i < n; i++)				//初始化森林为单个record树的森林
	{
		Binary_node<Record> temp_node(records[i]);
		forest.insert(0, temp_node);
	}
	//生成哈夫曼树
	while (forest.size() > 1)
	{
		Binary_node<Record> search_temp;
		//找到根节点权重最小的树
		Binary_node<Record> weight_1st_least;
		int pos_1st_least = 0;
		forest.retrieve(pos_1st_least, weight_1st_least);
		for (int k = 1; k < forest.size(); k++)
		{
			forest.retrieve(k, search_temp);
			if (weight_1st_least.data.retrieve_weight() > search_temp.data.retrieve_weight())
			{
				forest.retrieve(k, weight_1st_least);
				pos_1st_least = k;
			}
		}
		//找到根节点权重第二小的树
		double least_weight = weight_1st_least.data.retrieve_weight();
		Binary_node<Record> weight_2nd_least;
		int pos_2nd_least = 0;
		forest.retrieve(pos_2nd_least, weight_2nd_least);
		for (int k = 1; k < forest.size(); k++)
		{
			forest.retrieve(k, search_temp);
			double temp_weight = search_temp.data.retrieve_weight();
			double least_weight_2nd = weight_2nd_least.data.retrieve_weight();
			//(最小<当前<=暂定第二小)或者(最小==当前的同时二者位置不同) 时暂定第二小更新
			if (((least_weight < temp_weight) && (temp_weight <= least_weight_2nd))
				|| ((least_weight == temp_weight) && (k != pos_1st_least)))
			{
				forest.retrieve(k, weight_2nd_least);
				pos_2nd_least = k;
			}
		}
		double least_weight_2nd = weight_2nd_least.data.retrieve_weight();
		//新建二叉结点(左边连权重第一小的树,右边连权重第二小的树)
		Binary_node<Record>* node_copy_temp_1 = new Binary_node<Record>(weight_1st_least);
		Binary_node<Record>* node_copy_temp_2 = new Binary_node<Record>(weight_2nd_least);
		Record create_temp_record('\0', least_weight + least_weight_2nd);
		Binary_node<Record> create_temp_node(create_temp_record, node_copy_temp_1, node_copy_temp_2);
		//之前根权重最小的两结点出表(先出排在后面的一个以防止先出了前面的之后后面的位置信息失效)
		if (pos_2nd_least > pos_1st_least)
		{
			forest.remove(pos_2nd_least, search_temp);
			forest.remove(pos_1st_least, search_temp);
		}
		else
		{
			forest.remove(pos_1st_least, search_temp);
			forest.remove(pos_2nd_least, search_temp);
		}
		//新建结点入表
		forest.insert(0, create_temp_node);
		//森林中树数目减少1
		//count_of_trees -= 1;
	}
	//最后剩下的即为哈夫曼树的根节点
	Binary_node<Record> temp_root;
	forest.retrieve(0, temp_root);
	Binary_tree<Record>::root = temp_root.recursive_copy(&temp_root);
	//递归赋予码
	recursive_set_bits(Binary_tree<Record>::root);
}

//显示当前编码规则
void Huffman_tree::Huffman_display()
{
	recursive_Huffman_display(Binary_tree<Record>::root);
}
//递归显示当前编码规则的辅助函数
void Huffman_tree::recursive_Huffman_display(const Binary_node<Record>* sub_node)
{
	if (sub_node != NULL)
	{
		if (sub_node->left == NULL && sub_node->right == NULL)
		{
			cout << "Character: " << sub_node->data.retrieve_item()
				<< "  Bits: " << sub_node->data.retrieve_bits() << endl;
		}
		else
		{
			recursive_Huffman_display(sub_node->left);
			recursive_Huffman_display(sub_node->right);
		}
	}
}

//编码
string Huffman_tree::encode(string chars)
{
	string result_bits;
	bool expected = 1;		//当前字符是否在编码规则范围内
	for (unsigned int i = 0; i < chars.length(); i++)	//对结束符前的每一个字符编码
		if (chars[i] != '\0')
		{
			expected = 0;
			recursive_encode_per_node(Binary_tree<Record>::root, chars[i], result_bits, expected);
			if (!expected)	//不在编码规则范围内时显示提示信息但继续编码
				cout << "Unexpected character: " << chars[i] << endl;
		}
	return result_bits;
}
//用于递归遍历结点并在结点判断是否编码的辅助函数
void Huffman_tree::recursive_encode_per_node(const Binary_node<Record>* sub_node, char this_char, string& result_bits, bool& expected)
{
	if (sub_node != NULL)
	{
		if (sub_node->data.retrieve_item() == this_char)
		{
			expected = 1;
			result_bits += sub_node->data.retrieve_bits();
		}
		else
		{
			recursive_encode_per_node(sub_node->left, this_char, result_bits, expected);
			recursive_encode_per_node(sub_node->right, this_char, result_bits, expected);
		}
	}
}

//译码
string Huffman_tree::decode(string bits)
{
	unsigned int pos = 0;	//当前读到输入比特流bits的哪一位
	bool last_ = 1;			//最后一个比特是否是冗余的
	Binary_node<Record>* current_node = Binary_tree<Record>::root;	//当前到达结点
	string result_chars;	//储存译码结果
	for (pos = 0; pos < bits.length(); pos++)	//开始译码
	{
		last_ = 1;
		if (bits[pos] == '0')		//遇到0看左边
		{
			if (current_node->left != NULL)
			{
				//遇到叶子结点则输出字符到译码结果并且指针回到根节点,且最后一个比特不是冗余的
				if (current_node->left->left == NULL && current_node->left->right == NULL)
				{
					result_chars += current_node->left->data.retrieve_item();
					current_node = Binary_tree<Record>::root;
					last_ = 0;
					continue;
				}
				//遇到非叶子结点则指针向左前进
				else
				{
					current_node = current_node->left;
					continue;
				}
			}
		}
		else if (bits[pos] == '1')	//遇到1看右边
		{
			if (current_node->right != NULL)
			{
				//遇到叶子结点则输出字符到译码结果并且指针回到根节点,且最后一个比特不是冗余的
				if (current_node->right->left == NULL && current_node->right->right == NULL)
				{
					result_chars += current_node->right->data.retrieve_item();
					current_node = Binary_tree<Record>::root;
					last_ = 0;
					continue;
				}
				//遇到非叶子结点则指针向右前进
				else
				{
					current_node = current_node->right;
					continue;
				}
			}
		}
		else						//出现非0非1显示警告并不再译码
		{
			cout << "Unexpected bit: " << bits[pos] << ", invalid decoding.";
			return "\0";
		}
	}
	//最后有冗余比特时输出提示信息
	if (last_)cout << "Redundant bit(s) detected." << endl;
	return result_chars;
}

//用递归方法赋予哈夫曼树叶子结点编码的辅助函数(向左加0向右加1)
void Huffman_tree::recursive_set_bits(Binary_node<Record>* current_node)
{
	if (current_node != NULL)
	{
		if (current_node->left != NULL)
		{
			current_node->left->data.set_bits((current_node->data.retrieve_bits()) + "0");
			recursive_set_bits(current_node->left);
		}
		if (current_node->right != NULL)
		{
			current_node->right->data.set_bits((current_node->data.retrieve_bits()) + "1");
			recursive_set_bits(current_node->right);
		}
	}
}