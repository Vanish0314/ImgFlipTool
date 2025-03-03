#define cimg_use_jpeg
#define cimg_use_png
#define cimg_display 0 // 禁用显示功能
#include "CImg.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cimg_library;

void flip_images_in_folder(const std::string& folder_path) {
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            std::string file_path = entry.path().string();
            std::string extension = entry.path().extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            if (extension == ".png" || extension == ".jpg" || extension == ".jpeg" || extension == ".bmp" || extension == ".gif" || extension == ".tiff") {
                try {
                    CImg<unsigned char> img(file_path.c_str());
                    img.mirror('y'); // Flip vertically
                    img.save(file_path.c_str());
                    std::cout << "Flipped image: " << file_path << std::endl;
                } catch (const cimg_library::CImgIOException& e) {
                    std::cerr << "Failed to process image " << file_path << ": " << e.what() << std::endl;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Please drag and drop a folder onto the executable to process images." << std::endl;
        return 0;
    }

    std::string folder_path = argv[1];
    flip_images_in_folder(folder_path);

    return 0;
}