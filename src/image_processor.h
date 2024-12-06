#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class ImageProcessor {
public:
    ImageProcessor(const std::string& imagePath, int newWidth = 100);
    bool loadImage();
    void resizeImage();
    void convertToGrayscale();
    void adjustContrastBrightness(double alpha, int beta);
    void autoAdjustContrast(); // New method
    cv::Mat getProcessedImage();
private:
    std::string imagePath;
    cv::Mat image;
    int newWidth;
};

#endif // IMAGE_PROCESSOR_H