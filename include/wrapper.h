#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NearestData {
    int index;
    double distance;
} NearestData;

void* Drawing_Init();
void  Drawing_Free();
int  AddPoint(double x, double y);
void MovePoint(double dx, double dy, int index);
void RemovePoint(int index);
const NearestData* GetNearestPointIndex(double px, double py);
int PointsCount();
const Point* GetPoint(int index);
int  AddLine(int point1, int point2);
void RemoveLineOnly(int index);
void RemoveLinePoints(int index);
const NearestData* GetNearestLineIndex(double px, double py);
int  LinesCount();
const Line* GetLine(int index);
int  AddConstraint(int a, int b, double value, ConstraintType type);
void RemoveConstraint(int index);
int  ConstraintsCount();
const Constraint* GetConstraint(int index);

char* Dialog_OpenFile();
char* Dialog_SaveAsFile();
char* Dialog_SaveFile();

char* Dialog_GetOpenFileName();
char* Dialog_GetSaveAsFileName();

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif /* __WRAPPER_H__ */
