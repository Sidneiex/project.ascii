#ifndef GIF_PROCESSOR_H
#define GIF_PROCESSOR_H

#include <Magick++.h>
#include <string>
#include <vector>

class GIFProcessor {
public:
    GIFProcessor(const std::string& gifPath, int newWidth = 100, float charAspectRatio = 0.5f);
    bool loadGIF();
    void processGIF(bool useColor = false, bool useBraille = false);
private:
    std::string gifPath;
    int newWidth;
    float charAspectRatio;
    std::vector<Magick::Image> frames;
};

#endif // GIF_PROCESSOR_H