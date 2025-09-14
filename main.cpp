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
    string zipName = fileName + ".zip";

    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    if (!mz_zip_writer_init_file(&zip, zipName.c_str(), 0)) {
        throw runtime_error("Error create zip: " + zipName);
    }

    string simpleName = filesystem::path(fileName).filename().string();

    if (!mz_zip_writer_add_mem(
        &zip,
        simpleName.c_str(),
        dataFile.data(),
        dataFile.size(),
        MZ_BEST_COMPRESSION)
        ) {
        mz_zip_writer_end(&zip);
        throw runtime_error("Error add file in zip");
    }

    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);

    cout << "Compression finish: " << zipName << endl;

}

void readQueue() {
    while (!queueFiles.empty()) {
        string pathFile = queueFiles.front();
        queueFiles.pop();

        cout << "path file: " << pathFile << endl;

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
