#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

// Print the tree structure of files and directories
void print_tree(const std::filesystem::path& path, int depth = 0) {
    // Collect all entries in the current directory
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        entries.push_back(entry);
    }
    // Iterate entries and print with correct prefix
    for (size_t i = 0; i < entries.size(); ++i) {
        bool is_last = (i == entries.size() - 1);
        std::string prefix = is_last ? "└── " : "├── ";
        std::string indent = std::string(depth * 4, ' ');
        std::cout << indent << prefix << entries[i].path().filename().string() << std::endl;
        // If entry is a directory, recursively print its contents
        if (entries[i].is_directory()) {
            // For subdirectories, add vertical line if not last
            print_tree(entries[i].path(), depth + 1);
        }
    }
}

int main() {
    std::cout << "." << std::endl; // Print root directory name
    std::filesystem::path root = ".";
    print_tree(root, 0);

    while (true) {
        std::cout << "Enter command(mkdir, touch, rm, rmdir, cp, mv, cat, find, exit): ";
        std::string cmd, name;
        std::cin >> cmd;
        if (cmd == "exit") break;
        
        // std::cout << "Enter name: ";
        // std::cin >> name;
        if (cmd == "mkdir") {
            // create directory
            std::filesystem::create_directory(name);
        } else if (cmd == "touch") {
            // create file
            std::ofstream file(name);
            file.close();
        } else if (cmd == "rm") {
            // remove file
            std::filesystem::remove(name);
        } else if (cmd == "rmdir") {
            // remove directory
            std::filesystem::remove_all(name);
        } else if (cmd == "cp") {
            std::cout << "insert src and dst: ";
            std::string src, dst;
            std::cin >> src >> dst;
            std::filesystem::copy(src, dst, std::filesystem::copy_options::recursive);
        } else if (cmd == "mv") {
            std::cout << "insert oldname and newname: ";
            std::string oldname, newname;
            std::cin >> oldname >> newname;
            std::filesystem::rename(oldname, newname);
        } else if (cmd == "cat") {
            std::cout << "insert filename: ";
            std::string filename;
            std::cin >> filename;
            // open file and print contents
        } else if (cmd == "find") {
            std::cout << "insert keyword: ";
            std::string keyword;
            std::cin >> keyword;
            // recursive search and print matches
            std::filesystem::recursive_directory_iterator it(std::filesystem::current_path());
            for (const auto& entry : it) {
                if (entry.is_directory()) continue;
                if (entry.path().filename().string().find(keyword) != std::string::npos) {
                    std::cout << entry.path().filename().string() << std::endl;
                }
            }
        }
    }
    return 0;
}

/*
.
├── file_manager
├── main.cpp
└── src
    ├── file_manager.cpp
    └── file_manager.h
*/