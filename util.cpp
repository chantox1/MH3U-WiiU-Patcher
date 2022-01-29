#include "util.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>

void stripFilename(char *in, char *out) {
    char dir[_MAX_DIR];
    _splitpath(in, out, dir, NULL, NULL);
    strcat(out, dir);
}

std::string hexifyStr(std::string str) {
    std::string res;
    for(std::string::size_type i=0; i+1 < str.size(); i=i+2) {
        std::string nextByte = str.substr(i,2);
        int val = std::stoi(nextByte, nullptr, 16);
        res += (unsigned char) val;
    }
    return res;
}

void pushOffsets(std::vector<int> &offsets, std::string str) {
    std::stringstream ss(str);
    std::string offset;
    while (ss.good()) {
        std::getline(ss, offset, ',');
        offsets.push_back(stoi(offset, nullptr, 0));
    }
}
