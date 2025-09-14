#include <iostream>
#include <filesystem>
#include <queue>
#include <fstream>
#include <string>
#include "miniz.h"

using namespace std;

queue<string> queueFiles;

vector<char> readFile(const string& fileName) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        throw runtime_error("No open file: " + fileName);
    }

    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0);

    vector<char> buffer(size);
    file.read(buffer.data(), size);
    return buffer;
}

void compressionToZip(const string& fileName) {
    vector<char> dataFile = readFile(fileName);




}

void readQueue() {
    while (!queueFiles.empty()) {
        string pathFile = queueFiles.front();
        queueFiles.pop();

        compressionToZip(pathFile);
    }
}

int main()
{
    string path;
    cout << "Add path files: ";
    getline(cin, path);

    for (auto p : filesystem::recursive_directory_iterator(path)) {
        if (filesystem::is_regular_file(p)) {
            queueFiles.push(p.path().string());
        }
    }

    readQueue();

    return 0;
}
