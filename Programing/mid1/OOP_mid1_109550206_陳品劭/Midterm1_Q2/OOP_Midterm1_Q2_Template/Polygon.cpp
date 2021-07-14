#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

typedef struct pt {
	int x;
	int y;
} Point;

class Polygon
{
private:
	vector<Point> points; // all the points of the polygon
	float perimeter; // the polygon's perimeter
	float area; // the polygon's area

public:
	Polygon() {perimeter = 0; area = 0;}

	void set_coordinates(int x, int y) {
		// TODO: Read the coordinates of each point, and store them in "vector<Point> points".
		Point Input;
		Input.x = x;
		Input.y = y;
		points.push_back(Input);
	}
	
	float compute_area() const {
		// TODO: Compute the area.
		int length = points.size() - 1;
		float ans = points[length].x * points[0].y - points[0].x * points[length].y;
		for (int i = 0; i < length; i++) {
			ans += points[i].x * points[i + 1].y - points[i + 1].x * points[i].y;
		}
		ans /= 2;
		return ans;
	}
	
	float compute_perimeter() const {
		// TODO: Compute the perimeter.
		int length = points.size() - 1;
		float a = points[length].x - points[0].x;
		float b = points[length].y - points[0].y;
		float ans = a * a + b * b;
		ans = sqrt(ans);
		for (int i = 0; i < length; i++) {
			a = points[i].x - points[i + 1].x;
			b = points[i].y - points[i + 1].y;
			ans += sqrt(a * a + b * b);
		}
		return ans;
	}
	
	void set_perimeter(float &perim) {
		perimeter = perim;
	}
	
	void set_area(float &a) {
		area = a;
	}
	
	void print_coordinates() const {
		// TODO: Print the coordinates.
		// Format: (x0, y0) (x1, y1) ... (xn, yn).
		for (int i = 0; i < points.size(); i++) {
			cout << "(" << points[i].x << ", " << points[i].y << ") ";
		}
		cout << '\n';
	}
	
	void print_perimeter() const {
		// TODO: Print the perimeter.
		cout << perimeter << '\n';
	}
	
	void print_area() const {
		// TODO: Print the area.
		cout << area << '\n';
	}
	
	bool operator>(const Polygon &p) const {	
		// TODO: Overload the operator >.
		return this->area > p.area;
	}
	
	bool operator<(const Polygon &p) const {	
		// TODO: Overload the operator <.
		return this->area < p.area;
	}
	
	bool operator==(const Polygon &p) const {	
		// TODO: Overload the operator ==.
		return this->area == p.area;
	}
};

void compare_area(const Polygon &p1, const Polygon &p2)
{
	// Compare the area of two polygons, and print the result.
	if(p1 > p2) {
		cout << "p1 > p2" << endl;
	}
	
	else if(p1 < p2) {
		cout << "p1 < p2" << endl;
	}
	
	else {
		cout << "p1 = p2" << endl;
	}
}

int main()
{	
	fstream file;
	file.open("test_Q2.txt");
	if (!file) {
		cout << "Fail to open!\n";
		system("pause");
		exit(0);
	}
	
	Polygon p1, p2;
	
	// read input from text file
	int m, n;
	file >> m; // number of points
	
	// p1
	int x_coord, y_coord;
	for (int i=0; i<m; i++) {
		file >> x_coord >> y_coord;
		p1.set_coordinates(x_coord, y_coord);
	} 

	// p2
	file >> n; // number of points
	for (int i=0; i<n; i++) {
		file >> x_coord >> y_coord;
		p2.set_coordinates(x_coord, y_coord);
	}
	
	// print the coordinates
	p1.print_coordinates();
	p2.print_coordinates();
	
	// Compute the perimeter.
	float perimeter1, perimeter2;
	perimeter1 = p1.compute_perimeter();
	perimeter2 = p2.compute_perimeter();	
	p1.set_perimeter(perimeter1);
	p2.set_perimeter(perimeter2);
	
	// print the perimeter
	cout << "p1 perimeter = ";
	p1.print_perimeter();
	cout << "p2 perimeter = ";
	p2.print_perimeter();
	
	// Compute the area.
	float area1, area2;
	area1 = p1.compute_area();
	area2 = p2.compute_area();
	p1.set_area(area1);
	p2.set_area(area2);	
	
	// print the area
	cout << "p1 area = ";
	p1.print_area();
	cout << "p2 area = ";
	p2.print_area();
	
	// Compare the two polygons.
	compare_area(p1, p2);
	
	system("pause");
	return 0;
} 
