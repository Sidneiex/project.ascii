#include "ascii_converter.h"
#include <algorithm> // For std::clamp

ASCIIConverter::ASCIIConverter(const cv::Mat& image)
    : image(image) {
    // More detailed character set for higher resolution
    asciiChars = "@%#*+=-:. ";
}

void ASCIIConverter::setAsciiChars(const std::string& chars) {
    asciiChars = chars;
}

std::string ASCIIConverter::convertToAsciiArt(bool useColor) {
    std::string asciiArt;
    int numChars = asciiChars.size();

    // Adjusted scaling factor for character aspect ratio
     float scaleFactor = 0.5f;

    for (int i = 0; i < image.rows; ++i) {
        std::string line;
        for (int j = 0; j < image.cols; ++j) {
            int charIndex = 0;
            uchar red = 0, green = 0, blue = 0;

            if (image.channels() == 1) {
                uchar pixelValue = image.at<uchar>(i, j);
                int intensity = pixelValue;
                charIndex = ((255 - intensity) * (numChars - 1)) / 255;
                red = green = blue = pixelValue;
            } else {
                cv::Vec3b colorPixel = image.at<cv::Vec3b>(i, j);
                blue = colorPixel[0];
                green = colorPixel[1];
                red = colorPixel[2];
                int intensity = static_cast<int>(0.299 * red + 0.587 * green + 0.114 * blue);
                charIndex = ((255 - intensity) * (numChars - 1)) / 255;
            }

            charIndex = std::clamp(charIndex, 0, numChars - 1);
            char asciiChar = asciiChars[charIndex];

            if (useColor) {
                line += "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
                line += asciiChar;
                line += "\033[0m"; // Reset color
            } else {
                line += asciiChar;
            }
        }
        asciiArt += line + '\n';
    }
    return asciiArt;
}

std::string ASCIIConverter::convertToBraille(bool useColor) {
    std::string brailleArt;

    cv::Mat grayImage;
    if (image.channels() == 3) {
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    } else {
        grayImage = image;
    }

    // Braille character mapping requires 2x4 pixel blocks
    int width = grayImage.cols - (grayImage.cols % 2);
    int height = grayImage.rows - (grayImage.rows % 4);

    for (int y = 0; y < height; y += 4) {
        std::string line;
        for (int x = 0; x < width; x += 2) {
            int brailleChar = 0x2800; // Base Unicode point for braille

            for (int dy = 0; dy < 4; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    int pixelX = x + dx;
                    int pixelY = y + dy;
                    uchar pixelValue = grayImage.at<uchar>(pixelY, pixelX);
                    bool isDotSet = pixelValue < 128; // Threshold can be adjusted

                    if (isDotSet) {
                        // Braille dot numbering
                        int dotPosition = dy * 2 + dx;
                        // Map dot position to braille encoding
                        static const int brailleDots[8] = {0x01, 0x08, 0x02, 0x10, 0x04, 0x20, 0x40, 0x80};
                        brailleChar |= brailleDots[dotPosition];
                    }
                }
            }

            if (useColor && image.channels() == 3) {
                cv::Vec3b colorPixel = image.at<cv::Vec3b>(y, x);
                uchar red = colorPixel[2];
                uchar green = colorPixel[1];
                uchar blue = colorPixel[0];
                line += "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
            }

            line += static_cast<char>(brailleChar);

            if (useColor && image.channels() == 3) {
                line += "\033[0m"; // Reset color
            }
        }
        brailleArt += line + '\n';
    }

    return brailleArt;
}