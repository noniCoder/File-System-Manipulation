#include<iostream>
#include<filesystem>
#include<unordered_map>
#include<vector>
#include<algorithm>

namespace fs = std::filesystem;

void scan(std::string rootPath, std::unordered_map<std::string, std::vector<fs::path>>& filesByExtension, std::unordered_map<std::string, uintmax_t>& countByExtension){
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(
            rootPath, 
            fs::directory_options::skip_permission_denied   //Change this if you want all 
        )){
            if(fs::is_regular_file(entry.path())){
                std::string ext = entry.path().extension().string();

                if(ext.empty()){
                    ext = "[no extension]";
                }

                //convert into lowsercase for consistent reading
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

                filesByExtension[ext].push_back(entry.path());
                countByExtension[ext]++;
            }            
        }
    }
    catch(const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }

    //Printing summary 
    std::cout << "\nFile count by Extension\n";
    for(const auto& [ext, count] : countByExtension){
        std::cout << ext << " : " << count << " files\n";
    }
}

int main(){
    int choice;

    std::string rootPath = "E:\\File System Manipulation\\Sample Files";      //Change this path accordingly
    std::unordered_map<std::string, std::vector<fs::path>> filesByExtension;
    std::unordered_map<std::string, uintmax_t> countByExtension;

    do
    {
        std::cout << "File System Manipulation\n";
        std::cout << "1. Scan Files\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;

        if(choice == 1){
            scan(rootPath, filesByExtension, countByExtension);
        }
        else if(choice == 2){
            std::cout << "Exiting program...\n";
        }
        else{
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 1 && choice != 2);

    std::cout << "exiting program\n";
    
    return 0;
    
    //Specific extension
    // std::string specExt = ".txt";
    // std::cout << "File with Extension: " << specExt << "\n";
    // if(filesByExtension.count(specExt)){
    //     for(const auto& path : filesByExtension[specExt]){
    //         std::cout << path.string() << "\n";
    //     }  
    // }
    // else{
    //     std::cout << "No files found with extension: " << specExt << "\n";
    // }

    // return 0;
}