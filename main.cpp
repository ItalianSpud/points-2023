#include "point.h"
#include "PointList.h"
#include <iostream>
#include <sstream>
#include <cassert>


using std::cout;
using std::cin;
using std::endl;
using std::stringstream;


int main() {
    cout << "Enter number of points: ";
    int size;
    cin >> size;
    PointList list(size);
    cout << "Enter points, separate by spaces and new lines: ";
    list.Read(cin);
    cout << "The convex hull of this list of points is: " << endl;
    list.ConvexHull().Write(cout);
    return 0;


}

