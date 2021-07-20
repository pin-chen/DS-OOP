#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class matrix
{
private:
	vector<vector<int> > M;
public:
	
	matrix()
	{
		//TO_DO: Initialize a matrix of size 3 * 3
		M.clear();
		Initialize(M);
	}
	
	matrix(vector<vector<int> >& m)
	{
		M = m;
	}
	
	//Initialize
	void Initialize(vector<vector<int> >& arr){
		arr.resize(3);
		for(int i = 0; i < 3; ++i)
			arr[i].resize(3);
	}
	// TO_DO: Implement a function to multiply two matrices.
	void multiply(vector<vector<int> >& adj)
	{
		vector<vector<int> > mul;
		Initialize(mul);
		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 3; ++j){
				for(int k = 0; k < 3; ++k){
					mul[i][j] += M[i][k] * adj[k][j];
				}
			}
		}
		M.clear();
		M = mul;
	}
	// TO_DO: Implement a function to calculate the classic adjoint matrix.
	vector<vector<int> > CalculateAdjoint()
	{
		vector<vector<int> > adj;
		Initialize(adj);
		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 3; ++j){
				adj[j][i] = cofactor(i, j);
			}
		}
		return adj;
	}
	// TO_DO: Implement a function to calculate the determinant.
	void determinant()
	{
		cout << "The determinant of matrix M is: " << M[0][0] <<'\n'; 
	}
	//calculate cofator
	int cofactor(int i, int j)
	{
		int cof[4] = {}, t = 0;
		for(int g = 0; g < 3; ++g){
			if(g == i) continue;
			for(int h = 0; h < 3; ++h){
				if(h == j) continue;
				else{
					cof[t++] = M[g][h];
					if(t > 3) break;
				}
			}
			if(t > 3) break;
		}
		if( (i + j) % 2)
			return (-1) * ( cof[0] * cof[3] - cof[1] * cof[2] );
		else		
			return cof[0] * cof[3] - cof[1] * cof[2];
	}
};

int main() 
{
	fstream fin;
	
	fin.open("testcase.txt", ios::in);
	if (!fin) {
		cout << "not open" << endl;
		exit(0);
	}
	
	int n;
	fin >> n;
	
	for(int r=0; r<n; r++) {
		////////////////////////
		// TO_DO: read the input and call the functions you've implemented to generate the output
		vector<vector<int> > arr;
		arr.resize(3);
		
		for(int i = 0; i <  3; ++i){
			
			arr[i].resize(3);
			for(int j = 0; j < 3; ++j){
				fin >> arr[i][j];
			}
		}
		
		matrix M(arr);
		
		vector<vector<int> > adj;
		adj = M.CalculateAdjoint();
		
		M.multiply(adj);
		M.determinant();
		
		arr.clear();
		////////////////////////
	}
	system("PAUSE");
	return 0;
}
