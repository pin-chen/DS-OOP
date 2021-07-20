#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void swap(int& a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void sort_Heap(vector<int>& arr, int size){
	if(size <= 0) return;
	size--;
	swap(arr[size], arr[0]);
	//
	int index = 0;
	while(index * 2 + 1 < size){
		int Max_child = index * 2 + 1;
		if(index * 2 + 2 < size)
			if(arr[Max_child] < arr[index * 2 + 2])
				Max_child = index * 2 + 2;
		if(arr[index] < arr[Max_child]){
			swap(arr[index], arr[Max_child]);
			index = Max_child;
		}else{
			break;
		}
	}
	//
	sort_Heap(arr, size);
}

void intsert_Heap(int& x, vector<int>& arr){
	arr.push_back(x);
	int index = arr.size() - 1;
	while(index){
		int parent = (index - 1) / 2;
		if(arr[index] > arr[parent]){
			swap(arr[index], arr[parent]);
		}else{
			break;
		}
		index = parent;
	}
}

int main(){
	fstream  file;
	//
	file.open("demo.txt");
	if (!file.is_open()) {
		cout << "Failed to open file!" << endl;
		return 0;
	}
	//
	vector<int> arr;
	int n;
	file >> n;
	//cout << n;
	for(int i = 0; i < n; i++){
		int x;
		file >> x;
		intsert_Heap(x, arr);
	}
	//
	sort_Heap(arr, n);
	//
	for(int i = 0; i < arr.size(); i++){
		cout << arr[i] << " ";
	}
	cout<< '\n';
	//system("PAUSE");
	return 0;
} 
