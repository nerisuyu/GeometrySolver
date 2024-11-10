#include "data.h"
#include "common.h"
#include "wrapper.h"
#include "drawing.hpp"
#include <cmath>
#include <logger.h>


extern "C" {

FILE* logfile;

static NearestData nearest_data[1];

static DrawingData* data;

void* Drawing_Init() {
    openlogfile();
    return data = new DrawingData;
}
void  Drawing_Free() { 
    delete data;
}

int  AddPoint(double x, double y) { 
    Point point[] = {{x, y}};
    return data->AddPoint(point);
    Matrix_MakeMatrix();
    Solver_Solve();
}
void MovePointAnonimous(double dx, double dy, int index) { 
    Point delta[] = {{dx, dy}};
    data->MovePoint(delta, index);
}
void MovePoint(double dx, double dy, int index) { 
    Point delta[] = {{dx, dy}};
    data->MovePoint(delta, index);
    Matrix_MakeMatrix();
    Solver_Solve();
}
void RemovePoint(int index) { 
    data->RemovePoint(index);
    Matrix_MakeMatrix();
    Solver_Solve();
}
const NearestData* GetNearestPointIndex(double px, double py) { 
    Point pointer[] = {{px, py}};
    nearest_data->index = data->GetNearestPointIndex(pointer);
    nearest_data->distance = sqrt(pointer->x);
    return nearest_data;
}
int PointsCount() { 
    return data->PointsCount();
}
const Point* GetPoint(int index) { 
    return data->GetPoint(index);
}

int  AddLine(int point1, int point2) { 
    Line line[] = {{point1, point2}};
    return data->AddLine(line);
}
void RemoveLineOnly(int index){ 
    data->RemoveLineOnly(index);
    Matrix_MakeMatrix();
    Solver_Solve();
}
void RemoveLinePoints(int index) { 
    data->RemoveLinePoints(index);
    Matrix_MakeMatrix();
    Solver_Solve();
}
const NearestData* GetNearestLineIndex(double px, double py) { 
    Point pointer[] = {{px, py}};
    nearest_data->index = data->GetNearestLineIndex(pointer);
    nearest_data->distance = sqrt(pointer->x);
    return nearest_data;
}
int  LinesCount() { 
    return data->LinesCount();
}
const Line* GetLine(int index) { 
    return data->GetLine(index);
}

int  AddConstraint(int a, int b, double value, ConstraintType type) { 
    Constraint constraint[] = {{a, b, value, type}};
    int index = data->AddConstraint(constraint);
    Matrix_MakeMatrix();
    Solver_Solve();
    return index;
}
void RemoveConstraint(int index) { 
    data->RemoveConstraint(index);
    Matrix_MakeMatrix();
    Solver_Solve();
}
int  ConstraintsCount() { 
    return data->ConstraintsCount();
}
const Constraint* GetConstraint(int index) { 
    return data->GetConstraint(index);
}



};