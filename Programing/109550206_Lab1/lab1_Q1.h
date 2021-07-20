#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

class QUADRATIC
{
	public:
		QUADRATIC() : a(0), b(0), c(0) {}
		QUADRATIC(int a, int b, int c) : a(a), b(b), c(c) {}
		void add(QUADRATIC q);
		void discriminant();

		int a;
		int b;
		int c;

		void print();

		void show();
		void input();
};

#endif // QUADRATIC_H_INCLUDED