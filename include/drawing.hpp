#ifndef __DRAWINGDATA_HPP__
#define __DRAWINGDATA_HPP__

#include <vector>
#include "data.h"

class DrawingData {
protected:
    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Constraint> constraints;
    void _RemoveLineOnlyByPoint(int index);
    void _RemoveConstraintByPoint(int index);
    void _RemoveConstraintByLine(int index);  
public:
    DrawingData() : points(), lines(), constraints() {};
    DrawingData(const char *path);
    bool Save(const char *path);
    
    int  AddPoint(Point* point);
    void MovePoint(Point* delta, int index);
    void RemovePoint(int index);
    int  GetNearestPointIndex(Point* pointer);
    inline const int    PointsCount()       {return points.size();};
    inline const Point* GetPoint(int index) {return points.data() + index;};
    
    int  AddLine(Line* line);
    void RemoveLineOnly(int index);
    void RemoveLinePoints(int index);
    int  GetNearestLineIndex(Point* pointer);
    inline const int  LinesCount()         {return lines.size();};
    inline const Line* GetLine(int index)  {return lines.data() + index;};
    
    int  AddConstraint(Constraint* constraint);
    void RemoveConstraint(int index);
    inline const int  ConstraintsCount()              {return constraints.size();};
    inline const Constraint* GetConstraint(int index) {return constraints.data() + index;};
};

class DrawingDataRef {
    DrawingData& m_data;
public:
    DrawingDataRef(DrawingData& data) : m_data(data) {};
    inline const int         PointsCount()            {return m_data.PointsCount();       };
    inline const Point*      GetPoint(int index)      {return m_data.GetPoint(index);     };
    inline const int         LinesCount()             {return m_data.LinesCount();        };
    inline const Line*       GetLine(int index)       {return m_data.GetLine(index);      };
    inline const int         ConstraintsCount()       {return m_data.ConstraintsCount();  };
    inline const Constraint* GetConstraint(int index) {return m_data.GetConstraint(index);};
};

#endif /* __DRAWING_HPP__ */