// array_and_struct_example.cpp

#include "cmpt_error.h"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

// By defeualt, everything is public in a struct.
struct Point {
	int x, y;

	// Default constructor (takes no inputs)
	Point()
	: x(0), y(0)
	{ }

	Point(int a, int b)
	: x(a), y(b)
	{ }

	// Copy constructor: makes a copy of another Point object
	Point(const Point& other)
	:x(other.x), y(other.y)
	{ }

	// Every C++ object has a special pointer that points to the object itself
	double dist(const Point& other) {
		double dx = this->x - other.x;
		double dy = this->y - other.y;
		return sqrt(dx*dx + dy*dy);
	}
}; // Struct Point

void print(const Point& p) {
	cout << "(" << p.x << ", " << p.y << ")";
}

void println(const Point& p) {
	print(p);
	cout << "\n";
}

void test1() {
	Point origin;			// Create point origin with default constructor
		Point p{-2, 4};		// Create Point p with inputs
		Point q{p};			// Use copy constructor to create q, a copy of p

		println(origin);
		println(p);
		println(q);

		cout << "dist(p, origin): " <<  p.dist(origin) << "\n";
}



class Intvec {
private:
	int* arr; // Pointer to the underlying array
	int cap; // Capacity of the underlying array, ie its size
	int sz; // Number of elements in the array

	// Double the capacity of the underlying array
	void resizeArray() {
		cap = 2 * cap;

		// Make the new array
		int* newArr = new int[cap];

		// Copy elements to the new array
		for(int i = 0; i < sz; ++i) {
			newArr[i] = arr[i];
		}

		// Delete
		delete[] arr;

		// Set up the new array
		arr = newArr;
	}

public:
	// Default constructor that creates an empty array of size 0.
	// The initial capacity of 10 is just a guess
	Intvec()
	: cap(10), sz(0)
	{
		arr = new int[cap];
	}

	// This destructor is called automatically when an Intvec is deleted or
	// Leaves scope.

	~Intvec() {
		delete[] arr; //note the use of []
	} 

	// Some of the following functions have "const" before their bodies. This 
	// indicates that the function does not modify the object. In other words, 
	// using "const" like this makes the function read-only.
	bool empty() {
		return sz == 0;
	}

	int size() const {
		return sz;
	}

	int capacity() const {
		return cap;
	}

	int get(int i) const {
		if (i < 0 || i >= sz) cmpt::error("get: index out of bounds");
		return arr[i];
	}

	void set(int i, int x) {
		if (i < 0 || i >= sz) cmpt::error("set: index out of bounds");
		arr[i] = x;
	}

	// Add x to the end of this Intvec, re-sizing the underlying array if
	// necessary.
	void append(int x) {
		if (sz >= cap) {
			resizeArray();
		}
		arr[sz] = x;
		sz++;
	}

	void print() const {
		cout << "[";
		for(int i = 0; i < sz; ++i) {
			cout << arr[i] << " ";
		}
		cout << "]";
	}

	void prinln() const {
		print();
		cout << "\n";
	}

}; // Class Intvec

void test2() {
	Intvec v;
	assert(v.size() == 0);
	assert(v.empty());

	for(int i = 1; i <= 11; ++i) {
		v.append(i);
		v.print();
		cout << " size=" << v.size() << ", cap=" << v.capacity() << "\n";
	}
}

int main() {
	//test1();
	test2();
}