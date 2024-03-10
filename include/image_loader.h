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

    Image_Loader(const std::string& filepath, bool flipVertical = false) {
        if (flipVertical) flipVertically();
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

    // image y-axis and OpenGL conventional y-axis is different.
    void flipVertically() const {
        stbi_set_flip_vertically_on_load(true); // should come before loaindg any image
    }

    void releaseImgMem() const {
        stbi_image_free(data);
    }
private:
    int width, height, nChannels;
    unsigned char* data;
};