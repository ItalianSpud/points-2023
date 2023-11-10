//
// Created by ryanj on 11/9/2023.
//
#include <cassert>
#include <sstream>
#include "PointList.h"

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
    PointList correctList(5);
    data.clear();
    data.str(
            "4 -5\n"
            "10 10\n"
            "1 10\n"
            "0 1\n"
            "0 0\n"
    );
    correctList.Read(data);
    PointList hull = test.ConvexHull();
    assert(hull.Equals(correctList)); // base test
    data.clear();
    data.str(
            "-100 -100\n"
            "100 100\n"
            "0 0\n"
            "1 1\n"
            "100 0\n"
            "-1000 0\n"
            "-1 1\n"
            "-2 2\n"
            "3 3\n"
            "5 -19\n"
    );
    PointList test2(20);
    test2.Read(data);
    data.clear();
    data.str("-100 -100\n"
             "100 100\n"
             "100 0\n"
             "-1000 0\n");
    hull = test2.ConvexHull();
    PointList correctList2(4);
    correctList2.Read(data);
    assert(hull.Equals(correctList2)); // Test with not full list
    return 0;


}

