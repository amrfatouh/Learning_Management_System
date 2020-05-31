/*
-no spaces are allowed
-no mumbers other than numbers specified in any menu are allowed
-still doesn't handle wrong inputs (string instead of numbers,..etc.)
-doesn't handle the case that any of the (courses,assignments,solutions) lists are empty
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
	string userName;
	string password;
public:
	Student(string a, string b)
	{
		userName = a;
		password = b;
	}
	string getPassword()
	{
		return password;
	}
	string getUserName()
	{
		return userName;
	}
};

class Solution
{
	string submitter, content, grade, comment;
public:
	Solution(string a, string b, string c, string d)
	{
		submitter = a;
		content = b;
		grade = c;
		comment = d;
	}
	string getSubmitter()
	{
		return submitter;
	}
	string getContent()
	{
		return content;
	}
	string getGrade()
	{
		return grade;
	}
	string getComment()
	{
		return comment;
	}
	void setSubmitter(string a)
	{
		submitter = a;
	}
	void setContent(string a)
	{
		content = a;
	}
	void setGrade(string a)
	{
		grade = a;
	}
	void setComment(string a)
	{
		comment = a;
	}
};

class Assignment
{
	string name;
	vector<Solution> SOLA;
public:
	Assignment(string assignmentName)
	{
		name = assignmentName;
	}
	void addSolution(Solution sol)
	{
		SOLA.push_back(sol);
	}
	string getAssignmentName()
	{
		return name;
	}
	Solution& getSolution(int i)
	{
		return SOLA[i];
	}
	vector<Solution>& getSolutionList()
	{
		return SOLA;
	}
};

class Course
{
	string name;
	vector<Assignment> ASSA; //assignments array
public:
	Course(string courseName)
	{
		name = courseName;
	}
	void createAssignment(string assignmentName)
	{
		ASSA.push_back(Assignment(assignmentName));
	}
	Assignment& getAssignment(int i) //must be sent by reference in order to change in it
	{
		return ASSA[i];
	}
	vector<Assignment>& getAssignmentsList() //must be sent by reference in order to change in it
	{
		return ASSA;
	}
	string getCourseName()
	{
		return name;
	}
};

class Doctor
{
	string userName;
	string password;
	vector<Course> CA; //courses array
public:
	Doctor(string u, string p)
	{
		userName = u;
		password = p;
	}
	void createCourse(string courseName)
	{
		CA.push_back(Course(courseName));
	}
	Course& getCourse(int i) //must be sent by reference in order to change in it
	{
		return CA[i];
	}
	vector<Course>& getCourseList() //must be sent by reference in order to change in it
	{
		return CA;
	}
	string getPassword()
	{
		return password;
	}
	string getUserName()
	{
		return userName;
	}
};


vector<Doctor> DA; //doctors array
vector<Student> SA; //students array

class WelcomeMenu
{
public:
	/*void showMessage()
	{
		cout << "welcome menu" << endl << "============" << endl;
		cout << "1)logIn" << endl << "2)register" << endl;
	}*/
	void userTypeMenu()
	{
		cout << endl << "User Type Menu" << endl << "==============" << endl;
		cout << "1)doctor" << endl;
		cout << "2)student" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			loginMenuDoctor();
		}
		else if (a == 2)
		{
			loginMenuStudent();
		}
	}
	void loginMenuDoctor()
	{
		cout << endl << "Login Menu" << endl << "==========" << endl;
		cout << "1)logIn" << endl << "2)register" << endl;
		int a;
		cin >> a;
		//taking input for logging in
		if (a == 1)
		{
			string userName;
			cout << "username: ";
			cin >> userName;
			//checking if the user name is available
			bool found = 0;
			int num;
			for (int i = 0; i < DA.size(); i++)
				if (userName == DA[i].getUserName())
				{
					found = 1;
					num = i;
					break;
				}
			if (found)
			{
				//checking password
				cout << "password: ";
				string password;
				cin >> password;
				if (password == DA[num].getPassword())
				{
					cout << "logged in successfully!" << endl;
					cout << "welcome, " << DA[num].getUserName() << endl;
					//logIn code
					mainMenuDoctor(num);
				}
				else
				{
					cout << "password is not correct" << endl;
					loginMenuDoctor();
				}
			}
			else
			{
				cout << "user name is not valid" << endl;
				loginMenuDoctor();
			}
		}
		//taking input for registering & checking it
		else if (a == 2)
		{
			cout << "register menu" << endl;
			cout << "user name: ";
			string userName;
			cin >> userName;

			bool failedUserName = 1;
			while (failedUserName)
			{
				failedUserName = 0;
				//checking that the user name does not match that of any other user;
				for (int i = 0; i < DA.size(); i++)
				{
					if (userName == DA[i].getUserName())
					{
						failedUserName = 1;
						break;
					}
				}

				//reprompting
				if (failedUserName)
				{
					cout << "user name already taken! Enter another user name" << endl;
					cout << "user name: ";
					cin >> userName;
				}
			}
			cout << "password: ";
			string password;
			cin >> password;

			//adding the new doctor to the array
			DA.push_back(Doctor(userName, password));
			loginMenuDoctor();
		}
	}
	void mainMenuDoctor(int num)
	{
		cout << endl << "Main Menu" << endl << "=========" << endl;
		cout << "1)list courses" << endl;
		cout << "2)create course" << endl;
		cout << "3)log out" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			//list courses
			for (int i = 0; i < DA[num].getCourseList().size(); i++)
			{
				cout << i << ")" << DA[num].getCourse(i).getCourseName() << endl;
			}
			cout << "choose the correspondent course number to view course" << endl;
			int b;
			cin >> b;
			courseMenuDoctor(num, b);

		}
		else if (a == 2)
		{
			//create course
			string courseName;
			cout << "course name: ";
			cin >> courseName;
			DA[num].createCourse(courseName);
			mainMenuDoctor(num);

		}
		else if (a == 3)
		{
			cout << "logged out" << endl;
			loginMenuDoctor();
		}
	}
	void courseMenuDoctor(int num, int b)
	{
		cout << endl << "Course Menu" << endl << "===========" << endl;
		cout << "1)list assignments" << endl;
		cout << "2)create assignment" << endl;
		cout << "3)back" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			//list assignments
			for (int i = 0; i < DA[num].getCourse(b).getAssignmentsList().size(); i++)
			{
				cout << i << ")" << DA[num].getCourse(b).getAssignment(i).getAssignmentName() << endl;
			}
			cout << "choose the correspondent assignment number to view assignment" << endl;
			int c;
			cin >> c;
			assignmentMenuDoctor(num, b, c);
		}
		else if (a == 2)
		{
			//create assignment
			cout << "assignment name: ";
			string assignmentName;
			cin >> assignmentName;
			DA[num].getCourse(b).createAssignment(assignmentName);
			courseMenuDoctor(num, b);
		}
		else if (a == 3)
		{
			//back
			mainMenuDoctor(num);
		}
	}
	void assignmentMenuDoctor(int num, int b, int c)
	{
		cout << endl << "Assignment Menu" << endl << "===============" << endl;
		cout << "1)show info" << endl;
		cout << "2)show grades report" << endl;
		cout << "3)list solutions" << endl;
		cout << "4)back" << endl;

		Assignment& assignment = DA[num].getCourse(b).getAssignment(c); //must be declared as a reference in order to change in it

		int a;
		cin >> a;
		if (a == 1)
		{
			//show info
			cout << "assignment name: " << DA[num].getCourse(b).getAssignment(c).getAssignmentName() << endl;
			assignmentMenuDoctor(num, b, c);
		}
		else if (a == 2)
		{
			//show grades report
			for (int i = 0; i < assignment.getSolutionList().size(); i++)
				cout << assignment.getSolution(i).getSubmitter() << "'s grade is: " << assignment.getSolution(i).getGrade() << endl;
			assignmentMenuDoctor(num, b, c);
		}
		else if (a == 3)
		{
			//list solutions
			for (int i = 0; i < assignment.getSolutionList().size(); i++)
				cout << i << ")" << assignment.getSolution(i).getSubmitter() << endl;
			cout << "choose the correspondent solution number to view solution" << endl;
			/*choosing solution*/
			int d;
			cin >> d;
			solutionMenuDoctor(num, b, c, d);
		}
		else if (a == 4)
		{
			//back
			courseMenuDoctor(num, b);
		}
	}
	void solutionMenuDoctor(int num, int b, int c, int d)
	{
		cout << endl << "Solution Menu" << endl << "=============" << endl;
		cout << "1)show solution" << endl;
		cout << "2)set grade" << endl;
		cout << "3)set a comment" << endl;
		cout << "4)back" << endl;

		Solution& solution = DA[num].getCourse(b).getAssignment(c).getSolution(d);

		int a;
		cin >> a;
		if (a == 1)
		{
			//show solution
			cout << solution.getContent() << endl;
			solutionMenuDoctor(num, b, c, d);
		}
		else if (a == 2)
		{
			//set grade
			string s;
			cin >> s;
			solution.setGrade(s);
			solutionMenuDoctor(num, b, c, d);
		}
		else if (a == 3)
		{
			//set a comment
			string s;
			cin >> s;
			solution.setComment(s);
			solutionMenuDoctor(num, b, c, d);
		}
		else if (a == 4)
		{
			//back
			assignmentMenuDoctor(num, b, c);
		}

	}
	//student menus
	void loginMenuStudent()
	{
		cout << endl << "Login Menu" << endl << "==========" << endl;
		cout << "1)logIn" << endl << "2)register" << endl;
		int a;
		cin >> a;
		//taking input for logging in
		if (a == 1)
		{
			string userName;
			cout << "username: ";
			cin >> userName;
			//checking if the user name is available
			bool found = 0;
			int num;
			for (int i = 0; i < SA.size(); i++)
				if (userName == SA[i].getUserName())
				{
					found = 1;
					num = i;
					break;
				}
			if (found)
			{
				//checking password
				cout << "password: ";
				string password;
				cin >> password;
				if (password == SA[num].getPassword())
				{
					cout << "logged in successfully!" << endl;
					cout << "welcome, " << SA[num].getUserName() << endl;
					//logIn code
					mainMenuStudent(num);
				}
				else
				{
					cout << "password is not correct" << endl;
					loginMenuDoctor();
				}
			}
			else
			{
				cout << "user name is not valid" << endl;
				loginMenuStudent();
			}
		}
		//taking input for registering & checking it
		else if (a == 2)
		{
			cout << "register menu" << endl;
			cout << "user name: ";
			string userName;
			cin >> userName;

			bool failedUserName = 1;
			while (failedUserName)
			{
				failedUserName = 0;
				//checking that the user name does not match that of any other user;
				for (int i = 0; i < SA.size(); i++)
				{
					if (userName == SA[i].getUserName())
					{
						failedUserName = 1;
						break;
					}
				}

				//reprompting
				if (failedUserName)
				{
					cout << "user name already taken! Enter another user name" << endl;
					cout << "user name: ";
					cin >> userName;
				}
			}
			cout << "password: ";
			string password;
			cin >> password;

			//adding the new doctor to the array
			SA.push_back(Student(userName, password));
			loginMenuStudent();
		}

	};
	void mainMenuStudent(int num)
	{

	}
};

int main()
{
	//setting up dummy data
	/*adding doctor "amr"*/
	DA.push_back(Doctor("amr", "123"));
	/*adding courses for amr*/
	DA[0].createCourse("Math");
	DA[0].createCourse("Engineering Drawing");
	/*adding assignments for Math course*/
	DA[0].getCourse(0).createAssignment("integration by substitution assignment");
	DA[0].getCourse(0).createAssignment("integration by parts assignment");
	/*adding solutions to integration by substitution assignment*/
	Assignment& intBySubs = DA[0].getCourse(0).getAssignment(0);
	intBySubs.addSolution(Solution("Mahmoud","x+2=5","NA","not the correct answer!"));
	intBySubs.addSolution(Solution("Amr Fatouh","dy/dx(x)=1","20","good job!"));

	//running the program
	WelcomeMenu welcomeMenu;
	welcomeMenu.userTypeMenu();
}