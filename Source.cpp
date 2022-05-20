#include "Container.h"
#include "Object.h"

uint32_t Object::m_counter = 0;

Task* RANDOM(Container <Task*> &cont) {
	int n = rand() % 4;
	Task* task;
	char signs[4] = { '+', '-', '*', '/' };	
	static int index = 0;
	switch (n) {
	case 0:
			
		task = new ArithmeticTask(rand() % 20, rand() % 20, signs[rand() % 4], std::to_string(index));
		++index;
		return task;
	case 1:
		task = new CounterTask(cont);
		return task;
	case 2:
		task = new CounterResultTask(cont);
		return task;
	case 3:
		task = new CounterObject;
		return task;	
	default:
		throw "нет такого типа задач";
		break;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");

	Container <Task*> tasks;
	Container <std::string> info;
	
	Task* task1 = RANDOM(tasks);
	AddTask* add1 = new AddTask(task1, tasks);
	add1->execute();
	Task* task2 = RANDOM(tasks);
	AddTask* add2 = new AddTask(task2, tasks);
	add2->execute();
	Task* task3 = RANDOM(tasks);
	AddTask* add3 = new AddTask(task3, tasks);
	add3->execute();
	Task* task4 = RANDOM(tasks);
	AddTask* add4 = new AddTask(task4, tasks);
	add4->execute();
	Task* task5 = RANDOM(tasks);
	AddTask* add5 = new AddTask(task5, tasks);
	add5->execute();
	Task* task6 = RANDOM(tasks);
	AddTask* add6 = new AddTask(task6, tasks);
	add6->execute();
	Task* task7 = RANDOM(tasks);
	AddTask* add7 = new AddTask(task7, tasks);
	add7->execute();
	Task* task8 = RANDOM(tasks);
	AddTask* add8 = new AddTask(task8, tasks);
	add8->execute();
	Task* task9 = RANDOM(tasks);
	AddTask* add9 = new AddTask(task9, tasks);
	add9->execute();
	Task* task10 = RANDOM(tasks);
	AddTask* add10 = new AddTask(task10, tasks);
	add10->execute();
	Task* task11 = RANDOM(tasks);
	AddTask* add11 = new AddTask(task11, tasks);
	add11->execute();


	CounterObject* count_obj = new CounterObject;
	count_obj->execute();
	std::cout << count_obj->toString() << std::endl;

	std::cout << "Выполняем задачи: " << std::endl;

	for (int i = 0; i < 11; ++i) {
		tasks.get_front()->execute();
		info.push_back(tasks.get_front()->toString());
		tasks.pop_front();
	}

	for (Container<std::string>::Iterator i = info.begin(); i != info.end(); i++) {
		std::cout << i.get_node()->data << std::endl;
	}

	tasks.clear();
	info.clear();

	delete count_obj;

	delete add1;
	delete add2;
	delete add3;
	delete add4;
	delete add5;
	delete add6;
	delete add7;
	delete add8;
	delete add9;
	delete add10;
	delete add11;

	delete task1;
	delete task2;
	delete task3;
	delete task4;
	delete task5;
	delete task6;
	delete task7;
	delete task8;
	delete task9;
	delete task10;
	delete task11;

	std::cout << "Подсчет всех объектов после удаления + 1 объект, который считает: " << std::endl;
	CounterObject* count_obj2 = new CounterObject;
	count_obj2->execute();
	//должен остаться 1 объект - счетчик
	std::cout << count_obj2->toString() << std::endl;

	delete count_obj2; // теперь 0

	return 0;
}