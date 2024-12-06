#include "gif_processor.h"
#include "ascii_converter.h"
#include "terminal_manager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

GIFProcessor::GIFProcessor(const std::string& gifPath, int newWidth, float charAspectRatio)
    : gifPath(gifPath), newWidth(newWidth), charAspectRatio(charAspectRatio) {}

bool GIFProcessor::loadGIF() {
    try {
        Magick::readImages(&frames, gifPath);
        if (frames.empty()) {
            std::cerr << "Error: Cannot load GIF or GIF has no frames: " << gifPath << std::endl;
            return false;
        }
        return true;
    } catch (Magick::Exception& error_) {
        std::cerr << "Error loading GIF: " << error_.what() << std::endl;
        return false;
    }
}

void GIFProcessor::processGIF(bool useColor, bool useBraille) {
    // Process each frame in the GIF
    for (const auto& frame : frames) {
        // Convert Magick::Image to OpenCV cv::Mat
        Magick::Image tempFrame = frame;
        tempFrame.magick("BGR");
        Magick::Blob blob;
        tempFrame.write(&blob);
        cv::Mat cvFrame(tempFrame.rows(), tempFrame.columns(), CV_8UC3, (void*)blob.data());

        // Get terminal dimensions
        int terminalWidth = TerminalManager::getTerminalWidth();
        int terminalHeight = TerminalManager::getTerminalHeight();

        // Calculate aspect ratio and resize to fit the terminal while respecting the charAspectRatio
        float aspectRatio = static_cast<float>(cvFrame.cols) / cvFrame.rows;
        int frameWidth = newWidth > 0 ? newWidth : terminalWidth;
        int frameHeight = static_cast<int>(frameWidth / aspectRatio * charAspectRatio);
        
        if (frameHeight > terminalHeight) {
            frameHeight = terminalHeight;
            frameWidth = static_cast<int>(frameHeight * aspectRatio / charAspectRatio);
        }

        cv::resize(cvFrame, cvFrame, cv::Size(frameWidth, frameHeight));

        // Auto-adjust contrast
        if (cvFrame.channels() == 1) {
            cv::equalizeHist(cvFrame, cvFrame);
        } else {
            std::vector<cv::Mat> channels;
            cv::split(cvFrame, channels);
            for (auto& channel : channels) {
                cv::equalizeHist(channel, channel);
            }
            cv::merge(channels, cvFrame);
        }

        // Convert to grayscale if color is not used
        if (!useColor) {
            cv::cvtColor(cvFrame, cvFrame, cv::COLOR_BGR2GRAY);
        }

        // Create ASCII art
        ASCIIConverter asciiConverter(cvFrame);
        std::string asciiArt;
        if (useBraille) {
            asciiArt = asciiConverter.convertToBraille(useColor);
        } else {
            asciiArt = asciiConverter.convertToAsciiArt(useColor);
        }

        // Clear screen and print
        TerminalManager::clearScreen();
        std::cout << asciiArt << std::endl;

        // Control frame rate (this can be adjusted based on the GIF's frame delay if available)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}