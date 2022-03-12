#ifndef FBSD
#define FBSD

#include <SD.h>

void sdSetup(int chipSelect);

void sdLogWrite(String data);

#endif