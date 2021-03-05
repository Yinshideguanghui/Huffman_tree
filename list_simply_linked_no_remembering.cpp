#include"list_simply_linked_no_remembering.h"

template <class List_entry>				//定位
Node<List_entry>* List<List_entry>::set_position(int position)const
{
	Node<List_entry>* q = head;
	for (int i = 0; i < position; i++)q = q->next;
	return q;
}

template <class List_entry>				//复制构造函数
List<List_entry>::List(const List<List_entry>& copy)
{
	clear();
	if (copy.empty()) { head = NULL; }
	else
	{
		Node<List_entry>* copy_ptr, * new_copy_ptr;
		copy_ptr = copy.head;
		new_copy_ptr = new Node<List_entry>(copy_ptr->entry);
		head = new_copy_ptr;
		count = 1;
		while (copy_ptr->next != NULL)
		{
			copy_ptr = copy_ptr->next;
			new_copy_ptr->next = new Node<List_entry>(copy_ptr->entry);
			new_copy_ptr = new_copy_ptr->next;
			count++;
		}
	}
}

//void operator = (const List<List_entry>& copy);

template <class List_entry>				//当前大小
int List<List_entry>::size()const
{
	return count;
}

template <class List_entry>				//是否为空
bool List<List_entry>::empty()const
{
	return count == 0;
}

template <class List_entry>				//清除
void List<List_entry>::clear()
{
	Node<List_entry>* tempptr;
	while (head->next != NULL)
	{
		tempptr = head->next;
		delete head;
		head = tempptr;
	}
	delete head;
	head = NULL;
}

template <class List_entry>				//函数遍历
void List<List_entry>::traverse(void(*visit)(List_entry&))
{
	Node<List_entry>* ptr = head;
	for (int i = 0; i < count; i++)
	{
		visit(ptr->entry);
		ptr = ptr->next;
	}
}

template <class List_entry>				//取得值
Error_code List<List_entry>::retrieve(int position, List_entry& x)const
{
	if (position < 0 || position > count) return Range_error;
	x = set_position(position)->entry;
	return success;
}

//Error_code replace(int position, const List_entry& x)

template <class List_entry>				//移出
Error_code List<List_entry>::remove(int position, List_entry& x)
{
	if (position < 0 || position > count)return Range_error;
	if (count == 0) return underflow;
	Node<List_entry>* previous, * following;
	if (position > 0)
	{
		previous = set_position(position - 1);
		following = previous->next;
		previous->next = following->next;
	}
	else
	{
		following = head;
		head = following->next;
	}
	x = following->entry;	//记录原先位置值
	delete following;
	following = NULL;
	count--;
	return success;
}

template <class List_entry>				//插入
Error_code List<List_entry>::insert(int position, const List_entry& x)
{
	if (position < 0 || position > count) return Range_error;
	Node<List_entry>* new_node, * previous = NULL, * following;
	if (position > 0)
	{
		previous = set_position(position - 1);
		following = previous->next;
	}
	else following = head;
	new_node = new Node<List_entry>(x, following);
	if (new_node == NULL)return overflow;
	if (position == 0) head = new_node;
	else previous->next = new_node;
	count++;
	return success;
}