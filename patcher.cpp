// Copyright (C) 2021  Chantox <danielzegers22o@gmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#include "patcher.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <direct.h> 
#include <filesystem>
#include "util.h"
using namespace std;
namespace fs = filesystem;

void getPatches(vector<Patch> &patchList) {
    string name;
    string data;
    vector<int> offsets;
    int n_loops;

    ifstream patches("patches.txt");
    string line;
    int count = 1;
    while (getline(patches, line)) {
        if (count == 1) {
            name = line;
        }
        else if (count == 2) {
            data = hexifyStr(line);
        }
        else if (count == 3) {
            pushOffsets(offsets, line);
        }
        else if (count == 4) {
            int n_loops = stoi(line);

            patchList.push_back(Patch(name, data, offsets, n_loops));
            offsets.clear();
        }
        else count = 0;
        count++;
    }
}

void newGetPatches(vector<Patch_new> &patchList) {
    string name;
    std::string payload;
    vector<int> offsets;
    int n_loops;
    vector<PatchData> data;

    ifstream patchReader;
    patchReader.exceptions(ifstream::badbit);
    char ch;
    try {
        patchReader.open(".test/newPatches.txt");
        readCharIgnoreWS(patchReader, ch);
        while (patchReader.good()) {
            name += ch;
            ch = readName(patchReader, name);
            while (ch == '[') {
                readPayload(patchReader, payload, n_loops);
                readOffsets(patchReader, offsets);
                data.push_back({payload, offsets, n_loops});
                readCharIgnoreWS(patchReader, ch);
            }

            patchList.push_back(Patch_new(name, data));
            name.clear();
            offsets.clear();
            data.clear();
        }
    }
    catch (const ifstream::failure& f) {
        cout << "Exception occurred while reading patches.txt\n";
    }
}

int applyPatches(vector<Patch> &patchList, char *path) {
    // Decompress into code.bin
    try {
        fs::copy_file(path, "temp.rpx", fs::copy_options::overwrite_existing);
    }
    catch(const fs::filesystem_error &fe){
        cerr << fe.what() << '\n';
        return -1;
    }
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
    
    // Create backup
    char bkpPath[_MAX_PATH];
    stripFilename(path, bkpPath);
    strcat(bkpPath, "MH3G_Cafe_EU.bkp");
    rename(path, bkpPath);

    // Recompress & replace original at path
    system("wiiurpxtool -c code.bin temp.rpx");
    rename("temp.rpx", path);
    remove("code.bin");

    return 0;
}

int main (int argc, char* argv[]) {
    if (argc == 2) {
       char workingDir[_MAX_DIR];
       stripFilename(argv[0], workingDir);
        _chdir(workingDir);

        char *path = argv[1];
        if (checkMD5(path, rpxHash)) {
            cout << "Commencing patch process.\n";
            vector<Patch_new> patchList;
            newGetPatches(patchList);
            for (auto & element : patchList) {
                cout << element.name << "\n";
            }
            /*
            vector<Patch> patchList;
            getPatches(patchList);
            if (!applyPatches(patchList, path)){
                cout << "Patching complete!\n";
            }
            else {
                cout << patchError;
            }
            */
        }
        else {
            cout << md5Error;
        }
        system("pause");
    }
    else {
        cout << "No file provided.\n"
                "Please drag-and-drop MH3U_Cafe_EU.rpx onto the exe.\n";
        system("pause");
    }
    return 0;
}
