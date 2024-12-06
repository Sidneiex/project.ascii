#ifndef ASCII_CONVERTER_H
#define ASCII_CONVERTER_H

#include <opencv2/opencv.hpp>
#include <string>

class ASCIIConverter {
public:
    ASCIIConverter(const cv::Mat& image);
    void setAsciiChars(const std::string& chars);
    std::string convertToAsciiArt(bool useColor = false);
    std::string convertToBraille(bool useColor = false); // New method
private:
    cv::Mat image;
    std::string asciiChars;
};

#endif // ASCII_CONVERTER_H