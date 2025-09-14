#include <iostream>
#include <filesystem>
#include <queue>

using namespace std;

int main()
{
    string path;
    queue<string> queueFiles;
    cout << "Add path files: ";
    getline(cin, path);

    for (auto p : filesystem::recursive_directory_iterator(path)) {
        if (filesystem::is_regular_file(p)) {
            queueFiles.push(p.path().string());
        }
    }

while (!queueFiles.empty()) {
    string pathFile = queueFiles.front();
    queueFiles.pop();

    cout << "Path file: " << pathFile << endl;
}

    return 0;
}
