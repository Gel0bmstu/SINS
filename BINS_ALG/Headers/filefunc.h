#pragma once

#include "../Include/FileFuncs.cpp"

double readFile();
int skipLine(FILE **pFile);
void getVels();
void filePreparation();
void SetTextCurPos(short col, short row);
void SetTextCurVisibility(bool vsbl);
void writeFile();