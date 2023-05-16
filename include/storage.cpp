#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

class Storage {
public:
    static std::string read(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string content((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
            file.close();
            return content;
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return "";
        }
    }

    static bool write(const std::string& directory, const std::string& filename, const std::string& content) {
        if (!isDirectoryAllowed(directory)) {
            std::cerr << "Access to the specified directory is not allowed." << std::endl;
            return false;
        }

        std::ofstream file(directory + "/" + filename);
        if (file.is_open()) {
            file << content;
            file.close();
            return true;
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }
    }

    static std::vector<std::string> searchFiles(const std::string& directory) {
        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().filename().string());
            }
        }
        return files;
    }

private:
    static bool isDirectoryAllowed(const std::string& directory) {
        // Example directory set as allowed ("/path/to/allowed_directory")
        const std::string allowedDirectory = "./resources";
        return (directory == allowedDirectory);
    }
};
