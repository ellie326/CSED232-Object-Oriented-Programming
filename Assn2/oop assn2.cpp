#include <iostream>
#include <string>
#include <cmath>
#include "list.hpp"

using namespace std; 

int main() {
	List s_list;					//initializaiton 
	s_list.count = 0;
	s_list.dept_cnt = 0;
	s_list.head = NULL;

	int choice = 0; 
	
	while (true) {
		s_list.menu();
		cout << "Selection: "; 
		cin >> choice;
		if (choice == 1) {												//add student
			s_list.add_student(&s_list);
			
		}
		else if (choice == 2) {											//delete student 
			s_list.delete_student(&s_list);
			
		}
		else if (choice == 3) {											//print the student list 
			s_list.print_student(s_list);
		}
		else if (choice == 4) {											//pivot table 
			s_list.pivot(s_list);
		}
		else if (choice == 5) {											//exit 
			s_list.del_node(&s_list);
			break;
		}
		else {
			cout << "A wrong choice is entered. try again!" << endl;
			continue;
		}
	}
	return 0; 
}

void List::menu() {
	cout << "---------------MENU---------------" << endl;
	cout << "1. Add a student" << endl;
	cout << "2. Delete a student" << endl;
	cout << "3. Print the student's list" << endl;
	cout << "4. Pivot table" << endl;
	cout << "5. Exit" << endl;
	cout << "----------------------------------" << endl;
	return;
}

void student::input_info(bool *exception) {						//exception boolean variable will check the correct input value 

	cout << "Dept: ";
	std::cin.ignore(); 
	std::getline(std::cin, dept); 										//input until the enter key 
	
	for (int i = 0; i < dept.length(); i++) {
		if (dept[i] == ' ') {									//if there's a space inbetween the string, delete the space 
			*exception = false;
			cout << "The input department contains spaces. Try again. " << endl;
			return;
		}
		if (int(dept[i]) < 65 || int(dept[i]) > 90) {			//if the input is in lowercase, print the error message and get the input value again. 						
			*exception = false; 
			cout << "The input department is in lowercase. Try again. " << endl; 
			return; 
		}
	}
	
	cout << "Gender: ";
	std::getline(std::cin, gender);

	for (int i = 0; i < gender.length(); i++) {
		if (gender[i] == ' ') {									//if there's a space inbetween the string, delete the space 
			*exception = false;
			cout << "The input gender contains spaces. Try again. " << endl;
			return;
		}
	}
	
	if (gender.compare("M") != 0 && gender.compare("F") != 0) {			//if the input is in lowercase, print the error message and get the input value again. 						
		*exception = false;
		cout << "The input gender is neither M nor F. Try again." << endl;
		return;
	}
	
	cout << "Name: ";
	std::getline(std::cin, name); 

	for (int i = 0; i < name.length(); i++) {
		if (name[i] == ' ') {
			*exception = false;
			cout << "The input name contains a space! Try again without any spaces" << endl; 
			return; 
		}
	}
	
	cout << "Age: ";
	cin >> age;
	if (age < 18 || age > 30) {											// if the age is less than 18 / more than 30, error 
		*exception = false;
		cout << "The input age is not in the range of 18 ~ 30. Try again." << endl;
		return; 
	}
	cout << endl; 
	return;
}

void List::add_student(List* s_list) {									//this will add student and sort at the same time 
	bool exception = true;												//this variable will check for the exceptions  

	student input_student;	
	input_student.input_info(&exception);								//this function will save the input values  
	
	while (exception) {													//no error found in the input. 

		Node* new_node = new Node;										//dynamically allocate the new student for linked list 
		new_node->data = input_student;									//this may be unnecessary bc the compiler has default constructor 
		int check_new_dept = 0;

		if (s_list->count == 0) {										//if there exist no other student in the list 
			s_list->head = new_node;
			s_list->count++;
			s_list->dept[s_list->dept_cnt] = new_node->data.dept;
			s_list->dept_cnt++;
			cout << "A student is added in table!" << endl;
			return;
		}
				
		Node* walker = s_list->head;												//walker will used to check whether the new student should be before/after the current checking node
		Node* prev = s_list->head;													//prev directs the node before the walker 
		int prev_num = 0;															//prev num counts the number of walker passed along the list 

		if (check_repeat(new_node, *s_list)) {										//check_repeat function checks whether the student already exists in the list or not 
																					//return 0 if the student exsists 
			for (int cnt = 0; cnt < s_list->count; cnt++) {
				if (new_node->data.dept.compare(walker->data.dept) == 0) {			//check the dept first, and if the dept already exists, change the value of check_new_dept to 1
					check_new_dept = 1;
					break;
				}
				if (walker->next != NULL) {											//checks the whole list until the last node. 
					walker = walker->next;
					prev_num++;
				}

			}

			while (check_new_dept && new_node->data.dept.compare(walker->data.dept) == 0 && walker != NULL){		//when same dept. 
				
				if (new_node->data.gender.compare(walker->data.gender) < 0){		//when the new node should come before the walker 

					if (prev_num == 0) {											//when the new node should be added before the current head node 
						new_node->next = s_list->head;
						s_list->head = new_node;
						s_list->count++;
						cout << "A student is added in table!" << endl;
						return;
					}
					walker = previous(prev_num, prev);									//when the new node should be added before the walker node, move walker node one node before it. 
					break;																//so that the new node can be added before the walker node 
				}
				else if (new_node->data.gender.compare(walker->data.gender) == 0 &&		//this is when the gender is the same, and name is different. 
					new_node->data.name.compare(walker->data.name) < 0){				//But the new node should go before the walker node 
					
					if (prev_num == 0) {												//when the new node should be added before the current head node 
						new_node->next = walker;
						s_list->head = new_node;
						s_list->count++;
						cout << "A student is added in table!" << endl;
						return;
					}
					walker = previous(prev_num, prev);									//when the new node should be added before the walker node, move walker node one node before it. 
					break;
				}
				else if (new_node->data.gender.compare(walker->data.gender) == 0 &&		//this is when the gender and name is the same, and age is different. 
					new_node->data.name.compare(walker->data.name) == 0 &&
					new_node->data.age < walker->data.age)
				{
					if (prev_num == 0) {												//when the new node should be added before the current head node 
						new_node->next = s_list->head;
						s_list->head = new_node;
						s_list->count++;
						cout << "A student is added in table!" << endl;
						return;
					}
					walker = previous(prev_num, prev);									//when the new node should be added before the walker node, move walker node one node before it. 
					break;
				}
				if (walker->next == NULL)												//when the walker is the last node and the new node should be added to the tail of the list 
				{
					walker->next = new_node;							
					new_node->next = NULL;
					s_list->count++;
					cout << "A student is added in table!" << endl;
					return;
				}

				walker = walker->next;													//move walker through the list and sort the new node 
				prev_num++;
			}
																						//if new dept should be added 
			if (!check_new_dept) {
				if (s_list->dept_cnt >= 9) {																															
					cout << "there is already 9 dept exists in the list" << endl;
					return;
				}

				walker = s_list->head;													//initialize the walker and prev_num because from the for loop in like 118, 
				prev_num = 0;															//the walker already moved through the list and directs the end of the list 
				
			
				s_list->dept[s_list->dept_cnt] = new_node->data.dept;					//add the new dept to the string array in s_list 
				s_list->dept_cnt++;
				
				while (walker != NULL && new_node->data.dept.compare(walker->data.dept) > 0) {		//find the place where the new node should be added 
					walker = walker->next;															//the new node should be added before the walker unless the new node should be added to the tail of the list 
					prev_num++;
				}
				if (prev_num == 0) {																//when new node should be added before the head node 
					new_node->next = s_list->head;
					s_list->head = new_node;
					s_list->count++;
					cout << "A student is added in table!" << endl;
					return;
				}
			}
			if (walker == NULL) {																	//when the new node should be added to the tail of the list 									
				walker = previous(prev_num, prev);
				walker->next = new_node;
			}
			else {																					//move the walker one node before using previous function 
				walker = previous(prev_num, prev);
				new_node->next = walker->next;
				walker->next = new_node;
			}

			s_list->count++;																		//student with new dept is added so increase the number of student (s_list->count) 

			cout << "A student is added in table!" << endl;
			return;
		}
		else {																						//when check_repeat = 1, meaning the student already exists in the list 
			cout << "duplicate it" << endl << "The student already exists." << endl;
			return;
		}
	}
	return; 
}

Node* List::previous(int prev_num, Node* prev) {													//prev pointer will direct a node right before the node directed by walker 
	for (int i = 0; i < prev_num - 1; i++) {
		prev = prev->next;
	}
	return prev;
}

int List::check_repeat(Node* new_node, List s_list) {								//return 0 if the student already exists  

	Node* walker = s_list.head;

	for (int i = 0; i < s_list.count; i++) {										
		if (new_node->data.dept.compare(walker->data.dept) == 0 &&
			new_node->data.name.compare(walker->data.name) == 0 &&
			new_node->data.gender.compare(walker->data.gender) == 0 &&
			new_node->data.age == walker->data.age)									//when the info of new student matches that of student in the list 
		{

			return 0;
		}
		else {
			walker = walker->next;
		}
	}

	return 1;
}

void List::delete_student(List* s_list) {
	bool exception = true; 

	if (s_list->head == NULL) {
		cout << "student doesn't exists in the list. Try again. " << endl; 
		return; 
	}

	student delete_student;
	delete_student.input_info(&exception);

	while (exception) {																			//exception is true unless the input info is not in the range 
		Node temp;
		temp.data = delete_student;

		Node* walker = s_list->head;															//these values mean the same thing as in add_student 
		Node* prev = s_list->head;
		int prev_num = 0;

		int num_in_dept = 0; 

		for (int i = 0; i < s_list->count; i++){

			if (walker->next != NULL && walker->data.dept.compare(walker->next->data.dept) == 0 && temp.data.dept.compare(walker->data.dept) == 0) {							//if matching student is found
				num_in_dept++;
			}

			if (temp.data.dept.compare(walker->data.dept) == 0 &&								//if matching student is found
				temp.data.name.compare(walker->data.name) == 0 &&
				temp.data.gender.compare(walker->data.gender) == 0 &&
				temp.data.age == walker->data.age){
				cout << "num: " << num_in_dept << endl;

				if (num_in_dept == 0) {				
					for (int j = 0; j < s_list->dept_cnt; j++) {
						
						if (s_list->dept[j].compare(walker->data.dept) == 0) {								//delete that department in the string array of dept in s_list 
							
							s_list->dept[j] = s_list->dept[s_list->dept_cnt - 1]; 
							s_list->dept_cnt--;
							
							break;

						} 
					}
				}
				if (prev_num == 0 && walker->next == NULL) {
					s_list->head = NULL; 
					delete walker;
					s_list->count--;

					cout << "Succefully Deleted" << endl;
					return;
				}

				if (walker->next == NULL) {
					prev = previous(prev_num, prev);
					prev->next == NULL; 
					delete walker; 
					s_list->count--;

					cout << "Succefully Deleted" << endl;
					return;
				}

				if (prev_num == 0) {												//when you need to delete the first node 

					s_list->head = walker->next;									//rearrange the list 
					walker->next = NULL;
				}
				else {
					for (int j = 0; j < prev_num - 1; j++) {						//prev directs the node before the walker node 
						prev = prev->next;
					}

					prev->next = walker->next;										// delete the walker node 
					walker->next = NULL;
				}
	
				delete walker;														//deallocation 
				s_list->count--; 

				cout << "Succefully Deleted" << endl;
				return;
			}
			walker = walker->next;
			prev_num++;
		}

		//when the entered student doesn't exists in the list 										
		cout << "Can't Delete it" << endl;
		return;
	}
	return; 
}

void List::print_student(List s) {

	if (s.head == NULL) {
		cout << "student doesn't exists in the list. Try again. " << endl;
		return;
	}

	Node* walker = s.head;

	cout << "Dept\t" << "Gender\t" << "Name\t" << "Age\t" << endl;
	for (int i = 0; i < s.count; i++) {									//print the student in the list from the head node to the end of the list 
		cout << walker->data.dept << "\t"
			<< walker->data.gender << "\t"
			<< walker->data.name << "\t"
			<< walker->data.age << endl;
		walker = walker->next;
	}
}

void List::print_category_menu() {													//print function 
	cout << endl << "---------------Category---------------" << endl;
	cout << "1. Dept" << endl;
	cout << "2. Gender" << endl;
	cout << "3. Dept and Gender" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Selection: "; 
	return; 
}

void List::print_function_menu() {													//print function 
	cout << endl << "---------------Function---------------" << endl;
	cout << "1. Average" << endl;
	cout << "2. Max" << endl;
	cout << "3. Min" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Selection: ";
	return;
}

void List::pivot(List s) {
	if (s.head == NULL) {
		cout << "student doesn't exists in the list. Try again. " << endl;
		return;
	}

	print_category_menu();							//category: dept / gender / dept & gender
	int category;
	cin >> category;

	print_function_menu();							//function: average / max / min 
	int function;
	cin >> function;

	if (function == 1 || function == 2 || function == 3) {
		switch (category) {
		case 1: //dept 
			category_dept(s, function);
			break;
		case 2: //gender 
			category_gender(s, function);
			break;
		case 3: //dept and gender 
			category_dept_gender(s, function);
			break;
		default:																	//when none of the above category is chosen, print error message and go back to the menu 
			cout << "Wrong category entered! Go back to the menu" << endl;
		}
	}
	else {
		cout << "Wrong calculation entered! Go back to the menu" << endl;					//when none of the above function is chosen, print error message and go back to the menu 
	}

	

	return;
}

void List::category_dept(List s, int function) {
	int arr[2][9] = {};															//array[0] will get the age and array[1] will get the number of students in the dept 
	string dept_list[9] = {};													//since the dept array in s_list is not sorted, I will resave the dept in this array 
	
	Node* walker = s.head;
	int dept = 0;

	float answer[9] = {};														//this will save the answer that will be printed 

	switch (function) {
	case 1: //average 

		for (int i = 0; i < s.count; i++) {
			dept_list[dept] = walker->data.dept;								//save the new dept to the dept_list array 
			arr[0][dept] += walker->data.age;
			arr[1][dept] ++;
			if (walker->next != NULL && walker->data.dept.compare(walker->next->data.dept) != 0) {		//if the next node has new dept, move on to the next dept_list array 
				dept++;
			}
			walker = walker->next;												//do the for loop for all student in the list 
		}

		cout << "Dept\t" << "Average\t" << endl;

		for (int i = 0; i < s.dept_cnt; i++) {
			answer[i] = round(((float)arr[0][i] / arr[1][i]) * 10) / 10;		//this will round up to 1 decimal place 
			if (answer[i]) {													//if age is 0, don't print 
				cout << dept_list[i] << "\t" << answer[i] << endl;
			}
		}
		break;
	case 2: // max 
		for (walker = s.head; walker != NULL; walker = walker->next) {		//stop when walker is NULL pointer 

			if (answer[dept] == 0) {												//initialization : let the first student of that dept has the max age 
				dept_list[dept] = walker->data.dept;								//add the new dept to the dept_list array 
				answer[dept] = walker->data.age;   
				continue; 
			}

			if (walker->data.dept.compare(walker->next->data.dept) != 0) {			//if the next node of walker has new dept, increase dept var. 
				dept++;
				continue;
			}

			if (answer[dept] < walker->data.age) {						// if walker->next node is older than walker age, let the walker->next age be the max 
				answer[dept] = walker->data.age;
				continue;
			}

		}

		cout << "Dept\t" << "Max\t" << endl;

		for (int i = 0; i < s.dept_cnt; i++) {										//print the result 
			if (answer[i]) {														//if age is 0, don't print 
				cout << dept_list[i] << "\t" << answer[i] << endl;
			}
		}
		break;
	case 3: //min																	do the same task as max but just the inequality is changed 
		for (walker = s.head; walker != NULL; walker = walker->next) {

			if (answer[dept] == 0) {
				dept_list[dept] = walker->data.dept;
				answer[dept] = walker->data.age;  
			}

			if (walker->data.dept.compare(walker->next->data.dept) != 0) {
				dept++;
				continue;
			}

			if (answer[dept] > walker->data.age) {						//if walker->next node is younger than walker age, let the walker->next age be the max 
				answer[dept] = walker->data.age;
				continue;
			}

		}

		cout << "Dept\t" << "Max\t" << endl;

		for (int i = 0; i < s.dept_cnt; i++) {										//print the result 
			if (answer[i]) {														//if age is 0, don't print 
				cout << dept_list[i] << "\t" << answer[i] << endl;
			}
		}
		break;
	}
	return;
}

void List::category_gender(List s, int function) {
	int female = 0, male = 0;													//these variables will save the age 
	int f_cnt = 0, m_cnt = 0;													//these variables will save the number of students who are male/ female 

	float female_answer = 0, male_answer = 0; 

	Node* walker = s.head;

	switch (function) {
	case 1: //average 

		for (int i = 0; i < s.count; i++) {
			if (walker->data.gender.compare("F") == 0) {						//from input_info, I only accepted either F or M, so I used if else statement 
				female += walker->data.age;
				f_cnt++;
			}
			else {
				male += walker->data.age;
				m_cnt++;
			}
			walker = walker->next;
		}
			
		female_answer = round(((float)female / f_cnt) * 10) / 10;			//round up to 1 decimal place 
		male_answer = round(((float)male / m_cnt) * 10) / 10;


		cout << "Gender\t" << "Average\t" << endl;								//print the result 

		if (female != 0) {														//if age is 0, don't print 
			cout << "F\t" << female_answer << endl;
		}
		if (male != 0) {														//if age is 0, don't print 
			cout << "M\t" << male_answer << endl;
		}

		break;
	case 2: // max 
		for (walker = s.head; walker != NULL; walker = walker->next) {
			if (walker->data.gender.compare("F") == 0) {						//for female 					
				if (female == 0) {												//initialization 
					female = walker->data.age;
					continue; 
				}	
				if (female < walker->data.age) {								//compare the past max age and the walker's age 
					female = walker->data.age;
				}
			}
				
			if (walker->data.gender.compare("M") == 0) {						//for male 
				if (male == 0) {												//initialization 
					male = walker->data.age;
					continue;
				}
				if (male < walker->data.age) {									//compare the past max age and the walker's age 
					male = walker->data.age;
				}
			}

		}

		cout << "Gender\t" << "Max\t" << endl;									//print the result 

		if (female != 0) {														//if age is 0, don't print 
			cout << "F\t" << female << endl;
		}	
		if (male != 0) {														//if age is 0, don't print 
			cout << "M\t" << male << endl;
		}

		break;
	case 3: //min
		for (walker = s.head; walker != NULL; walker = walker->next) {
			if (walker->data.gender.compare("F") == 0) {						//for female 	
				if (female == 0) {												//initialization 
					female = walker->data.age;
				}
				if (female > walker->data.age) {								//compare the past max age and the walker's age 
					female = walker->data.age;
				}
			}

			if (walker->data.gender.compare("M") == 0) {						//for male 
				if (male == 0) {												//initialization 
					male = walker->data.age;
				}
				if (male > walker->data.age) {									//compare the past max age and the walker's age 
					male = walker->data.age;
				}
			}

		}

		cout << "Gender\t" << "Max\t" << endl;									//print the result 

		if (female != 0) {														//if age is 0, don't print 
			cout << "F\t" << female << endl;
		}
		if (male != 0) {														//if age is 0, don't print 
			cout << "M\t" << male << endl;
		}

		return;
	}
}

void List::category_dept_gender(List s, int function) {
	int average[2][18] = {}, max[18] = {}, min[18] = {};						//since max dept # is 9 and there are two gender, I made array size of 18 (average is 2 * 18)  
	string dept_list[18] = {};													//only the even elements will have the value 

	Node* walker = s.head; 
	int dept = 0;

	for (int i = 0; i < s.count; i++) {											//for loop for all students in the list 
		
		dept_list[dept] = walker->data.dept;									//save the new dept to the dept_list string array (will be used when print the result 
		
		if (walker->data.gender.compare("F") == 0) {							//for female 
			average[0][dept] += walker->data.age;								//female will be saved in even-th element 
			average[1][dept] ++;												//this will count the number of female students added 
			if (max[dept] == 0) {												//initialization for max 
				max[dept] = walker->data.age;
			}
			else {																//compare max and walker's age 
				if (max[dept] < walker->data.age) {
					max[dept] = walker->data.age;
				}
			}
			if (min[dept] == 0) {												//initialization for min 
				min[dept] = walker->data.age;
			}
			else {																//compare min and walker's age 
				if (min[dept] > walker->data.age) {
					min[dept] = walker->data.age;
				}
			}
		}
		else {																	//for male 
			average[0][dept + 1] += walker->data.age;							//male info will be saved in odd-th element 				
			average[1][dept + 1] ++;											//this will count the number of male students added 
			
			if (max[dept + 1] == 0) {											//initialization for max 
				max[dept + 1] = walker->data.age;
			}
			else {
				
				if (max[dept + 1] < walker->data.age) {							//compare max and walker's age 
					max[dept + 1] = walker->data.age;
				}
			}
			
			if (min[dept + 1] == 0) {											//initialization for min 
				min[dept + 1] = walker->data.age;
			}
			else {
				
				if (min[dept + 1] > walker->data.age) {							//compare min and walker's age 
					min[dept + 1] = walker->data.age;
				}
			}
		}
		if (walker->next != NULL && walker->data.dept.compare(walker->next->data.dept) != 0) {	//if new dept 
			dept += 2;															//+=2 because only the even-th array contains the name of the dept  
		}
		walker = walker->next;
	}

	float answer[18] = {};

	//answers are made. so now we just have to print the results. 
	switch (function) {
	case 1: //average
		cout << "Dept\t" << "Gender\t" << "Average" << endl;
																	//rounded answers will be saved here 


		for (int i = 0; i < 18; i += 2) {
			answer[i] = round(((float)average[0][i] / average[1][i]) * 10) / 10;			//round to one decimal place 
			if (average[0][i] != 0) {														//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "F" << "\t" << answer[i] << endl;
			}
			
			answer[i + 1] = round(((float)average[0][i + 1] / average[1][i + 1]) * 10) / 10;	//round to one decimal place 
			if (average[0][i + 1] != 0) {														//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "M" << "\t" << answer[i + 1] << endl;
			}
		}
		break;
	case 2:
		cout << "Dept\t" << "Gender\t" << "Max" << endl;
		for (int i = 0; i < 18; i += 2) {
			if (max[i] != 0) {																	//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "F" << "\t" << max[i] << endl;
			}
			if (max[i + 1] != 0) {																//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "M" << "\t" << max[i + 1] << endl;
			}
		}
		break;
	case 3:
		cout << "Dept\t" << "Gender\t" << "Min" << endl;
		for (int i = 0; i < 18; i += 2) {
			if (min[i] != 0) {																	//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "F" << "\t" << min[i] << endl;
			}
			if (min[i + 1] != 0) {																//if age is 0, don't print 
				cout << dept_list[i] << "\t" << "M" << "\t" << min[i + 1] << endl;
			}
		}
		break;
	}
	return;
}

void List::del_node(List* s) {			//deallocation 
	if (s->head == NULL) {			//no student in the list 
		return; 
	}
	
	Node* walker = s->head; 
	s->head = NULL; 
	
	while (walker != NULL) {
		Node* temp = walker; 
		walker = walker->next; 
		delete temp; 
	}
	return; 
}