#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

static char szFile[MAX_PATH];

char* Dialog_OpenFile() {
    OPENFILENAME ofn;
    
    ZeroMemory(szFile, MAX_PATH);
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0JSON Files (*.json)\0*.json\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) { return szFile; }
    return "No such file";
}

char* Dialog_SaveAsFile() {
    OPENFILENAME ofn;
    
    ZeroMemory(szFile, MAX_PATH);
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0JSON Files (*.json)\0*.json\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = ".txt";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn)) { return szFile; }
    return "No such file";
}