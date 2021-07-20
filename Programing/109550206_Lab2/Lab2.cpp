#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor;
	
public:
	PrimeFactorization() {
		//TO_DO: initial constructor
		num1 = 1;
		num2 = 1;
	}
	PrimeFactorization(int _a, int _b) {
		//TO_DO: _a means the first integer and _b means the second integer
		num1 = _a;
		num2 = _b;
	}
	void Get_Prime_Factorization() {
		//TO_DO: Prime factorization num1 and num2, push result to the num1_factor and num2_factor.
		int factor = 2;
		while (num1 > 1){
			while( num1 % factor == 0 ){
				num1_factor.push_back(factor);
				num1 /= factor;
			}
			factor % 2 ? factor += 2 : factor += 1;
		}
		factor = 2;
		while (num2 > 1){
			while( num2 % factor == 0 ){
				num2_factor.push_back(factor);
				num2 /= factor;
			}
			factor % 2 ? factor += 2 : factor += 1;
		}
	}

	void Print_Prime_Factorization() {
		//TO_DO: Print num1_factor and num2_factor.
		cout << "num1_Prime_factor : \"";
		for ( int i = 0; i < num1_factor.size(); ++i) {
			cout << num1_factor[i] << " ";
		}
		cout << "\"\n";
		cout << "num2_Prime_factor : \"";
		for ( int i = 0; i < num2_factor.size(); ++i) {
			cout << num2_factor[i] << " ";
		}
		cout << "\"\n";
	}

	void Print_GCD() {
		//TO_DO: Use num1_factor and num2_factor to find GCD and print the result.
		int ans = 1, i = 0, j = 0;
		while(i < num1_factor.size() && j < num2_factor.size() ){
			if ( num1_factor[i] == num2_factor[j] ){
				ans *= num1_factor[i];
				++i;
				++j;
			}else if ( num1_factor[i] > num2_factor[j] ){
				++j;
			}else {
				++i;
			}
		}
		cout << "GCD: " << ans << '\n';
	}

	void Input(){
		cin >> num1 >> num2;
	}

	void Show(){
		cout << "num1 = " << num1 << '\n';
		cout << "num2 = " << num2 << '\n';
	}
};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		//PrimeFactorization PF;

		//PF.Input();
		int a, b;
		cin >> a >> b;

		//PF.Show();
		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);

		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD();

		cout << endl;

	}

	system("PAUSE");
	return 0;
}
