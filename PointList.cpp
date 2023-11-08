//
// Created by ryanj on 10/27/2023.
//

#include "PointList.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

PointList::~PointList() {
    for (int i = 0; i < _filled; i++) {
        delete _list[i];
    }
    delete[] _list;
}

PointList::PointList(const PointList &original) : _size(original._size), _filled(original._filled) {
    _list = new Point*[original._size];
    for (int i = 0; i < _size; i++) {
        _list[i] = new Point(original._list[i]->GetX(), original._list[i]->GetY());
    }
}

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

PointList::PointList(size_t size) {
    _size = size;
    _filled = 0;
    _list = new Point*[size];
}

void PointList::Read(istream &input) {
    string temp;
    size_t x = _size - _filled;
    for (int i = 0; i < x; i++) {
        _filled++;
        _list[i] = new Point(0, 0);
        _list[i]->Read(input);
    }
}

void PointList::Write(ostream &output) {
    for (int i = 0; i < _filled; i++) {
        _list[i]->Write(output);
        output << endl;
    }
}

Point PointList::At(size_t index) const {
    return *_list[index];
}

string PointList::ToString() const {
    string result;
    for (int i = 0; i < _filled; i++) {
        result += _list[i]->ToString();
    }
    return result;
}


PointList PointList::ConvexHull() const {
    if (_filled <= 3) {
        return *this;
    }
    PointList resultList = *this;
    double minY = _list[0]->GetY();
    int anchorIndex = 0;
    for (int i = 0; i < _filled; i++) {
        if (_list[i]->GetY() < minY) {
            anchorIndex = i;
            minY = _list[i]->GetY();
        }
    }
    resultList.SortByAngle(anchorIndex);
    //resultList.Write(cout);

    for (int i =0; i < resultList._filled - 2; i++) {
        if (!(resultList._list[i]->InwardsAngle(*resultList._list[i + 1], *resultList._list[i + 2]))) {
            resultList.RemovePoint(i + 1);
            i--;
        }
    }
    return resultList;
}

void PointList::RemovePoint(size_t index) {
    if (index < _filled) {
        delete _list[index];
        for (int x = index + 1; x < _filled; x++) {
            _list[x - 1] = _list[x];
        }
        _filled--;
    }
}

void PointList::SortByAngle(size_t anchorIndex) {
    Swap(anchorIndex, 0);

    int minIndex = 1;
    double minAngle = At(0).Angle(At(1));
    for (int i = 1; i < _filled; i++) {
        for (int j = i; j < _filled; j++) {
            if (minAngle > At(0).Angle(At(j))) {
                minIndex = j;
                minAngle = At(0).Angle(At(j));
            }
        }
        Swap(i, minIndex);
        minIndex = i + 1;
        if (i == _filled - 1)
            break;
        minAngle = At(0).Angle(At(i + 1));
    }
}

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
