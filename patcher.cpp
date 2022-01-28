#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <direct.h> 
#include <filesystem>
#include <openssl/md5.h>
namespace fs = std::filesystem;
using namespace std;


class Patch {
    public:
        string name;
        string data;
        vector<int> offsets;
        int n_loops;

        Patch(string name, string data, vector<int> offsets, int n_loops) {
            this->name = name;
            this->data = data;
            this->offsets = offsets;
            this->n_loops = n_loops;
        }
};

const unsigned char rpxHash[] = "\x38\x22\x89\x66\x3e\xb3\xbf\x8a\x73\x88\x42\x60\x69\x04\x49\xd8";

std::string hexifyStr(std::string str) {
    std::string res;
    for(std::string::size_type i=0; i+1 < str.size(); i=i+2) {
        std::string nextByte = str.substr(i,2);
        int val = std::stoi(nextByte, nullptr, 16);
        res += (unsigned char) val;
    }
    return res;
}

void getPatches(vector<Patch> &patchList) {
    string name;
    string data;
    vector<int> offsets;
    int n_loops;

    ifstream patches("patches.txt");
    string line;
    int count = 0;

    while (getline(patches, line)) {
        if (count == 0){
            name = line;
        }
        else if (count == 1)
            data = hexifyStr(line);
        else if (count == 2) {
            stringstream ss(line);
            string tempOffset;
            while (ss.good()) {
                getline(ss, tempOffset, ',');
                offsets.push_back(stoi(tempOffset, nullptr, 0));
            }
        }
        else if (count == 3) {
            int n_loops = stoi(line);
            patchList.push_back(Patch(name, data, offsets, n_loops));
        }
        else offsets.clear();
        count = (count > 3) ? 0 : count + 1;
    }
}

void applyPatches(vector<Patch> &patchList, char *path) {
    // Decompress into code.bin
    fs::copy_file(path, "./temp.rpx");
    system("wiiurpxtool -d temp.rpx code.bin");
    remove("temp.rpx");

    // Iterate over patchList & patch
    FILE *code = fopen("code.bin", "r+");
    string in;
    for (auto & element : patchList) {
        cout << "Apply patch \"" + element.name + "\"? Y/N\n";
        cin >> in;
        if (!in.compare("Y")) {
            string data = element.data;
            int datasize = data.size();
            for (auto & offset : element.offsets) {
                for (int i=0; i < element.n_loops; i++) {
                    fseek(code, offset + i*datasize, SEEK_SET);
                    fwrite(data.c_str(), datasize, 1, code);
                }
            }
        }
    }
    fclose(code);

    char saveDir[_MAX_DIR], tempPath[_MAX_DIR];
    _splitpath(path, saveDir, tempPath, NULL, NULL);
    strcat(saveDir, tempPath);
    
    // Create backup
    char bkpPath[_MAX_PATH];
    strcpy(bkpPath, saveDir);
    strcat(bkpPath, "MH3G_Cafe_EU.bkp");
    rename(path, bkpPath);

    // Recompress & replace original at path
    system("wiiurpxtool -c code.bin temp.rpx");
    rename("temp.rpx", path);
    remove("code.bin");
}

bool checkMD5(char *path) {
    unsigned long filesize;
    char* file_buffer;
    ifstream t;

    // Get filesize
    t.open(path);
    t.seekg(0, ios::end);
    filesize = t.tellg();
    t.seekg(0, ios::beg);

    // Read file into memory & get MD5
    unsigned char result[MD5_DIGEST_LENGTH];
    file_buffer = new char[filesize];
    t.read((char*) file_buffer, filesize);
    MD5((unsigned char*) file_buffer, filesize, result);
    delete file_buffer;
    t.close();

    // Compare to pre-defined hash
    for (int i=0; i < MD5_DIGEST_LENGTH; i++) {
        if (result[i] != rpxHash[i])
            return false;
    }
    return true;
}

int main (int argc, char* argv[]) {
    if (argc == 2) {
        char workingDir[_MAX_PATH], tempPath[_MAX_PATH];
        _splitpath(argv[0], workingDir, tempPath, NULL, NULL);
        strcat(workingDir, tempPath);
        _chdir(workingDir);

        char *path = argv[1];
        if (checkMD5(path)) {
            vector<Patch> patchList;
            getPatches(patchList);
            applyPatches(patchList, path);
            cout << "Patching complete!\n";
        }
        else 
            cout << "File does not match expected MD5 hash.\n"
                    "Please ensure the file provided is unpatched, and"
                    "corresponds to the EUR / PAL version of the game.\n";
        system("pause");
    }
    else {
        cout << "No file provided.\n"
                "Please drag-and-drop MH3U_Cafe_EU.rpx onto the exe.\n";
        system("pause");
    }
    return 0;
}
