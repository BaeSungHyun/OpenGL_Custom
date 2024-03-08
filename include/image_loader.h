#define STB_IMAGE_IMPLEMENTATION // turns the header file such that it only contains the relevant definition source code.
#include "stb_image.h"
#include <string>

class Image_Loader {
public:
    Image_Loader() {
        width = 0;
        height = 0;
        data = nullptr;
    }

    Image_Loader(const std::string& filepath) {
        data = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
    }

    unsigned char* getData() const {
        return data;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getChannels() const {
        return nChannels;
    }

    void releaseImgMem() const {
        stbi_image_free(data);
    }
private:
    int width, height, nChannels;
    unsigned char* data;
};