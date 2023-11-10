//
// Created by Ryan Fecarotta
//

#include "PointList.h"
#include <iostream>

using std::cout;
using std::endl;

// We need a destructor for list
PointList::~PointList() {
    for (int i = 0; i < _filled; i++) {
        delete _list[i];
    }
    delete[] _list;
}

// copy constructor for point list
PointList::PointList(const PointList &original) : _size(original._size), _filled(original._filled) {
    _list = new Point*[original._size];
    for (int i = 0; i < _size; i++) {
        _list[i] = new Point(original._list[i]->GetX(), original._list[i]->GetY());
    }
}

// copy assignment operator for pointlist
PointList &PointList::operator=(const PointList &original) {
    if (&original == this) {
        cout << "No self-assignment allowed!";
        return *this;
    }
    _size = original._size;
    _list = new Point*[original._size];
    _filled = original._filled;
    for (int i = 0; i < _filled; i++) {
        _list[i] = new Point(original._list[i]->GetX(), original._list[i]->GetY());
    }
    return *this;
}

// create a blank pointList object given a size
PointList::PointList(size_t size) {
    _size = size;
    _filled = 0;
    _list = new Point*[size];
}

// check if one list equals another
// criterion for equaling is if every element is the same
// utilizes Point::Equals method
bool PointList::Equals(const PointList& compareList) const {
    if (_filled != compareList._filled) {
        return false;
    }
    bool present = false;
    for (int i = 0; i < _filled; i++) {
        for (int j = 0; j < _filled; j++) {
            if (At(i).Equals(compareList.At(i))) {
                present = true;
            }
        }
        if (!present) {
            return false;
        }
    }
    return true;
}

// Read from input
void PointList::Read(istream &input) {
    string temp;
    size_t x = _size - _filled;
    for (int i = 0; i < x; i++) {
        _filled++;
        _list[i] = new Point(0, 0);
        _list[i]->Read(input);
    }
}

// Write to output
void PointList::Write(ostream &output) {
    for (int i = 0; i < _filled; i++) {
        _list[i]->Write(output);
        output << endl;
    }
}

// return Point at given index.
// utilizes while loops to deal with indexes that are too high or too low by starting from the other end of the list
Point PointList::At(size_t index) const {
    while (index >= _filled) {
        index -= _filled;
    }
    while (index < 0) {
        index += _filled;
    }
    return *_list[index];
}

// return string representation of pointlist
// utilizes Point::ToString method
string PointList::ToString() const {
    string result;
    for (int i = 0; i < _filled; i++) {
        result += _list[i]->ToString();
    }
    return result;
}

// Return PointList representing convex hull of our list
// utilizes many helper functions
// to find ConvexHull we use the Graham Scan algorithm.
// in English, that means we sort list by angle compared to a point we know is on the hull before checking if each three points make a convex angle, removing any points that don't fit that.

PointList PointList::ConvexHull() const {
    if (_filled <= 3) { // if list is this small, return obvious result
        return *this;
    }
    PointList resultList = *this; // this will be the list we return. It begins as just a copy of our list, we will shear off the unnecessary points later
    double minY = _list[0]->GetY();
    int anchorIndex = 0;
    for (int i = 0; i < _filled; i++) {
        if (_list[i]->GetY() < minY) {
            anchorIndex = i; // find a point we know is on the hull, in this case the lowest point in our list.
            minY = _list[i]->GetY();
        }
    }

    resultList.SortByAngle(anchorIndex); // call our sort by angle function with the lowest point as our anchor point.

    for (int i =0; i < resultList._filled - 2; i++) { // this loop body is the main thing we're doing. this loop moves along our list
        if (!(resultList._list[i]->InwardsAngle(*resultList._list[i + 1], *resultList._list[i + 2]))) {  // Here, we can see if our three points make an inwards or outwards angle
            resultList.RemovePoint(i + 1); // if it's an outwards facing angle we remove the midpoint between them
            i--;
        } // now we should have a completely convex set of points, which gives us our desired hull!
    }
    return resultList; // return hull!
}

// this is a function to remove any point at an index
void PointList::RemovePoint(size_t index) {
    if (index < _filled) { // check if we have a point at the given index first
        delete _list[index]; // delete the point at that index
        for (int x = index + 1; x < _filled; x++) {
            _list[x - 1] = _list[x]; // move every other element in the list back one spot to make up for our empty part of the list
        }
        _filled--; // decrement _filled, our tracker of the current number of points in the list
    }
}

// Private helper function to sort list by angle compared to an anchor index
void PointList::SortByAngle(size_t anchorIndex) {
    Swap(anchorIndex, 0); // move our anchor index to the start so it can easily act as our anchor.

    for (int i = 1; i < _filled; i++) {
        int minIndex = i; // set up min Index tracker
        double minAngle = At(0).Angle(At(i)); // and min angle tracker
        for (int j = i; j < _filled; j++) { // selection sort, using Point::Angle method as our sorter
            if (minAngle > At(0).Angle(At(j))) { // we know that 0, our first element, is our anchor index, so we just check the angles based on that, looking for min angle
                minIndex = j;
                minAngle = At(0).Angle(At(j));
            }
        }
        Swap(i, minIndex); // swap minAngle to our current index in the list and continue loop.
    }
}

// Private helper function to swap two points.
void PointList::Swap(size_t index1, size_t index2) {
    if (index1 > _filled || index2 > _filled) {
        return;
    }
    if (index1 == index2) {
        return;
    }
    Point* temp = _list[index1];
    _list[index1] = _list[index2];
    _list[index2] = temp;

}
