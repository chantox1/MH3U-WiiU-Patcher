// Copyright (C) 2021  Chantox <danielzegers22o@gmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string>
#include <vector>

void stripFilename(char *in, char *out);
bool checkMD5(char *path, const unsigned char *hash);
int loadFile(std::ifstream &t, char **fileBuffer, unsigned long &filesize, char *path);
std::string hexifyStr(std::string str);
void pushOffsets(std::vector<int> &offsets, std::string str);

#endif
