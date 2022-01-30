// Copyright (C) 2021  Chantox <danielzegers22o@gmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

const unsigned char rpxHash[] = "\x38\x22\x89\x66\x3e\xb3\xbf\x8a\x73\x88\x42\x60\x69\x04\x49\xd8";

const char md5Error[] = "The file provided failed to match the expected MD5 hash.\n"
                        "Please ensure the file is unpatched, and corresponds to "
                        "the EUR / PAL version of the game.\n";

const char patchError[] =   "Patching failed.\n"
                            "Please ensure you have write access to the patcher's directory.\n";

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
