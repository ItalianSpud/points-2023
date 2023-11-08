#include "point.h"
#include "PointList.h"
#include <iostream>
#include <sstream>



using std::cout;
using std::endl;
using std::stringstream;


int main() {
    stringstream data(
            "11\n"
            "0 0\n"
            "1 10\n"
            "4 0\n"
            "10 10\n"
            "1 1\n"
            "0 1\n"
            "3 2\n"
            "1 9\n"
            "5 -1\n"
            "5 1\n"
            "4 -5"
            );
    int size;
    data >> size;
    PointList test(size);
    test.Read(data);
    PointList hull = test.ConvexHull();
    hull.Write(cout);
    return 0;


}

