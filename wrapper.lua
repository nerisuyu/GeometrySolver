local ffi = require("ffi");

ffi.cdef[[
  typedef struct Point {
    double x;
    double y;
  } Point;
  typedef struct Line {
    int point1;
    int point2;
  } Line;
  typedef enum ConstraintType {
    COINCIDENT_POINTS = 0,
    DISTANCE_OF_POINTS,   
    PARALLEL_LINES,       
    PERPENDICULAR_LINES,
    ANGLE_OF_LINES,
    VERTICAL_LINE,
    HORIZONTAL_LINE,
    POINT_ON_A_LINE,
    FIXED_POINT,
    CONSTRAINT_TYPES_COUNT
  } ConstraintType;
  typedef struct Constraint {
    union ConstraintIndices {
      struct {
        int point1;
        int point2;
      };
      struct {
        int line2;
        int line1;
      };
      struct {
        int point;
        int line;
      };
    } index;
    double value;
    ConstraintType type;
  } Constraint;
  typedef struct NearestData {
    int index;
    double distance;
  } NearestData;
  void* Drawing_Init();
  void  Drawing_Free();
  int  AddPoint(double x, double y);
  void MovePointAnonimous(double dx, double dy, int index);
  void MovePoint(double dx, double dy, int index);
  void RemovePoint(int index);
  NearestData* GetNearestPointIndex(double px, double py);
  int  PointsCount();
  Point* GetPoint(int index);
  int  AddLine(int point1, int point2);
  void RemoveLineOnly(int index);
  void RemoveLinePoints(int index);
  NearestData* GetNearestLineIndex(double px, double py);
  int  LinesCount();
  Line* GetLine(int index);
  
  int  AddConstraint(int a, int b, double value, ConstraintType type);
  void RemoveConstraint(int index);
  int  ConstraintsCount();
  const Constraint* GetConstraint(int index);
]]

return ffi.load("core")