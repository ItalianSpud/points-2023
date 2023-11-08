//
// Created by ryanj on 10/27/2023.
//

#ifndef THE_POINTS_2023_POINTLIST_H
#define THE_POINTS_2023_POINTLIST_H

#include <cstdlib>
#include "point.h"
#include <istream>
#include <ostream>
#include <string>
#include <sstream>

using std::istream;
using std::ostream;
using std::stringstream;
using std::string;

class PointList {
private:
    size_t _size;
    int _filled;
    Point** _list;
    void Swap(size_t index1, size_t index2);
    void SortByAngle(size_t anchorIndex);
public:
    ~PointList();
    PointList(const PointList& original);
    PointList& operator=(const PointList& original);
    PointList(size_t size);
    Point At(size_t index) const;
    void Read(istream& input);
    void Write(ostream& output);
    void RemovePoint(size_t index);
    string ToString() const;
    PointList ConvexHull() const;
};


#endif //THE_POINTS_2023_POINTLIST_H
