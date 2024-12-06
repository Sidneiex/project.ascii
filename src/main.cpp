#include "image_processor.h"
#include "ascii_converter.h"
#include "video_processor.h"
#include "gif_processor.h"
#include "terminal_manager.h"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool isImageFile(const std::string& path) {
    std::string ext = fs::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp" || ext == ".webp" || ext == ".tiff" || ext == ".tif");
}

bool isGifFile(const std::string& path) {
    std::string ext = fs::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return (ext == ".gif");
}

bool isVideoFile(const std::string& path) {
    std::string ext = fs::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return (ext == ".mp4" || ext == ".avi" || ext == ".mov" || ext == ".mkv" || ext == ".flv");
}

int main(int argc, char* argv[]) {
    Magick::InitializeMagick(*argv);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_path> [options]" << std::endl;
        return -1;
    }

    std::string inputPath = argv[1];
    int newWidth = TerminalManager::getTerminalWidth(); // Use terminal width
    bool useColor = false;
    bool useBraille = false;
    float charAspectRatio = 0.5f; // Default character aspect ratio

    // Simple argument parsing
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--color" || arg == "-C") {
            useColor = true;
        } else if (arg == "--width" || arg == "-W") {
            if (i + 1 < argc) {
                newWidth = std::stoi(argv[++i]);
            } else {
                std::cerr << "Error: Width value not specified." << std::endl;
                return -1;
            }
        } 
        else if (arg == "--char-aspect" || arg == "-A") {  // Added a new argument for character aspect ratio to parse and store the value into the charAspectRatio variable
            if (i + 1 < argc) {
                charAspectRatio = std::stof(argv[++i]);
            } else {
                std::cerr << "Error: Char aspect ratio value not specified." << std::endl;
                return -1;
            }
        }
        else if (arg == "--braille" || arg == "-B") {
            useBraille = true;
        }
    }

    if (isImageFile(inputPath)) {
        // Process as image
        ImageProcessor imgProcessor(inputPath, newWidth);
        if (!imgProcessor.loadImage()) {
            return -1;
        }
        imgProcessor.resizeImage();
        imgProcessor.autoAdjustContrast(); // Auto-adjust contrast
        ASCIIConverter asciiConverter(imgProcessor.getProcessedImage());
        std::string asciiArt;
        if (useBraille) {
            asciiArt = asciiConverter.convertToBraille(useColor);
        } else {
            asciiArt = asciiConverter.convertToAsciiArt(useColor);
        }
        std::cout << asciiArt << std::endl;
    } else if (isVideoFile(inputPath)) {
        // Initialize ncurses for video
        initscr();
        noecho();
        curs_set(FALSE);

        // Process as video
        VideoProcessor videoProcessor(inputPath, newWidth, charAspectRatio); // Added charAspectRatio as an argument
        if (!videoProcessor.loadVideo()) {
            endwin();
            return -1;
        }
        videoProcessor.processVideo(useColor, useBraille);

        // End ncurses
        endwin();
    } else if (isGifFile(inputPath)) {
        // Initialize ncurses for GIF
        initscr();
        noecho();
        curs_set(FALSE);

        // Process as GIF
        GIFProcessor gifProcessor(inputPath, newWidth, charAspectRatio); // Added charAspectRatio as an argument
        if (!gifProcessor.loadGIF()) {
            endwin();
            return -1;
        }
        gifProcessor.processGIF(useColor, useBraille);

        // End ncurses
        endwin();
    } else {
        std::cerr << "Unsupported file format." << std::endl;
        return -1;
    }

    return 0;
}
