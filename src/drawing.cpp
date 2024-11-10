#include "drawing.hpp"
#include "common.h"
#include <cmath>
#include <cstdlib>
#include "logger.h"

int
DrawingData::AddPoint(Point* point) {
    points.push_back(*point);
    int index = points.size() - 1;
    return index;
}

void
DrawingData::MovePoint(Point* delta, int index) {
    points[index].x += delta->x;
    points[index].y += delta->y;
    return;
}

void 
DrawingData::_RemoveLineOnlyByPoint(int index) {
    for (int i = 0; i < lines.size();) {
        if (lines[i].point1 <  index) {
            LOG("lines[%d].p1 <  %d\n", i, index);
            if      (lines[i].point2 == index)   RemoveLineOnly(i);
            else if (lines[i].point2  > index) --lines[i++].point2;
            else i++;
            continue;
        }
        if (lines[i].point1 == index) { LOG("l[%d].p1 == %d\n", i, index);RemoveLineOnly(i);} 
        else {
            --lines[i].point1;
            --lines[i].point2;
            i++;
            LOG("l[%d].p1 >  %d\n", i, index);
        }
    }
    return;
}

void
DrawingData::RemovePoint(int index) {
    _RemoveLineOnlyByPoint(index);
    _RemoveConstraintByPoint(index);
    LOG("HERE");
    points.erase(points.begin() + index);
    return;
}

int
DrawingData::GetNearestPointIndex(Point* pointer) {
    double min_length = 1E32;
    int    min_index = -1;
    for (int i = 0; i < points.size(); i++) {
        double length = pow(points[i].x - pointer->x, 2)
                      + pow(points[i].y - pointer->y, 2);
        if (min_length > length) {
            min_length = length;
            min_index = i;
        }
    }
    pointer->x = pointer->y = min_length;
    return min_index;
}

static int
LineCompare(const void* a, const void* b) {
    const Line* l1 = reinterpret_cast<const Line*>(a);
    const Line* l2 = reinterpret_cast<const Line*>(b);
    if (l1->point1 > l2->point1) return 1;
    if (l1->point1 < l2->point1) return-1;
    if (l1->point2 > l2->point2) return 1;
      /*l1->point2 < l2->point2*/return-1;
}

int 
DrawingData::AddLine(Line* line) {
    if (line->point1 > line->point2) {
        int swap = line->point1;
        line->point1 = line->point2;
        line->point2 = swap;
    }
    lines.push_back(*line);
    std::qsort(lines.data(), lines.size(), sizeof(Line), LineCompare);
    int index = lines.size() - 1;
    return index;
}

void
DrawingData::RemoveLineOnly(int index) {
    _RemoveConstraintByLine(index);
    lines.erase(lines.begin() + index);
}

void
DrawingData::RemoveLinePoints(int index) {
    int p1 = lines[index].point1;
    int p2 = lines[index].point2;
    RemoveLineOnly(index);
    points.erase(points.begin() + p1);
    points.erase(points.begin() + p2);
}

static bool
Projection(const Point* point, const Point* linepoint1, const Point* linepoint2, Point* projection) {
    double dx = linepoint2->x - linepoint1->x;
    double dy = linepoint2->y - linepoint1->y;
    double px = point->x - linepoint1->x;
    double py = point->y - linepoint1->y;
    double t = (px*dx + py*dy) / (dx*dx + dy*dy);
    
    projection->x = linepoint1->x + t*dx;
    projection->y = linepoint1->y + t*dy;
    
    return (t > 0 || t < 1);
}

int 
DrawingData::GetNearestLineIndex(Point* pointer) {
    Point projection[1];
    double min_length = 1E32;
    int    min_index;
    for (int i = 0; i < lines.size(); i++) {
        const Point* p1 = GetPoint(lines[i].point1);
        const Point* p2 = GetPoint(lines[i].point2);
        double length;
        if (Projection(pointer, p1, p2, projection)) {
            length = pow(projection->x - pointer->x, 2)
                   + pow(projection->y - pointer->y, 2);
        }
        else {
            double length1 = pow(p1[i].x - pointer->x, 2)
                           + pow(p1[i].y - pointer->y, 2);
            double length2 = pow(p2[i].x - pointer->x, 2)
                           + pow(p2[i].y - pointer->y, 2);
            length = fmin(length1, length2);
        }
        if (min_length > length) {
            min_length = length;
            min_index = i;
        }
    }
    pointer->x = pointer->y = min_length;
    return min_index;
}

void 
DrawingData::_RemoveConstraintByPoint(int index) {
    for (int i = 0; i < constraints.size();) {
        Constraint* constraint = constraints.data() + i;
        switch (constraint->type) {
            case COINCIDENT_POINTS:
            case DISTANCE_OF_POINTS:
                if (constraint->index.point1 == index ||
                    constraint->index.point2 == index )
                {
                    RemoveConstraint(i);
                }
                else i++;
                if (constraint->index.point1 > index) --constraint->index.point1;
                if (constraint->index.point2 > index) --constraint->index.point2;
                break;
            case POINT_ON_A_LINE:
            case FIXED_POINT:
                if (constraint->index.point == index)
                {
                    RemoveConstraint(i);
                }
                else i++;
                if (constraint->index.point > index) --constraint->index.point;
                break;
            default:
                i++;
                break;
        }
    }
}

void 
DrawingData::_RemoveConstraintByLine(int index) {
    for (int i = 0; i < constraints.size();) {
        Constraint* constraint = constraints.data() + i;
        switch (constraint->type) {
            case PARALLEL_LINES:
            case PERPENDICULAR_LINES:
            case ANGLE_OF_LINES:
                if (constraint->index.line1 == index ||
                    constraint->index.line2 == index )
                {
                    RemoveConstraint(i);
                }
                else i++;
                if (constraint->index.line1 > index) --constraint->index.line1;
                if (constraint->index.line2 > index) --constraint->index.line2;
                break;
            case POINT_ON_A_LINE:
            case VERTICAL_LINE:
            case HORIZONTAL_LINE:
                if (constraint->index.line == index)
                {
                    RemoveConstraint(i);
                }
                else i++;
                if (constraint->index.line > index) --constraint->index.line;
                break;
            default:
                i++;
                break;
        }
    }
}

int
DrawingData::AddConstraint(Constraint* constraint) {
    constraints.push_back(*constraint);
    int index = constraints.size() - 1;
    return index;
}

void
DrawingData::RemoveConstraint(int index) {
    constraints.erase(constraints.begin() + index);
}