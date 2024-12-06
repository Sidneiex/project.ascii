#include "image_processor.h"
#include <iostream>

ImageProcessor::ImageProcessor(const std::string& imagePath, int newWidth)
    : imagePath(imagePath), newWidth(newWidth) {}

bool ImageProcessor::loadImage() {
    image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Cannot load image: " << imagePath << std::endl;
        return false;
    }
    return true;
}

void ImageProcessor::adjustContrastBrightness(double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

void ImageProcessor::autoAdjustContrast() {
    if (image.channels() == 1) {
        // Grayscale image
        cv::equalizeHist(image, image);
    } else {
        // Color image
        std::vector<cv::Mat> channels;
        cv::split(image, channels);
        for (auto& channel : channels) {
            cv::equalizeHist(channel, channel);
        }
        cv::merge(channels, image);
    }
}

void ImageProcessor::resizeImage() {
    int originalWidth = image.cols;
    int originalHeight = image.rows;
    float aspectRatio = static_cast<float>(originalHeight) / originalWidth;
    int newHeight = static_cast<int>(newWidth * aspectRatio);
    cv::resize(image, image, cv::Size(newWidth, newHeight));
}

void ImageProcessor::convertToGrayscale() {
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

cv::Mat ImageProcessor::getProcessedImage() {
    return image;
}