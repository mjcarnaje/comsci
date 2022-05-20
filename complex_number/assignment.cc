/*
CCC102 Laboratory Assignment No. 1
Due: May 23, 2022 (Monday) at 11:55PM

This is the sample program that tests the implementation of the complex
number abtract data type (ADT). You may freely modify this file.
Modifications in this file will not be scored.

Provide the missing implementations of the complex number ADT in the
corresponding definitions file "complex.cc".

To test your implementation, you need to compile this file together with
the complex number ADT module. To compile the program using a C++
project, create a C++ console application project and add the three
files ("assignment1.cc", "complex.cc", and "complex.hh") into the
project. To compile the program using the GCC compiler in the command
line, invoke GCC using the command "gcc -o assignment1 assignment1.cc
complex.cc".

You must submit the whole homework package with your
modifications/additions in the electronic submission. This homework must
comply with the homework policy as stated in the "Assignments" page.
*/

#include <iostream>
#include "complex.hh"

using namespace std;

/*
This is the main function for testing the implementation of the
Complex class. This function is not scored and may be freely modified.
*/
int main(void)
{
    Complex a, b, c;

    cout << "Enter two complex numbers in the format (real, imaginary): " << endl;
    cout << "Real part of first complex number: ";
    cin >> a;
    cout << "Imaginary part of first complex number: ";
    cin >> b;

    cout << "============================================================" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    c = a + b;
    cout << "c = a + b = " << c << endl;

    c = a - b;
    cout << "c = a - b = " << c << endl;

    c = a * b;
    cout << "c = a * b = " << c << endl;

    c = a / b;
    cout << "c = a / b = " << c << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    c = a;
    cout << "c = a = " << c << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    c += b;

    cout << "c += b = " << c << endl;

    c = a;
    c -= b;
    cout << "c -= b = " << c << endl;

    c = a;
    c *= b;
    cout << "c *= b = " << c << endl;

    c = a;
    c /= b;
    cout << "c /= b = " << c << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    c = a;
    if (c == a)
    {
        cout << c << " is equal to " << a << endl;
    }

    if (c != b)
    {
        cout << c << " is not equal to " << b << endl;
    }
    else
    {
        cout << c << " is equal to " << b << endl;
    }
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    cout << "Magnitude of a = " << a.magnitude() << endl;
    cout << "Magnitude of b = " << b.magnitude() << endl;
    cout << "Magnitude of c = " << c.magnitude() << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    cout << "Conjugate of a = " << a.conjugate() << endl;
    cout << "Conjugate of b = " << b.conjugate() << endl;
    cout << "Conjugate of c = " << c.conjugate() << endl;
    cout << "============================================================" << endl;

    cout << "============================================================" << endl;
    cout << "Inverse of a = " << a.inverse() << endl;
    cout << "Inverse of b = " << b.inverse() << endl;
    cout << "Inverse of c = " << c.inverse() << endl;
    cout << "============================================================" << endl;

    return 0;
}
