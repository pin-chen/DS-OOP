#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
using namespace std;

class Roll_Call_System {

private:
	vector<string> studentNames;
	vector<string> pickedStudentNames;
	int seed;
	int a;
	int c;
	int m;

public:
	fstream fin;

	void OpenFile() {
		//TODO: open the file
		fin.open("demo.txt");
		cout << "Filename: demo.txt" << '\n';
	}

	void AddNames() {
		//TODO : add name to studentName vector
		int num;
		fin >> num;
		string s;
		studentNames.clear();
		for(int i = 0; i < num; ++i){
			fin >> s;
			studentNames.push_back(s);
		}
	}

	int GenerateRandomNumber() {
		//TODO: implement linear random number generator
		seed = (a * seed + c) % m;
		return seed;
	}

	void PickNames() {
		//TODO: randomly pick name form studentName vector
		//		and add them to pickedStudentName vector
		int pick_student_num;
		fin >> seed >> a >> c >> m >> pick_student_num;
		pickedStudentNames.clear();
		for(int j = 0; j < pick_student_num; ++j){
			int x = GenerateRandomNumber();
			pickedStudentNames.push_back( studentNames[x] );
		}
	}

	void PrintPickedStudentNames() {
		//TODO: print all picked name form studentName vector
		cout << "Picked Name:" << '\n';
		for(int i = 0; i < pickedStudentNames.size(); ++i){
			cout << pickedStudentNames[i] << '\n';
		}
	}

	void CaculateAlphabets() {
		//TODO: calculate how many diffetent alphabets are used and print it
		set<char> alphabets;
		for(int i = 0; i < pickedStudentNames.size(); ++i){
			for(int j = 0; j < pickedStudentNames[i].size(); ++j){
				alphabets.insert( tolower( pickedStudentNames[i][j] ) );
			}
			
		}
		cout << "Total alphabets: " << alphabets.size() << '\n' << '\n';
	}

};

int main() {
	
	Roll_Call_System rcs;
	rcs.OpenFile();
	rcs.AddNames();

	int times;
	rcs.fin >> times;
	while (times--) {
		rcs.PickNames();
		rcs.PrintPickedStudentNames();
		rcs.CaculateAlphabets();
	}
	
	system("PAUSE");
	return 0;

}
