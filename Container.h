#pragma once

#include <cstdint>
#include <cstdlib>
#include <exception>

template <typename T> class Container {
private:
	//размер контейнера
	uint32_t m_size;
	//элементы контейнера
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	Node* m_head;
	Node* m_tail;
public:
	Container() {
		m_size = 0;
		m_head = NULL;
		m_tail = NULL;
	}
	Container(const Container& other) {
		m_head = NULL;
		m_tail = NULL;
		m_size = 0;

		Node* p = other.m_head;

		while (p != NULL)
		{
			push_back(p->data);
			p = p->next;
		}
	}
	~Container() {
		clear();
	}

	//добавляет элемент в начало 
	void push_front(const T& data) { //O()
		Node* p = new Node;

		p->data = data;
		p->prev = NULL;
		p->next = m_head;

		if (m_head != NULL)
			m_head->prev = p;

		if (m_size == 0) {
			m_head = p;
			m_tail = p;
		}
		else m_head = p;
		++m_size;
	}
	//добавляет элемент в конец 
	void push_back(const T& data) { //O(1)
		Node* p = new Node;

		p->data = data;
		p->prev = m_tail;
		p->next = NULL;

		if (m_tail != NULL)
			m_tail->next = p;

		if (m_size == 0) {
			m_head = p;
			m_tail = p;
		}
		else m_tail = p;
		++m_size;
	}

	//удаляет первый элемент
	void pop_front() { //O(1)
		if (m_size == 0) {
			throw std::exception("на 0 делить нельзя");
		}
		if (m_size == 1) {
			m_head = NULL;
			m_tail = NULL;
		}
		else {
			Node* p = m_head->next;
			p->prev = NULL;
			m_head = p;
			--m_size;
		}
	}
	//удаляет последний элемент
	void pop_back() { //O(1)
		if (m_size == 0) {
			throw std::exception("на 0 делить нельзя");
		}
		if (m_size == 1) {
			m_head = NULL;
			m_tail = NULL;
		}
		else {
			Node* p = m_tail->prev;
			p->next = NULL;
			m_tail = p;
			--m_size;
		}


	}

	//возвращает значение первого элемента
	T& get_front() const { //O(1)
		if (m_size == 0) {
			throw std::exception("пустой контейнер");
		}
		else return m_head->data;

	}

	//возвращает значеие последнего элемента
	T& get_back() const { //O(1)
		if (m_size == 0) {
			throw std::exception("пустой контейнер");
		}
		else return m_tail->data;
	}


	//возвращает количество элементов
	uint32_t size() const { //O(1)
		return m_size;
	}
	//возвращает true, если контейнер пуст, false, иначе
	bool is_empty() const { //O(1)
		return m_size == 0;
	}

	//меняет содержимое с другим экземпляром контейнера
	void swap(Container& other) { //O(1)
		uint32_t other_size = other.m_size;
		other.m_size = m_size;
		m_size = other_size;
		Node* p = other.m_head;
		other.m_head = m_head;
		m_head = p;
		p = other.m_tail;
		other.m_tail = m_tail;
		m_tail = p;
	}

	//переставляет все элементы в обратном порядке
	void reverse() { //O(n)
		Node* p = m_head;
		Node* prev = NULL, * next = NULL;

		while (p != NULL) {
			next = p->next;
			p->next = prev;
			prev = p;
			p = next;
		}
		m_head = prev;
	}

	//очищает контейнер
	void clear() { //O(n)
		while (m_head != NULL)
		{
			Node* p = m_head;
			m_head = m_head->next;
			delete p;
		}
		m_head = NULL;
		m_tail = NULL;
		m_size = 0;
	}

	//итератор
	class Iterator {
	public:
		Iterator(Node* p) : node(p) {};

		Iterator operator++(int) {
			if (node != NULL) node = node->next;
			return *this;
		}
		Iterator operator--(int) {
			if (node != NULL) node = node->prev;
			return *this;
		}
		Node* get_node() const {
			return  node;
		}
		bool operator==(const Iterator& other) {
			return  node == other.node;
		}
		bool operator!=(const Iterator& other) {
			return  node != other.node;
		}

	private:
		Node* node;
	};

	Iterator begin() {
		return Iterator(m_head);
	}

	Iterator end() {
		return Iterator(m_tail);
	}

};