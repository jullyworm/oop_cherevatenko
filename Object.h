#include <string>
#include <iostream>
#include "Container.h"


class Object {
public:
	virtual std::string toString() const = 0;
	Object() = default;
	~Object() = default;
	Object(const Object& other) { ++m_counter; }
protected:
	static uint32_t m_counter;
};

class Task : public Object {
public:
	virtual void execute() = 0;
	virtual bool hasResult() const = 0;
	Task() {
		m_completed = false;
		++m_counter;
	}
	~Task(){
		--m_counter;
	}
protected:
	bool m_completed;
};

class Named : public Object {
protected:
	std::string m_name;
};

class ArithmeticTask : public Task, public Named {
public:
	ArithmeticTask(int a, int b, char c, std::string name) : m_a(a), m_b(b), m_c(c)
	{
		m_name = name;
		m_result = 0;
	}

	bool hasResult() const {
		return true;
	}

	void execute() {
		try {
			switch (m_c) {
			case '+':
				m_result = m_a + m_b;
				m_completed = true;
				break;
			case '-':
				m_result = m_a - m_b;
				m_completed = true;
				break;
			case '*':
				m_result = m_a * m_b;
				m_completed = true;
				break;
			case '/':
				if (m_b == 0) throw "на 0 делить нельзя";
				m_result = m_a;
				m_result /= m_b;
				m_completed = true;

				break;
			default:
				throw "знак не +-*/, меняйте";
				break;
			}
		}
		catch (const char* err) {
			std::cout << err << std::endl;
		}
	}

	double getResult() {
		return m_result;
	}

	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача " + m_name + " не выполнена, будет решено арифметическое выражение : " + std::to_string(m_a) + " " + m_c + " " + std::to_string(m_b);
			return res;
		}
		else {
			std::string res = "Арифметическая задача " + m_name +  " выполнена, было решено: "	+ std::to_string(m_a)	+ " " + m_c + " " + std::to_string(m_b) + " = " + std::to_string(m_result);
			return res;
		};
	}
private:
	double m_result;
	int m_a, m_b;
	char m_c;
};

class AddTask : public Task {
public:
	AddTask(Task* other_task, Container<Task*> &other_cont) : m_task(other_task), m_cont(other_cont) {}

	bool hasResult() const {
		return false;
	}

	void execute() {
		m_cont.push_back(m_task);
		m_completed = true;
	}

	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача не выполнена, будет добавлена указанная задача в контейнер";
			return res;
		}
		else {
			std::string res = "Задача добавления выполнена, была добавлена указанная задача в контейнер";
			return res;
		};
	}
private:
	Container<Task*>& m_cont;
	Task* m_task;
};

class CounterTask : public Task {
public:
	CounterTask(Container<Task*> const &other_cont) : m_count(0), m_cont(other_cont) {}

	bool hasResult() const {
		return true;
	}

	void execute() {
		m_count = m_cont.size();
		m_completed = true;
	}

	double getResult() {
		return m_count;
	}

	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача не выполнена, будет посчитано количество объектов в контейнере";
			return res;
		}
		else {
			std::string res = "Задача посчета количество объектов в контейнере выполнена, в контейнере находится " + std::to_string(m_count) + " объектов";
			return res;
		};
	}
private:
	Container<Task*> const & m_cont;
	uint32_t m_count;
};

class CounterResultTask : public Task {
public:
	CounterResultTask(Container<Task*>  &other_cont) : m_count(0), m_cont(other_cont) {}

	bool hasResult() const {
		return true;
	}

	void execute() {
		for (Container<Task*>::Iterator i = m_cont.begin(); i != m_cont.end(); i++) {
			if (i.get_node()->data->hasResult()) ++m_count;
		}
		m_completed = true;
	}

	double getResult() {
		return m_count;
	}
	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача не выполнена, будет посчитано количество задач с результатом в контейнере";
			return res;
		}
		else {
			std::string res = "Задача подсчета задач с результатом в конейнере выполнена, в контейнере находится " + std::to_string(m_count) + " задач с результатом";
			return res;
		};
	}

private:
	Container<Task*> & m_cont;
	uint32_t m_count;
};

class ClearContainer : public Task {
	ClearContainer(Container <Task*>& other_cont) : m_cont(other_cont) {}

	bool hasResult() const {
		return false;
	}

	void execute() {
		m_cont.clear();
		m_completed = true;
	}

	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача очистки не выполнена, будет очищен контейнер";
			return res;
		}
		else {
			std::string res = "Задача очистки выполнена, контейнер очищен";
			return res;
		};
	}
private:
	Container<Task*> & m_cont;
};

class CounterObject : public Task {
public:
	CounterObject() : m_count(0) {};

	bool hasResult() const {
		return true;
	}

	void execute() {
		m_count = m_counter;
		m_completed = true;
	}

	double getResult() {
		return m_count;
	}

	std::string toString() const {
		if (!m_completed) {
			std::string res = "Задача подсчета объектов не выполнена, будет посчитано количество объектов вообще";
			return res;
		}
		else {
			std::string res = "Задача подсчета объектов выполнена, существует " + std::to_string(m_count) + " объектов";
			return res;
		};
	}
private:
	uint32_t m_count;
};

