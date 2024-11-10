#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

static char szFile[2*MAX_PATH];

char* Dialog_GetOpenFileName() {
    OPENFILENAME ofn;
    
    ZeroMemory(szFile, MAX_PATH);
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Binary Drawing Files (*.bdw)\0*.bdw\0"; // "Text Files (*.txt)\0*.txt\0JSON Files (*.json)\0*.json\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) { return szFile; }
    return NULL;
}

char* Dialog_GetSaveAsFileName() {
    OPENFILENAME ofn;
    
    ZeroMemory(szFile, MAX_PATH);
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Binary Drawing Files (*.bdw)\0*.bdw\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = ".bdw";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn)) { return szFile; }
    return NULL;
}