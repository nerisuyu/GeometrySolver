#include <fstream>
#include <vector>
#include "drawing.hpp"
#include <cstring>

typedef struct _BinaryFileHeader {
    std::size_t points_count;
    std::size_t lines_count;
    std::size_t constraints_count;
} BinaryFileHeader;

class DrawingDataImage {
public:
    std::vector<Point>      points;
    std::vector<Line>       lines;
    std::vector<Constraint> constraints;
    DrawingDataImage(std::size_t p, std::size_t l, std::size_t c)
        : points(p)
        , lines(l)
        , constraints(c)
    {};
};

static
bool File_BinarySave(DrawingData& drawing, const char* filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    BinaryFileHeader data = {
        drawing.PointsCount(),
        drawing.LinesCount(),
        drawing.ConstraintsCount()
    };
    
    file.write(reinterpret_cast<const char*>(data.points_count),      sizeof(std::size_t));
    file.write(reinterpret_cast<const char*>(data.lines_count),       sizeof(std::size_t));
    file.write(reinterpret_cast<const char*>(data.constraints_count), sizeof(std::size_t));
    
    file.write(reinterpret_cast<const char*>(drawing.GetPoint(0)),      data.points_count      * sizeof(Point));
    file.write(reinterpret_cast<const char*>(drawing.GetLine(0)),       data.lines_count       * sizeof(Line));
    file.write(reinterpret_cast<const char*>(drawing.GetConstraint(0)), data.constraints_count * sizeof(Constraint));
    
    file.close();
    
    return true;
}

static
DrawingDataImage* File_BinaryOpen(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    BinaryFileHeader data;
    
    std::size_t size[1];
    file.read(reinterpret_cast<char*>(size), sizeof(std::size_t));
    data.points_count = *size;
    file.read(reinterpret_cast<char*>(size), sizeof(std::size_t));
    data.lines_count = *size;
    file.read(reinterpret_cast<char*>(size), sizeof(std::size_t));
    data.constraints_count = *size;
    
    DrawingDataImage* image = new DrawingDataImage(data.points_count, data.lines_count, data.constraints_count);
    
    file.read(reinterpret_cast<char*>(image->points.data()), data.points_count*sizeof(Point));
    file.read(reinterpret_cast<char*>(image->lines.data()), data.lines_count*sizeof(Line));
    file.read(reinterpret_cast<char*>(image->constraints.data()),data.constraints_count*sizeof(Constraint));
    
    file.close();
    
    return image;
}

DrawingData::DrawingData(const char *path) {
    const char* extension = strrchr(path, '.');
    DrawingDataImage* image = nullptr;
    if (strcmp(extension, ".bdw")) {
        image = File_BinaryOpen(path);
    }
    if (image) {
        points.swap(image->points);
        lines.swap(image->lines);
        constraints.swap(image->constraints);
        delete image;
    }
}

bool
DrawingData::Save(const char *path) {
    const char* extension = strrchr(path, '.');
    if (strcmp(extension, ".bdw")) {
        return File_BinarySave(*this, path);
    }
}