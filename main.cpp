#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;
std::string title = "File System Manipulation";

void typewritter(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void scan(const std::string& rootPath,
          std::unordered_map<std::string, std::vector<fs::path>>& filesByExtension,
          std::unordered_map<std::string, uintmax_t>& countByExtension) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(
                 rootPath,
                 fs::directory_options::skip_permission_denied)) {  // Change this if you want all
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();

                if (ext.empty()) {
                    ext = "[no extension]";
                }

                // convert into lowercase for consistent reading
                std::transform(ext.begin(), ext.end(), ext.begin(),
                               [](unsigned char c) { return std::tolower(c); });

                filesByExtension[ext].push_back(entry.path());
                countByExtension[ext]++;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }

    // Printing summary
    std::cout << "\nFile count by Extension\n";
    for (const auto& [ext, count] : countByExtension) {
        std::cout << ext << " : " << count << " files\n";
    }
    std::cout << '\n';
}

int main() {
    typewritter(title, 40);
    std::cout << std::endl;

    int choice = -1;
    do {
        std::cout << "1. Basic Scan (fast)\n";
        std::cout << "2. Custom Path (experimental)\n";
        std::cout << "9. Clear Screen\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose : ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
            std::cout << "Invalid choice.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string rootPath = "E:\\File System Manipulation\\Sample Files";  // Change this path accordingly
        std::unordered_map<std::string, std::vector<fs::path>> filesByExtension;
        std::unordered_map<std::string, uintmax_t> countByExtension;

        switch (choice) {
            case 1:
                std::cout << "------------------------------------------------------------\n";
                scan(rootPath, filesByExtension, countByExtension);
                std::cout << "------------------------------------------------------------\n";
                break;
            case 2:
                std::cout << "Enter folder path: ";
                // std::getline(std::cin, rootPath);
                // if (fs::exists(rootPath) && fs::is_directory(rootPath)) {
                //     scan(rootPath, filesByExtension, countByExtension);
                // } else {
                //     std::cout << "Path does not exist or is not a folder.\n";
                // }
                break;
            case 9:
                clearScreen();
                typewritter(title, 0);
                std::cout << std::endl;
                break;
            case 0:
                std::cout << "Goodbye.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
        
    } while (choice != 0);

    return 0;
}