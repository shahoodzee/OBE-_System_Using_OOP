#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<stack>
#include<conio.h>


#pragma warning(disable:4996)
using namespace std;



//obser
class filing
{
public:
	virtual void writefile() {}
	virtual void readfile() {}
	virtual void searchfile() {}
	virtual void deletefile() {}

};
class functionality {
public:
	virtual void add_entity() 
	{
		//cout << "base class" << endl;
	}
	virtual void update_entity()
	{
		//cout << "base class" << endl;
	}
	virtual void remove_entity()
	{
		//cout << "base class" << endl;
	}
};

/*
   |CLO|n ----------------1|learning outcome|1---------------n|Questions|
*/

class CLO 
{
protected:
	int clo_id;
	char clo_name[20] = "";
	int count = 0;

public:

	CLO()
	{
		clo_id = count = 0;
	}
	CLO(int clo_id, string clo_name1)
	{
		this->clo_id = clo_id;
		strcpy(this->clo_name, clo_name1.c_str());
	}
	void show()
	{
		cout << "id: " << this->clo_id << '\t' << "clo_name: " << clo_name << endl;
	}
	bool record_exists(int number)
	{
		ifstream f("clo.dat", ios::binary);
		while (f.read((char*)this, sizeof(CLO)))
		{
			if (this->clo_id == number)
			{
				return true;
			}
		}
		f.close();
		return false;
	}
	void add_entity(int id, string name)//clo 
	{
		this->clo_id = id;
		strcpy(this->clo_name, name.c_str());
		ofstream file("clo.dat", ios::binary | ios::app);
		file.write((char*)this, sizeof(CLO));
		count++;
		file.close();
	}
	void add_entity_direct_into_course(int id, string name, string filename)
	{
		char Filename[20];
		this->clo_id = id;
		count = count + 1;

		strcpy(this->clo_name, name.c_str());
		strcpy(Filename, filename.c_str());
		strcat(Filename, ".dat");
		ofstream file(Filename, ios::binary | ios::app);
		file.write((char*)this, sizeof(CLO));
		file.close();
	}
	void remove_entity(int remove1, string filename)
	{
		int pos = 0, flag = 0;
		char Filename[20];
		strcpy(Filename, filename.c_str());
		strcat(Filename, ".dat");
		ifstream ifs;
		ifs.open(Filename, ios::in | ios::binary);
		ofstream ofs;
		ofs.open("temp.dat", ios::out | ios::binary);

		while (!ifs.eof())
		{

			ifs.read((char*)this, sizeof(CLO));

			// if(ifs)checks the buffer record in the file
			if (ifs)
			{
				// comparing the roll no with
				// roll no of record to be deleted
				if (this->clo_id == remove1) {
					flag = 1;
					cout << "The deleted record is \n";
					// display the record
					this->show();
				}
				else
				{
					// copy the record of "student" file to "temp" file
					ofs.write((char*)this, sizeof(CLO));
				}
			}
		}

		ofs.close();
		ifs.close();

		// delete the old file
		remove(Filename);
		// rename new file to the older file
		int awein_warning_remove_krne_k_liye = rename("temp.dat", Filename);
		if (flag == 1)
		{
			cout << "\nrecord successfully deleted \n";
		}
		else
		{
			cout << "\nrecord not found \n";
		}
	}
	void update_entity(int id, string update,string filename)
	{
		int pos, flag = 0;
		
		char Filename[20];
		strcpy(Filename, filename.c_str());
		strcat(Filename, ".dat");
		
		fstream file;
		file.open(Filename, ios::in | ios::binary | ios::out);

		while (!file.eof()) {
			// storing the position of
			// current file pointeri.e. at
			// the end of previously read record
			pos = file.tellg();

			file.read((char*)this, sizeof(CLO));
			if (file)
			{
				// comparing the roll no with that
				// of the entered roll number
				if (this->clo_id == id) {
					flag = 1;

					// setting the new (modified)
					// data of the object or new record
					strcpy(this->clo_name, update.c_str());

					// placing the put(writing) pointer
					// at the starting of the  record
					file.seekp(pos);

					// writing the object to the file
					file.write((char*)this, sizeof(CLO));

					// display the data
					cout << "file updated! as" << endl;
					this->show();
					break;
				}
			}
		}
		file.close();

		if (flag == 1)
			cout << "\nrecord successfully modified \n";
		else
			cout << "\nrecord not found \n";
	}
	void get_all_clo()
	{
		ifstream file("clo.dat", ios::binary);
		while (file.read((char*)this, sizeof(CLO)))
		{
			this->show();
		}
		file.close();
	}
	void get_all_clos_from_particular_course(string filename)
	{
		int number = 0;
		ifstream file(filename + ".dat", ios::binary);
		cout << "" << endl;
		cout << "-----------------------------------------\n";
		while (true)
		{
			file.read((char*)this, sizeof(CLO));
			if (file.eof() == true)
			{
				number = this->count;
				cout << "CLO count" << this->count << endl;
				break;
			}
			this->show();
		}
		file.close();
		cout << "-----------------------------------------\n";
		//return number;
	}
	int get_clo_count(string c_code)
	{
		int number = 0;
		ifstream file(c_code + ".dat", ios::binary);
		while (!file.eof())
		{
			file.read((char*)this, sizeof(CLO));
			number = this->count;
		}
		file.close();
		return number;
	}

};
class Course :public functionality,public filing
{
protected:
	char course_code[10] = "";
	char course_name[50] = "";
	char pre_req_name[50] = "";
	char program[10] = "";
	int credit_hours = 0;

public:
	Course(){}
	void show_course() 
	{
		cout << "course_code: " << course_code << "\t" << "course_name: " << course_name << "\t";
		cout << "pre-requisite: " << pre_req_name << "\t" << " Credit_hours: " << credit_hours << endl;
	}
	void get_all_crs()
	{ 
		ifstream file("course.dat", ios::binary);
		cout << "-----------------------------------------\n";
		while (file.read((char*)this, sizeof(Course)))
		{
			this->show_course();
		}
		file.close();
		cout << "-----------------------------------------\n";

	}
	void add_entity(string code, string name,string pre_req,string program,int credit_hours)
	{
		cout << "Add a Course from course class" << endl;
		//must satisfy a CLO
		strcpy(this->course_code, code.c_str());
		strcpy(this->course_name, name.c_str());
		strcpy(this->pre_req_name, pre_req.c_str());
		strcpy(this->program, program.c_str());
		this->credit_hours = credit_hours;

		ofstream file("course.dat", ios::binary | ios::app);
		file.write((char*)this, sizeof(Course));
		file.close(); int option = 0;

		cout << "list all the CLOS for this course" << endl;
		CLO* clo = new CLO; int clo_id=0; string clo_name;
		while (true)
		{
			cout << "skip adding clos by pressing 0 at any input of clo id " << endl;
			cout << "enter clo id" << endl; cin >> clo_id;
			if (clo_id == 0)
			{
				break;
			}
			cout << "clo name" << endl; cin >> clo_name;
			clo->add_entity_direct_into_course(clo_id, clo_name, code);
			system("cls");
			cout << "clo added!" << endl;
		}
	}
	void remove_entity(string code)
	{
		//cout << "remove an assignment or quiz" << endl;
		char crs_code[10];
		strcpy(crs_code, code.c_str());
		int pos=0, flag = 0;
		ifstream ifs;
		ifs.open("course.dat", ios::in | ios::binary);
		ofstream ofs;
		ofs.open("temp_course.dat", ios::out | ios::binary);

		while (!ifs.eof())
		{
			ifs.read((char*)this, sizeof(Course));

			// if(ifs)checks the buffer record in the file
			if (ifs)
			{
				// comparing the roll no with
				// roll no of record to be deleted
				if (strcmp(this->course_code, crs_code) == 0)
				{
					flag = 1;
					cout << "The deleted record is \n";
					// display the record
					this->show_course();
				}
				else
				{
					// copy the record of "student" file to "temp" file
					ofs.write((char*)this, sizeof(Course));
				}
			}
		}

		ofs.close();
		ifs.close();

		// delete the old file
		remove(strcat(course_code,".dat"));//deleting the spearate file too where we list all the CLO's
		remove("course.dat");
		// rename new file to the older file
		int awein_warning_remove_krne_k_liye2 = rename("temp_course.dat", "course.dat");
		if (flag == 1)
		{
			cout << "\nrecord successfully deleted \n";
		}
		else
		{
			cout << "\nrecord not found \n";
		}

	}
	void update_entity(string code,string name)
	{
		int pos, flag = 0;
		char crs_code[50];
		strcpy(crs_code,code.c_str());
		fstream file;
		file.open("course.dat", ios::in | ios::binary | ios::out);

		while (!file.eof()) {
			// storing the position of
			// current file pointeri.e. at
			// the end of previously read record
			pos = file.tellg();

			file.read((char*)this, sizeof(Course));
			if (file)
			{
				// comparing the roll no with that
				// of the entered roll number
				if (strcmp(this->course_code, crs_code) == 0)
				{
					flag = 1;

					// setting the new (modified)
					// data of the object or new record
					strcpy(this->course_name, name.c_str());

					// placing the put(writing) pointer
					// at the starting of the  record
					file.seekp(pos);

					// writing the object to the file
					file.write((char*)this, sizeof(Course));

					// display the data
					cout << "course code updated! as" << endl;
					this->show_course();
					break;
				}
			}
		}
		file.close();

		if (flag == 1)
			cout << "\nrecord successfully modified \n";
		else
			cout << "\nrecord not found \n";
	}
};

class Question	//q_id	question clo_id clo_name
{
private:
	int q_id;
	int clo;
	char question[100] = "";

public:
	CLO* ptr = nullptr;
	Question()
	{
		q_id = 0;
		clo = 0;
		ptr = new CLO;
	}
	void show_question()
	{
		if (this->q_id > 0)
		{
			cout << "Question #" << this->q_id << " ";
			cout << question << " CLO [" << clo << "] \n";
		}
	}
	void show_all_questions(string filename)
	{
		ifstream file(filename, ios::binary);
		cout << "-----------------------------------------\n";
		while (file.read((char*)this, sizeof(Question)))
		{
			this->show_question();
		}
		file.close();
		cout << "-----------------------------------------\n";
	}
	void Add_question(string course_name, string filename, int id)
	{
		int find_clo = 0;
		show_all_questions(filename);
		cout << "enter Question# " << endl;
		cin >> q_id;
		/*test the question against ClOs*/
		ptr->get_all_clos_from_particular_course(course_name);

		cout << "\nEnter CLO to attach with the question" << endl;
		cin >> clo;

		cout << "Enter your question" << endl;
		cin.ignore(); cin.getline(this->question, 100);

		ofstream f;
		f.open(filename, ios::binary | ios::app);
		f.write((char*)this, sizeof(Question));
		cout << "Question saved in assignment" << endl;
		f.close();

		show_question();
	}
	void remove_question(string filename, int del_id)
	{
		int flag = 0, pos = 0;


		ifstream ifs;
		ifs.open(filename, ios::in | ios::binary);
		ofstream ofs;
		ofs.open("temp.dat", ios::out | ios::binary);

		while (!ifs.eof())
		{
			ifs.read((char*)this, sizeof(Question));

			// if(ifs)checks the buffer record in the file
			if (ifs)
			{
				// comparing the roll no with
				// roll no of record to be deleted
				if (this->q_id == del_id) {
					flag = 1;
					cout << "The deleted record is \n";
					// display the record
					this->show_question();
				}
				else
				{
					// copy the record of "student" file to "temp" file
					ofs.write((char*)this, sizeof(Question));
				}
			}
		}

		ofs.close();
		ifs.close();
		// delete the old file
		remove(filename.c_str());
		// rename new file to the older file
		int awein_warning_remove_krne_k_liye = rename("temp.dat", filename.c_str());
		if (flag == 1)
		{
			cout << "\nrecord successfully deleted \n";
		}
		else
		{
			cout << "\nrecord not found \n";
		}


	}
	void update_question(string filename, int id, string new_quesiton)
	{
		int pos, flag = 0;

		fstream file;
		file.open(filename, ios::in | ios::binary | ios::out);

		while (!file.eof()) {
			// storing the position of
			// current file pointeri.e. at
			// the end of previously read record
			pos = file.tellg();

			file.read((char*)this, sizeof(Question));

			if (file)
			{
				// comparing the roll no with that
				// of the entered roll number
				if (this->q_id == id) {
					flag = 1;

					// setting the new (modified)
					// data of the object or new record
					strcpy(this->question, new_quesiton.c_str());

					// placing the put(writing) pointer
					// at the starting of the  record
					file.seekp(pos);

					// writing the object to the file
					file.write((char*)this, sizeof(Question));

					// display the data
					cout << "file updated!" << endl;
					break;
				}
			}
		}
		file.close();

		if (flag == 1)
			cout << "\nrecord successfully modified \n";
		else
			cout << "\nrecord not found \n";

	}
	void update_question_clo(string filename, int id, int clo)
	{
		int pos, flag = 0;

		fstream file;
		file.open(filename, ios::in | ios::binary | ios::out);

		while (!file.eof()) {
			// storing the position of
			// current file pointeri.e. at
			// the end of previously read record
			pos = file.tellg();

			file.read((char*)this, sizeof(Question));

			if (file)
			{
				// comparing the roll no with that
				// of the entered roll number
				if (this->q_id == id) {
					flag = 1;
					cout << "question id found!" << endl;
					// setting the new (modified)
					// data of the object or new record
					this->clo = clo;

					// placing the put(writing) pointer
					// at the starting of the  record
					file.seekp(pos);

					// writing the object to the file
					file.write((char*)this, sizeof(Question));

					// display the data
					cout << "file updated!" << endl;
					show_question();
					break;
				}
			}
		}
	};
	int return_clo() 
	{
		return this->clo;
	}
};

class observer
{
private:
	int id;
	char filename[50] = "";
	int arr[10] = {};
public:
	int clo_num = 0;
	CLO* ptr = nullptr;
	observer()
	{
		id = 0;
	}
	int get_length() 
	{
		int len = 0;
		for (int i = 0; i < 10; i++)
		{
			if (arr[i] != 0)
			{
				len++;
			}
		}
		return len;
	}
	bool search_eval(string filetype,int id)
	{
		ifstream f("assignment.dat", ios::binary);
		while (f.read((char*)this, sizeof(observer)))
		{
			if (this->id == id)
			{
				return true;
			}
		}
		f.close();
		return false;
	}
	void show_eval(string filetype)
	{
		if (filetype == "assignment.dat")
		{
			cout << "as_id: a" << this->id << " filename :" << this->filename << endl;
		}
		else if (filetype == "exam.dat")
		{
			cout << "ex_id: e" << id << " filename :" << filename << endl;
		}
		else if (filetype == "quiz.dat")
		{
			cout << "q_id: q" << id << " filename :" << filename << endl;
		}
	}
	void show_all_evals(string filetype,string c_code)
	{
		ptr = new CLO; system("cls");
		cout << "CLO count:" << ptr->get_clo_count(c_code) << endl;
		cout << "arr:" << get_length() << endl;
		int num = 0;
		ifstream f;
		f.open(filetype, ios::binary);
		cout << "-----------------------------------------\n";
		cout << "CLO's -> ";
		for (int i = 0; i < 10; i++)
		{
			cout <<arr[i] << " ";
		}
		cout << endl;

		//while (f.read((char*)this, sizeof(observer)))
		while (f.read((char*)this, sizeof(observer)))
		{
			show_eval(filetype);
		}
		cout << "-----------------------------------------\n";
		f.close();


	}
	void add_in_eval(string c_code, string filename, string filetype, int id)
	{
		int arr[10] = {};
		strcpy(this->filename, filename.c_str());
		this->id = id;

		ofstream myfile;
		myfile.open(filetype, ios::binary | ios::app);

		system("cls");

		cout << "Adding questions in assignment!\n";
		Question* ptr1 = new Question;

		for (int i = 0; true; i++)
		{
			ptr1->Add_question(c_code, filename + ".dat", i + 1);
			clo_num = ptr1->return_clo();

			for (int i = 0; i < 10; i++)
			{
				if (arr[i] == clo_num)
				{
					break;
				}
				if (arr[i] == 0)
				{
					arr[i] = clo_num;
					break;
				}
			}

			cout << "Press 1 to finish or any key to continue...... \n";
			int option = 0;	
			cin >> option;
			if (option == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					this->arr[i] = arr[i];
				}
				myfile.write((char*)this, sizeof(observer));
				myfile.close();
				show_all_evals("assignment.dat",c_code);
				break;

			}
		}
		system("pause");
		system("cls");

	}
	void remove_in_eval(string filename, int del_id)
	{
		int flag = 0, pos = 0;
		ifstream ifs;
		ifs.open(filename, ios::in | ios::binary);
		ofstream ofs;
		ofs.open("temp.dat", ios::out | ios::binary);

		while (!ifs.eof())
		{

			ifs.read((char*)this, sizeof(observer));

			// if(ifs)checks the buffer record in the file
			if (ifs)
			{
				// comparing the roll no with
				// roll no of record to be deleted
				if (this->id == del_id) {
					flag = 1;
					cout << "The deleted record is \n";
					// display the record
					this->show_eval("assignment.dat");
				}
				else
				{
					// copy the record of "student" file to "temp" file
					ofs.write((char*)this, sizeof(observer));
				}
			}
		}

		ofs.close();
		ifs.close();

		// delete the old file
		remove(filename.c_str());
		// rename new file to the older file
		int awein_warning_remove_krne_k_liye = rename("temp.dat", filename.c_str());
		if (flag == 1)
		{
			cout << "\nrecord successfully deleted \n";
		}
		else
		{
			cout << "\nrecord not found \n";
		}
	}
	void update_in_eval(string filename) 
	{
		string question; int num = 0; int q_id = 0; int clo = 0;
		Question* ptr;
		system("cls");
		cout << "functions:\n";
		cout << "1 Update a question \n";
		cout << "2 Update a CLO      \n";
		cout << "3 Delete a question \n";
		cin >> num;
		cout << "enter question ID " << endl;
		cin >> q_id;
		switch (num)
		{
		case 1:
			cout << "Enter new question?" << endl;
			cin.ignore(); getline(cin, question);
			ptr = new Question;
			ptr->update_question(filename, q_id, question);
			break;
		case 2:
			cout << "Enter new CLO" << endl;
			cin >> clo;
			ptr = new Question;
			ptr->update_question_clo(filename, q_id, clo);
			break;
		case 3:
			ptr = new Question;
			ptr->remove_question(filename, q_id);
			break;
		default:
			system("cls");
			cout << "wrong input!" << endl;
			break;
		}
	}

};
class Evaluation
{
public:
	virtual void Add_Evaluation(string filename)
	{

	}
	virtual void Update_Evaluation(string filename)//update an exam/assignment by changing the question/clo to be tested.
	{

	}
	virtual void Remove_Evaluation(string filename)
	{

	}
	virtual void Show_Evaluation(string c_code)
	{

	}
};
class Assignment :public Evaluation
{
	char filename[50] = "";
	int as_id = 0;
	Question* ptr;
public:
	observer* obs = nullptr;
	Assignment()
	{
		ptr = new Question;
	}
	void show() 
	{
		obs = new observer;
		obs->show_eval("assignment.dat");
	}
	void delete_assignment(int rev_id)
	{
		int flag=0,pos = 0;
		ifstream ifs;
		ifs.open("assignment.dat", ios::in | ios::binary);
		ofstream ofs;
		ofs.open("temp.dat", ios::out | ios::binary);

		while (!ifs.eof())
		{

			ifs.read((char*)this, sizeof(Assignment));

			// if(ifs)checks the buffer record in the file
			if (ifs)
			{
				// comparing the roll no with
				// roll no of record to be deleted
				if (this->as_id == rev_id) {
					flag = 1;
					cout << "The deleted record is \n";
					// display the record
					this->show();
				}
				else
				{
					// copy the record of "student" file to "temp" file
					ofs.write((char*)this, sizeof(Assignment));
				}
			}
		}

		ofs.close();
		ifs.close();

		// delete the old file
		remove("assignment.dat");
		// rename new file to the older file
		int awein_warning_remove_krne_k_liye = rename("temp.dat", "assignment.dat");
		if (flag == 1)
		{
			cout << "\nrecord successfully deleted \n";
		}
		else
		{
			cout << "\nrecord not found \n";
		}
	}
	void Show_Evaluation(string c_code)
	{
		obs = new observer;
		obs->show_all_evals("assignment.dat",c_code);
	}
	void Add_Evaluation(string c_code) 
	{
		obs = new observer;

		cout << "Give as_id" << endl;	
		int id; cin >> id; this->as_id = id;
		
		string filename = c_code + "_assignment_a"+ to_string(as_id);
		strcpy(this->filename, filename.c_str());

		obs = new observer;
		obs->add_in_eval(c_code, filename, "assignment.dat", id);

		cout << "Assignment saved in list successfully......\n\n\n" << endl;
	}
	void Remove_Evaluation(string c_code) 
	{
		cout << "enter as_id of file to be removed :\na"; 
		int del_id;		cin >> del_id;

		//observer_list* olst = new observer_list;
		//olst->remove("assignmentclo");

		c_code = c_code + "_assignment_a" + to_string(del_id) + ".dat";
		
		obs = new observer;
		obs->remove_in_eval("assignment.dat", del_id);

		remove(c_code.c_str());
	}
	void Update_Evaluation(string c_code)
	{
		cout << "Enter as_id of the assignment to edit\n" << endl;
		int a = 0;		cin >> a;

		string filename = c_code + "_assignment_a" + to_string(a) + ".dat";
		obs = new observer;
		obs->update_in_eval(filename);

	}

};
class Exam :public Evaluation
{
};
class Quiz :public Evaluation
{
};
class Program : public functionality
{
public:
	void add_entity()
	{
		cout << "Add a program from program class" << endl;
	}
	void remove_entity()
	{
		cout << "Remove a program from program class" << endl;
	}
	void update_entity()
	{
		cout << "Update a program from program class" << endl;
	}
};
class PLO {};
class user {
public:
	virtual void signin() {}
};
class academicofficer :public user
{
protected:
	Course* crs = new Course;
	Program* prgm = new Program;
	CLO* clo = new CLO;
	int option = 0;
public:
	void signin() {
		cout << "user signed in as AO\n functions : Course, Program" << endl;
		system("pause");
		system("cls");
		while (true)
		{
			cout << "0 back\n1 Course\n2 Program\n3 edit CLO's for A course \n4 edit PLO'S for A Program\n";
			cin >> option;
			if (option == 0)
			{
				break;
			}
			else if (option == 1)
			{
				cout << "course selected!\n";
				crs->get_all_crs();
				cout << "Funcitonalities:\n 0 back\n1 add\n2 update\n3 remove\n";
				cin >> option;
				if (option == 0)
				{
					break;
				}
				else if (option == 1)
				{
					string pre_req_name; string program;
					string id; string name; int req = 0, crd_hrs = 0;
					cout << "enter course code (i.e: cs2001)" << endl; cin >> id;
					cout << "enter course name\n"; cin.ignore(); getline(cin, name);
					cout << "Enter program name\n"; cin.ignore(); getline(cin, program);
					cout << "enter credit hours\n"; cin >> crd_hrs;

					cout << "Does this course has any pre requisite\n 1 yes\n0 no\n"; 
					cin >> req;
					if (req == 1)
					{
						cout << "Enter pre req name"; cin >> pre_req_name;
						crs->add_entity(id, name, pre_req_name, program,crd_hrs);
					}
					else
					{
						crs->add_entity(id, name, "no pre_req", program, crd_hrs);
					}
				}
				else if (option == 2)
				{
					string id; string name;
					cout << "enter course code of course to update" << endl; cin >> id;
					cout << "write the updated name of the course" << endl; cin >> name;
					crs->update_entity(id,name);
				}
				else if (option == 3)
				{
					cout << "enter course code to delete" << endl; string del; cin >> del;
					crs->remove_entity(del);
				}
				else
				{
					cout << "wrong input()\n";
				}
			}
			else if (option == 3)
			{
				Course* crs = new Course;
				system("cls");
				crs->get_all_crs();
				cout << "select Course by entering course code" << endl;
				string code; cin >> code;

				cout << "CLO selected!\n funcitonalities\n";
				clo->get_all_clos_from_particular_course(code);
				cout << "0 back\n1 Add CLO\n2 Update clo\n3 Remove clo\n";
				cin >> option;
				if (option == 0)
				{
					break;
				}
				else if (option == 1)
				{
					int id; string name;
					cout << "id:" << endl; cin >> id;
					cout << "clo name" << endl; cin >> name;
					system("cls");
					clo->add_entity_direct_into_course(id,name,code);
					clo->get_all_clos_from_particular_course(code);
				}
				else if (option == 2)
				{
					string update; int id;
					cout << "enter id whose CLO name you want to enter" << endl; cin >> id;
					cout << "enter new CLO name" << endl; cin >> update;
					system("cls");
					clo->update_entity(id, update, code);
				}
				else if (option == 3)
				{
					int id = 0; 
					cout << "enter ID to remove from CLO list" << endl;
					cin >> id;
					system("cls");
					clo->remove_entity(id,code);
				}
				else
				{
					cout << "wrong input()\n";
				}
			}
			else
			{
				cout << "wrong input";
			}
		}
		

	}
};
class teacher :public user
{
private:
	int entity = 0;
	int n = 0;
	string c_code;
	Assignment ass;
	Exam ex;
	Course* cr = new Course;
public:
	void signin() 
	{
		system("cls");
		cout << "User sisgned in as Teacher (fucntions: Conduct Evaluation)\nAvailable Courses:\n";
		cr->get_all_crs();
		cout << "Select Course by its code (cs2001)" << endl;
		cin >> c_code;
		int show = 0;
		while (true)
		{
			cout << "\n\n0-back\n1-Add evaluation\n2-update evaluation\n3-Remove evaluation\n4-Show EValuations" << endl;
			cin >> entity;
			if (entity == 0)
			{
				break;
			}
			else if (entity == 1)
			{
				Evaluation* ptr = nullptr;
				cout << "select option:\n1-Assignment\n2-Exam\n";
				cin >> n;
				if (n == 1)
				{
					ptr = new Assignment;
					ptr->Show_Evaluation(c_code);
					ptr = new Assignment;
					ptr->Add_Evaluation(c_code);
				}
				else if (n == 2)
				{
					ptr = new Exam;
					ptr->Show_Evaluation(c_code);
					ptr = new Exam;
					ptr->Add_Evaluation(c_code);
				}

			}
			else if (entity == 2)
			{
				Evaluation* ptr = nullptr;
				cout << "select option:\n1-Assignment\n2-Exam\n"; cin >> n;
				if (n == 1)
				{
					ptr = new Assignment;
					ptr->Show_Evaluation(c_code);
					ptr = new Assignment;
					ptr->Update_Evaluation(c_code);
				}
				else if (n == 2)
				{
					ptr = new Exam;
					ptr->Show_Evaluation(c_code);
					ptr = new Exam;
					ptr->Update_Evaluation(c_code);
				}
			}
			else if (entity == 3)
			{
				Evaluation* ptr = nullptr;
				cout << "select option:\n1-Assignment\n2-Exam" << endl;	cin >> n;
				if (n == 1)
				{
					ptr = new Assignment;
					ptr->Show_Evaluation(c_code);
					ptr = new Assignment;
					ptr->Remove_Evaluation(c_code);
				}
				else if (n == 2)
				{
					ptr = new Exam;
					ptr->Show_Evaluation(c_code);
					ptr = new Exam;
					ptr->Remove_Evaluation(c_code);
				}
			}
			else if (entity == 4)
			{
				Evaluation* ptr = nullptr;
				cout << "select option:\n1-Assignment\n2-Exam\n"; 
				cin >> n;
				string filename;
				if (n == 1)
				{
					ptr = new Assignment;
					ptr->Show_Evaluation(c_code);
					cout << "Enter as id of the assignment." << endl;
					cin >> show;
					filename = c_code + "_assignment_a" + to_string(show) + ".dat";
					Question* q = new Question;
					q->show_all_questions(filename);
				}
				else if (n == 2)
				{
					ptr = new Exam;
					ptr->Show_Evaluation(c_code);
					cout << "Enter as id of the exam." << endl;
					cin >> show;
					filename = c_code + "_exam_a" + to_string(show) + ".dat";
					Question* q = new Question;
					q->show_all_questions(filename);
				}
			}
			else
			{
				cout << "wrong input \n";
				system("pause");
			}
		}

	}
};

int main()
{
	academicofficer ao;
	teacher tchr;
	user* ptr = nullptr;
	cout << "USER interface!\n1-Academic officer \n2-Teacher" << endl;
	int user = 0; cin >> user;
	if (user == 1)
	{
		ptr = &ao;
		ptr->signin();
	}
	else
	{
		ptr = &tchr;
		ptr->signin();
	}


	
} 
