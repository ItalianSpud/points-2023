//
// Created by Carlos R. Arias on 10/27/23.
//

#include "point.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using std::acos;
using std::abs;

Point::Point(double x, double y): _x(x), _y(y) {

}

string Point::ToString() const {
    stringstream ss;
    ss << "[" << _x << ", " << _y << "]";
    return ss.str();
}

double Point::Distance(const Point &point) const {
    return sqrt(pow(_x - point._x, 2.0) + pow(_y - point._y, 2.0));
}

double Point::GetX() const {
    return _x;
}

double Point::GetY() const {
    return _y;
}

double Point::Angle(const Point& point) const {
    double adjacent = point.GetX() - _x, opposite = point.GetY() - _y;
    double angle = atan2(opposite, adjacent) * (180/3.141592653589);
    return angle;

}

bool Point::InwardsAngle(const Point& point1, const Point& point2) const {
    double dotX1 = point1.GetX() - _x;
    double dotY1 = point1.GetY() - _y;
    double dotX2 = point2.GetX() - point1.GetX();
    double dotY2 = point2.GetY() - point1.GetY();
    return dotX1 * dotY2 - dotY1 * dotX2 > 0;
}



void Point::Write(ostream &output) const {
    output << _x << " " << _y;
}

void Point::Read(istream &input) {
    input >> _x >> _y;
}

