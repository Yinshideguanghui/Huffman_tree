#include<iostream>
#include<iomanip>
#include"Binary_tree_linked.h"

template<class Entry>		//是否为空
bool Binary_tree<Entry>::empty() const
{
	return root == NULL;
}

template<class Entry>		//中序遍历LVR
void Binary_tree<Entry>::inorder(void(*visit)(Entry&))
{
	recursive_inorder(root, visit);
}
template<class Entry>		//递归中序遍历LVR辅助函数
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>* sub_root, void(*visit)(Entry&))
{
	if (sub_root != NULL)
	{
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}

template<class Entry>		//前序遍历VLR
void Binary_tree<Entry>::preorder(void(*visit)(Entry&))
{
	recursive_preorder(root, visit);
}
template<class Entry>		//递归前序遍历VLR辅助函数
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry>* sub_root, void(*visit)(Entry&))
{
	if (sub_root != NULL)
	{
		(*visit)(sub_root->data);
		recursive_preorder(sub_root->left, visit);
		recursive_preorder(sub_root->right, visit);
	}
}

template<class Entry>		//后序遍历LRV
void Binary_tree<Entry>::postorder(void(*visit)(Entry&))
{
	recursive_postorder(root, visit);
}
template<class Entry>		//递归后序遍历LRV辅助函数
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry>* sub_root, void(*visit)(Entry&))
{
	if (sub_root != NULL)
	{
		recursive_postorder(sub_root->left, visit);
		recursive_postorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}

template<class Entry>		//当前结点个数
int Binary_tree<Entry>::size() const
{
	return recursive_size(root);
}
template<class Entry>		//递归求结点个数辅助函数
int Binary_tree<Entry>::recursive_size(Binary_node<Entry>* sub_root) const
{
	if (sub_root == NULL) return 0;
	else return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template<class Entry>		//当前高度
int Binary_tree<Entry>::height() const
{
	return recursive_height(root);
}
template<class Entry>		//递归求高度辅助函数
int Binary_tree<Entry>::recursive_height(Binary_node<Entry>* sub_root) const
{
	if (sub_root == NULL) return 0;
	else
	{
		int left_height = recursive_height(sub_root->left);
		int right_height = recursive_height(sub_root->right);
		if (left_height >= right_height) return 1 + left_height;
		else return 1 + right_height;
	}
}

template<class Entry>		//清空
void Binary_tree<Entry>::clear()
{
	recursive_clear(root);
	root = NULL;
}
template<class Entry>		//清空递归辅助函数
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry>*& sub_root)
{
	if (sub_root != NULL)
	{
		recursive_clear(sub_root->left);
		recursive_clear(sub_root->right);
		delete sub_root;
	}
}

template<class Entry>		//插入，到矮的一边(一样高插入到左边)
void Binary_tree<Entry>::insert(const Entry& x)
{
	recursive_insert(root, x);
}
template<class Entry>		//插入递归辅助函数，到矮的一边(一样高插入到左边)
void Binary_tree<Entry>::recursive_insert(Binary_node<Entry>*& sub_root, const Entry& x)
{
	if (sub_root == NULL)sub_root = new Binary_node<Entry>(x);
	else
	{
		int left_height = recursive_height(sub_root->left);
		int right_height = recursive_height(sub_root->right);
		if (left_height <= right_height) recursive_insert(sub_root->left, x);
		else recursive_insert(sub_root->right, x);
	}
}

template<class Entry>		//复制构造函数
Binary_tree<Entry>::Binary_tree(const Binary_tree<Entry>& original)
{
	root = recursive_copy(original.root);
}
template<class Entry>		//复制构造函数递归辅助函数
Binary_node<Entry>* Binary_tree<Entry>::recursive_copy(const Binary_node<Entry>* sub_root)
{
	if (sub_root == NULL) return NULL;
	else
	{
		Binary_node<Entry>* copy_temp = new Binary_node<Entry>(sub_root->data);
		copy_temp->left = recursive_copy(sub_root->left);
		copy_temp->right = recursive_copy(sub_root->right);
		return copy_temp;
	}
}

template<class Entry>		//重载赋值运算符
Binary_tree<Entry>& Binary_tree<Entry>::operator=(const Binary_tree<Entry>& original)
{
	Binary_tree<Entry> new_copy(original);
	return new_copy;
}