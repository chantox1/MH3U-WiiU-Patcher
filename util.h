// Copyright (C) 2021  Chantox <danielzegers22o@gmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string>
#include <vector>

const std::string whiteSpace = " \t\n\r\f\v";

void stripFilename(char *in, char *out);
void rTrimWhiteSpace(std::string &s);
bool chInString(char ch, std::string str);
void readCharIgnoreWS(std::ifstream &fs, char &ch);
char readName(std::ifstream &fs, std::string &name);
void readPayload(std::ifstream &fs, std::string &payload, int &n_loops);
void readOffsets(std::ifstream &fs, std::vector<int> &offsets);
bool checkMD5(char *path, const unsigned char *hash);
int loadFile(std::ifstream &t, char **fileBuffer, unsigned long &filesize, char *path);
std::string hexifyStr(std::string str);
void pushOffsets(std::vector<int> &offsets, std::string str);

#endif
