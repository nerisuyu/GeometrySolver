#ifndef __DATA_H__
#define __DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif /* __DATA_H__ */