// Copyright (C) 2021  Chantox <danielzegers22o@gmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#include "util.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <openssl/md5.h>

void stripFilename(char *in, char *out) {
    char dir[_MAX_DIR];
    _splitpath(in, out, dir, NULL, NULL);
    strcat(out, dir);
}

bool checkMD5(char *path, const unsigned char *hash) {
    std::ifstream t;
    char *fileBuffer;
    unsigned long filesize;

    if (!loadFile(t, &fileBuffer, filesize, path)) {
        unsigned char result[MD5_DIGEST_LENGTH];
        MD5((unsigned char*) fileBuffer, filesize, result);
        delete fileBuffer;
        t.close();

        for (int i=0; i < MD5_DIGEST_LENGTH; i++) {
            if (result[i] != hash[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int loadFile(std::ifstream &t, char **fileBuffer, unsigned long &filesize, char *path) {
    t.exceptions(std::ifstream::badbit);
    try {
        t.open(path);
        t.seekg(0, std::ios::end);
        filesize = t.tellg();
        t.seekg(0, std::ios::beg);

        *fileBuffer = new char[filesize];
        t.read(*fileBuffer, filesize);
    }
    catch(const std::ifstream::failure &f) {
        std::cout
            << "Exception occurred while opening or reading file at" << path << "\n";
        return -1;
    }
    return 0;
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
