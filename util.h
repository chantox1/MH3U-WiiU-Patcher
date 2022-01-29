#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string>
#include <vector>

void stripFilename(char *in, char *out);
bool checkMD5(char *path, const unsigned char *hash);
std::string hexifyStr(std::string str);
void pushOffsets(std::vector<int> &offsets, std::string str);

#endif
