#include "video_processor.h"
#include "ascii_converter.h"
#include "terminal_manager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

VideoProcessor::VideoProcessor(const std::string& videoPath, int newWidth, float charAspectRatio)
    : videoPath(videoPath), newWidth(newWidth), charAspectRatio(charAspectRatio) {}

bool VideoProcessor::loadVideo() {
    cap.open(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video file: " << videoPath << std::endl;
        return false;
    }
    return true;
}

void VideoProcessor::processVideo(bool useColor, bool useBraille) {
    // Print loading message before processing
    TerminalManager::clearScreen();
    std::cout << "Generating your ASCII video output, sit tight..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    TerminalManager::clearScreen();

    cv::Mat frame;
    double fps = cap.get(cv::CAP_PROP_FPS);
    int delay = fps > 0 ? static_cast<int>(1000 / fps) : 33;

    while (cap.read(frame)) {
        int terminalWidth = TerminalManager::getTerminalWidth();
        int terminalHeight = TerminalManager::getTerminalHeight();

        int frameWidth = newWidth > 0 ? newWidth : terminalWidth;
        float aspectRatio = static_cast<float>(frame.cols) / static_cast<float>(frame.rows);

        int frameHeight = static_cast<int>(frameWidth / aspectRatio * charAspectRatio);
        if (frameHeight > terminalHeight) {
            frameHeight = terminalHeight;
            frameWidth = static_cast<int>(frameHeight * aspectRatio / charAspectRatio);
        }

        cv::resize(frame, frame, cv::Size(frameWidth, frameHeight));

        // Auto-adjust contrast
        if (frame.channels() == 1) {
            cv::equalizeHist(frame, frame);
        } else {
            std::vector<cv::Mat> channels;
            cv::split(frame, channels);
            for (auto& channel : channels) {
                cv::equalizeHist(channel, channel);
            }
            cv::merge(channels, frame);
        }

        // Convert to grayscale if color is not used
        if (!useColor) {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }

        // Create ASCII art
        ASCIIConverter asciiConverter(frame);
        std::string asciiArt;
        if (useBraille) {
            asciiArt = asciiConverter.convertToBraille(useColor);
        } else {
            asciiArt = asciiConverter.convertToAsciiArt(useColor);
        }

        // Clear screen and print
        TerminalManager::clearScreen();
        std::cout << asciiArt << std::endl;

        // Wait for the appropriate time before showing the next frame
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}