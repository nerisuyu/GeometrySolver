#include "data.h"
#include "common.h"
#include "wrapper.h"
#include "drawing.hpp"

static char open_filename[512];

char* Dialog_OpenFile() {
    if (open_filename[0] != '/0') {
        // TODO 
    }
    char* filename = Dialog_GetOpenFileName();
    
    DrawingData* newData = new DrawingData(filename);
    if (newData) {
        if (data)
            delete data;
        data = newData;
    }
}
char* Dialog_SaveAsFile() {
    
}
char* Dialog_SaveFile() {
    
}
char* Dialog_NewFile() {
    
}