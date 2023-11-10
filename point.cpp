//
// Created by Carlos R. Arias on 10/27/23.
//

#include "point.h"

#include <sstream>
#include <iostream>
#include <cmath>

using std::string;
using std::stringstream;
using std::ostream;
using std::istream;

// constructor for point
Point::Point(double x, double y): _x(x), _y(y) {

}

// ToString method, returns string representation of point
string Point::ToString() const {
    stringstream ss;
    ss << "[" << _x << ", " << _y << "]";
    return ss.str();
}

// use distance formula to find distance between two points
double Point::Distance(const Point &point) const {
    return sqrt(pow(_x - point._x, 2.0) + pow(_y - point._y, 2.0));
}

// check if one point equals another
bool Point::Equals(const Point& comparePoint) const {
    if (_x == comparePoint.GetX() && _y == comparePoint.GetY()) {
        return true;
    }
    return false;
}

// return x value
double Point::GetX() const {
    return _x;
}

// and y value
double Point::GetY() const {
    return _y;
}

// Get angle of one point compared to another.
// utilizes cmath's atan2 function
double Point::Angle(const Point& point) const {
    double adjacent = point.GetX() - _x, opposite = point.GetY() - _y; // get opposite and adjacent legs
    double angle = atan2(opposite, adjacent) * (180/3.141592653589); // utilize arctangent to get angle, multiply radian value by 180/PI to convert to degrees
    return angle;
}

// check if three points form an inwards facing (convex) angle or outwards facing (concave) angle
// utilizes cross product of the three points and sees if it is positive or negative. If positive, return true if negative return false
bool Point::InwardsAngle(const Point& point1, const Point& point2) const {
    double dotX1 = point1.GetX() - _x;
    double dotY1 = point1.GetY() - _y;
    double dotX2 = point2.GetX() - point1.GetX();
    double dotY2 = point2.GetY() - point1.GetY();
    return dotX1 * dotY2 - dotY1 * dotX2 > 0;
}

// write to output
void Point::Write(ostream &output) const {
    output << ToString();
}

// read from input
void Point::Read(istream &input) {
    input >> _x >> _y;
}

