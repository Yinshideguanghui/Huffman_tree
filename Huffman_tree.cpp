#include"Huffman_tree.h"

//��һ���㹹���������
Huffman_tree::Huffman_tree(Record records[], int n)
{
	int count_of_trees = n;					//��¼��ǰɭ��������Ŀ
	List<Binary_node<Record>> forest;		//ɭ��
	for (int i = 0; i < n; i++)				//��ʼ��ɭ��Ϊ����record����ɭ��
	{
		Binary_node<Record> temp_node(records[i]);
		forest.insert(0, temp_node);
	}
	//���ɹ�������
	while (forest.size() > 1)
	{
		Binary_node<Record> search_temp;
		//�ҵ����ڵ�Ȩ����С����
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
		//�ҵ����ڵ�Ȩ�صڶ�С����
		double least_weight = weight_1st_least.data.retrieve_weight();
		Binary_node<Record> weight_2nd_least;
		int pos_2nd_least = 0;
		forest.retrieve(pos_2nd_least, weight_2nd_least);
		for (int k = 1; k < forest.size(); k++)
		{
			forest.retrieve(k, search_temp);
			double temp_weight = search_temp.data.retrieve_weight();
			double least_weight_2nd = weight_2nd_least.data.retrieve_weight();
			//(��С<��ǰ<=�ݶ��ڶ�С)����(��С==��ǰ��ͬʱ����λ�ò�ͬ) ʱ�ݶ��ڶ�С����
			if (((least_weight < temp_weight) && (temp_weight <= least_weight_2nd))
				|| ((least_weight == temp_weight) && (k != pos_1st_least)))
			{
				forest.retrieve(k, weight_2nd_least);
				pos_2nd_least = k;
			}
		}
		double least_weight_2nd = weight_2nd_least.data.retrieve_weight();
		//�½�������(�����Ȩ�ص�һС����,�ұ���Ȩ�صڶ�С����)
		Binary_node<Record>* node_copy_temp_1 = new Binary_node<Record>(weight_1st_least);
		Binary_node<Record>* node_copy_temp_2 = new Binary_node<Record>(weight_2nd_least);
		Record create_temp_record('\0', least_weight + least_weight_2nd);
		Binary_node<Record> create_temp_node(create_temp_record, node_copy_temp_1, node_copy_temp_2);
		//֮ǰ��Ȩ����С����������(�ȳ����ں����һ���Է�ֹ�ȳ���ǰ���֮������λ����ϢʧЧ)
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
		//�½�������
		forest.insert(0, create_temp_node);
		//ɭ��������Ŀ����1
		//count_of_trees -= 1;
	}
	//���ʣ�µļ�Ϊ���������ĸ��ڵ�
	Binary_node<Record> temp_root;
	forest.retrieve(0, temp_root);
	Binary_tree<Record>::root = temp_root.recursive_copy(&temp_root);
	//�ݹ鸳����
	recursive_set_bits(Binary_tree<Record>::root);
}

//��ʾ��ǰ�������
void Huffman_tree::Huffman_display()
{
	recursive_Huffman_display(Binary_tree<Record>::root);
}
//�ݹ���ʾ��ǰ�������ĸ�������
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

//����
string Huffman_tree::encode(string chars)
{
	string result_bits;
	bool expected = 1;		//��ǰ�ַ��Ƿ��ڱ������Χ��
	for (unsigned int i = 0; i < chars.length(); i++)	//�Խ�����ǰ��ÿһ���ַ�����
		if (chars[i] != '\0')
		{
			expected = 0;
			recursive_encode_per_node(Binary_tree<Record>::root, chars[i], result_bits, expected);
			if (!expected)	//���ڱ������Χ��ʱ��ʾ��ʾ��Ϣ����������
				cout << "Unexpected character: " << chars[i] << endl;
		}
	return result_bits;
}
//���ڵݹ������㲢�ڽ���ж��Ƿ����ĸ�������
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

//����
string Huffman_tree::decode(string bits)
{
	unsigned int pos = 0;	//��ǰ�������������bits����һλ
	bool last_ = 1;			//���һ�������Ƿ��������
	Binary_node<Record>* current_node = Binary_tree<Record>::root;	//��ǰ������
	string result_chars;	//����������
	for (pos = 0; pos < bits.length(); pos++)	//��ʼ����
	{
		last_ = 1;
		if (bits[pos] == '0')		//����0�����
		{
			if (current_node->left != NULL)
			{
				//����Ҷ�ӽ��������ַ�������������ָ��ص����ڵ�,�����һ�����ز��������
				if (current_node->left->left == NULL && current_node->left->right == NULL)
				{
					result_chars += current_node->left->data.retrieve_item();
					current_node = Binary_tree<Record>::root;
					last_ = 0;
					continue;
				}
				//������Ҷ�ӽ����ָ������ǰ��
				else
				{
					current_node = current_node->left;
					continue;
				}
			}
		}
		else if (bits[pos] == '1')	//����1���ұ�
		{
			if (current_node->right != NULL)
			{
				//����Ҷ�ӽ��������ַ�������������ָ��ص����ڵ�,�����һ�����ز��������
				if (current_node->right->left == NULL && current_node->right->right == NULL)
				{
					result_chars += current_node->right->data.retrieve_item();
					current_node = Binary_tree<Record>::root;
					last_ = 0;
					continue;
				}
				//������Ҷ�ӽ����ָ������ǰ��
				else
				{
					current_node = current_node->right;
					continue;
				}
			}
		}
		else						//���ַ�0��1��ʾ���沢��������
		{
			cout << "Unexpected bit: " << bits[pos] << ", invalid decoding.";
			return "\0";
		}
	}
	//������������ʱ�����ʾ��Ϣ
	if (last_)cout << "Redundant bit(s) detected." << endl;
	return result_chars;
}

//�õݹ鷽�������������Ҷ�ӽ�����ĸ�������(�����0���Ҽ�1)
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