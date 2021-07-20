#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct info {
	int height;
	int weight;

	// don't change this
	bool operator<(const info& other) const {
		return height < other.height;
	}
};

//TODO: implement three comparsion function 
//example: 
//bool functionName(const dataType& p1, const dataType& p2) {
//	return p1 > p2;
//}
typedef pair<string, info> dataType;
//1.implement compare by height here
bool compare_by_height(const dataType& p1, const dataType& p2) {
	return p1.second < p2.second;
}
//2.implement compare by weight here
bool compare_by_weight(const dataType& p1, const dataType& p2) {
	return p1.second.weight < p2.second.weight;
}
//3.implement compare by height and weight here
bool compare_by_height_and_weight(const dataType& p1, const dataType& p2) {
	if(p1.second.height == p2.second.height)
		return p1.second.weight < p2.second.weight;
	return p1.second.height < p2.second.height;
}

class Map
{
public:
	Map()
	{
		people.clear();
	}

	void readFile() {
		fstream file;
		file.open("test.txt", ios::in);
		int cmdNum;
		file >> cmdNum;

		while (cmdNum--) {
			char cmd;
			file >> cmd;
			switch (cmd) {
				case 'a':
				{
					string name;
					file >> name;
					info ii;
					file >> ii.height >> ii.weight;
					add(name, ii);
					break;
				}
				case 'f':
				{
					string name;
					file >> name;
					find(name);
					break;
				}
				case 'e':
				{
					string name;
					file >> name;
					erase(name);
					break;
				}
			}
		}

		file.close();
	}

	void add(string name, info& _info) {
		//TODO: implement add function add new data into the map(vector<pair<...>>)
		//If the name is already in the map, override his/her data
		bool not_found = true;
		vector<pair<string, info>>::iterator it;
		for(it = people.begin(); it != people.end(); it++){
			if( it -> first == name){
				not_found = false;
				cout << it->first << "'s h: " << it->second.height << " and w: " << it->second.weight << " is changed to "; 
				it->second.height = _info.height;
				it->second.weight = _info.weight;
				cout << "h: " << it->second.height << " and w: " << it->second.weight << '\n'; 
				break;
			}
		}
		if(not_found){
			//pair<string, info> input(name, _info);
			people.push_back(make_pair(name, _info));
		}
	}

	void find(string name) {
		//TODO: implement find function to get the information of the given name if the name exist
		//otherwise, print "name is not found"
		//you must use iterator to implement
		bool not_found = true;
		vector<pair<string, info>>::iterator it;
		for(it = people.begin(); it != people.end(); it++){
			if( it -> first == name){
				not_found = false;
				cout << it->first << " is found! h: " << it->second.height << " and w: " << it->second.weight << '\n';
				break;
			}
		}
		if(not_found) cout << name << " is not found!" << '\n';
	}

	void erase(string name) {
		//TODO: implement erase function to delete the element of the given name if the name exist
		//otherwise, print "name is not found"
		//you must use iterator to implement
		bool not_found = true;
		vector<pair<string, info>>::iterator it;
		for(it = people.begin(); it != people.end(); it++){
			if( it -> first == name){
				not_found = false;
				cout << it->first << " is erased!" <<'\n';
				people.erase(it);
				break;
			}
		}
		if(not_found) cout << name << " is not found!" << '\n';
	}

	void sortByName() {
		//TODO: call sort() function (default one)
		if(people.size() == 1) return;
		sort(people.begin(), people.end());
	}

	void sortByInfo(const char* type) {

		if (type == "H") {
			//TODO: call sort() function and compare by height
			sort(people.begin(), people.end(), compare_by_height);
		}
		else if (type == "W") {
			//TODO: call sort() function and compare by weight
			sort(people.begin(), people.end(), compare_by_weight);
		}
		else if (type == "HW") {
			//TODO: call sort() function and compare by height and weight
			sort(people.begin(), people.end(), compare_by_height_and_weight);
		}
	}

	void write(fstream& file) {
		//TODO: Write all elements in the map to the file
		//you must use iterator to implement
		vector<pair<string, info>>::iterator it;
		for(it = people.begin(); it != people.end(); it++){
			file << it->first << ":\t" << it->second.height << ",\t" << it->second.weight << "\n";
		}
		file << "\n";
	}

	void writeFile() {
		fstream file;
		file.open("lab7.txt", ios::out);

		file << "Sort By Name\n";
		sortByName();
		write(file);
		file << "Sort By Height\n";
		sortByInfo("H");
		write(file);
		file << "Sort By Weight\n";
		sortByInfo("W");
		write(file);
		file << "Sort By Height&Weight\n";
		sortByInfo("HW");
		write(file);

		cout << "File lab7.txt saved!\n";
		file.close();
	}

private:
	vector<pair<string, info>> people;
};

int main() {
	Map myMap;

	myMap.readFile();
	myMap.writeFile();

	system("pause");
	return 0;
}