#pragma once
#include "node.hpp"

class List {
private:
	int check_repeat(Node*, List);
	Node* previous(int, Node*);
	void print_category_menu();
	void print_function_menu();
	void category_dept(List, int);
	void category_gender(List, int);
	void category_dept_gender(List, int);

public:
	int count, dept_cnt; 
	std::string dept[9];
	Node* head;

	void menu();
	void add_student(List*);
	void delete_student(List*);
	void print_student(List);
	void pivot(List);
	void del_node(List*); 
};