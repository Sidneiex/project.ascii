#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor {
public:
    VideoProcessor(const std::string& videoPath, int newWidth = 100, float charAspectRatio = 0.5f);
    bool loadVideo();
    void processVideo(bool useColor = false, bool useBraille = false);
private:
    std::string videoPath;
    int newWidth;
    float charAspectRatio;
    cv::VideoCapture cap;
};

#endif // VIDEO_PROCESSOR_H