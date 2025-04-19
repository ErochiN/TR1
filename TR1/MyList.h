#pragma once
template <typename T>
class List
{
public:
	List();
	~List();

	int GetSize();

	void push_back(T data);
	void push_head(T data);
	void push_at(const int index, T data);

	void delete_back();
	void delete_head();
	void delete_at(const int index);

	void clear();

	T& operator[](const int index);

private:
	template<typename T1>
	class Node
	{
	public:
		T1 data;
		Node* pNext;

		Node(T1 data = T1(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node<T>* head;
	int size;
};

template<typename T>
inline List<T>::List()
{
	this->head = nullptr;
	this->size = 0;
}

template<typename T>
inline List<T>::~List()
{
	this->clear();
}

template<typename T>
inline int List<T>::GetSize()
{
	return this->size;
}

template<typename T>
inline void List<T>::push_back(T data)
{
	if (this->head == nullptr)
		this->head = new Node<T>(data);
	else
	{
		Node<T>* cur = this->head;

		while (cur->pNext != nullptr)
			cur = cur->pNext;

		cur->pNext = new Node<T>(data);
	}
	++size;
}

template<typename T>
inline void List<T>::push_head(T data)
{
	if (this->head == nullptr)
		this->head = new Node<T>(data);
	else
		this->head = new Node<T>(data, this->head);
	++size;
}

template<typename T>
inline void List<T>::push_at(const int index, T data)
{
	if (index > size || index < 0)
		return;

	Node<T>* cur = this->head;

	for (int i = 0; i < index - 1; i++)
		cur = cur->pNext;

	Node<T>* newNode = new Node<T>(data, cur->pNext);
	cur->pNext = newNode;

	++size;
}

template<typename T>
inline void List<T>::delete_back()
{
	Node<T>* cur = this->head;

	while (cur->pNext != nullptr)
		cur = cur->pNext;

	delete cur;
	cur = nullptr;

	--size;
}

template<typename T>
inline void List<T>::delete_head()
{
	Node<T>* temp = this->head;

	this->head = this->head->pNext;

	delete temp;
	temp = nullptr;

	--size;
}

template<typename T>
inline void List<T>::delete_at(const int index)
{
	if (index > size || index < 0)
		return;

	Node<T>* cur = this->head;

	for (int i = 0; i < index - 1; i++)
		cur = cur->pNext;

	Node<T>* temp = cur->pNext;
	cur->pNext = temp->pNext;

	delete temp;
	temp = nullptr;

	--size;
}

template<typename T>
inline void List<T>::clear()
{
	while (this->size)
		this->delete_head();
}

template<typename T>
inline T& List<T>::operator[](const int index)
{
	Node<T>* cur = this->head;

	for (int i = 0; i < index; i++)
		cur = cur->pNext;

	return cur->data;
}
