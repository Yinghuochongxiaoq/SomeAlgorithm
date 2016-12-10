#pragma once
#include <iostream>
using namespace std;

class Base
{
public:
	int m_base;
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
};

class VirtualClassNote: Base
{
public:
	int m_derived;
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g() { cout << "Derive::g" << endl; }
	void VirtualMathRead();
};

