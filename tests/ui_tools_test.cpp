#include "data.h"
#include "common.h"
#include "wrapper.h"
#include "assert.h"

void Matrix_MakeMatrix() {}
void Solver_Solve() {}

int main(int _, char* __[]) {
    Drawing_Init();
    
    {
       Point p[] = {
           {0, 0},
           {3, 0},
           {3, 4}
       };
       AddPoint(p+0);
       AddPoint(p+1);
       AddPoint(p+2);
       assert(PointsCount() == 3);
       assert(GetPoint(1)->x == p[1].x &&
              GetPoint(1)->y == p[1].y);
       Line l[] = {
           {1, 0},
           {1, 2},
           {2, 0}
       };
       AddLine(l+0);
       AddLine(l+1);
       AddLine(l+2);
       assert(LinesCount() == 3);
       assert(GetLine(0)->point1 == 0 &&
              GetLine(0)->point2 == 1);
       assert(GetLine(1)->point1 == 0 &&
              GetLine(1)->point2 == 2);
       assert(GetLine(2)->point1 == 1 &&
              GetLine(2)->point2 == 2);
       
       Point pointer = {0, 2};
       assert(GetNearestPointIndex(&pointer) == 0);
       assert(GetNearestLineIndex(&pointer) == 1);
       
       Point pointer2 = {2, 3};
       assert(GetNearestPointIndex(&pointer2) == 2);
       assert(GetNearestLineIndex(&pointer2) == 1);
       
       Constraint c[] = {
             {2, 2, 0, FIXED_POINT},
             {2, 2, 0, HORIZONTAL_LINE},
             {0, 2, 5, DISTANCE_OF_POINTS},
             {0, 3, 90, ANGLE_OF_LINES}
       };
       AddConstraint(c+0);
       AddConstraint(c+1);
       AddConstraint(c+2);
       AddConstraint(c+3);
       assert(ConstraintsCount() == 4);
       assert(GetConstraint(1)->type == HORIZONTAL_LINE);
       
       
       RemovePoint(0);
       assert(LinesCount() == 1);
       assert(GetLine(0)->point1 == 0 &&
              GetLine(0)->point2 == 1);
       assert(GetPoint(0)->x == 3 &&
              GetPoint(0)->y == 0);
       assert(ConstraintsCount() == 2);
       assert(GetConstraint(0)->type        == FIXED_POINT);
       assert(GetConstraint(0)->index.point == 1          );
       assert(GetConstraint(1)->type        == HORIZONTAL_LINE);
       assert(GetConstraint(1)->index.line  == 0              );
    }
    
    Drawing_Free();
    return 0;
}