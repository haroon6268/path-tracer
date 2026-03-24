#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

int main()
{
  std::cout << "Hello World!" << std::endl;
    int width = 512;
    int height = 512;
    int channels = 3; // RGB
    unsigned char data[width * height * channels];
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
            if((x/64)%2 == 0){
            int index = (y * width + x) * channels;
            data[index]     = 0; // Red
            data[index + 1] = 0;   // Green
            data[index + 2] = 255;   // Blue
            }else{
            int index = (y * width + x) * channels;
            data[index]     = 0; // Red
            data[index + 1] = 255;   // Green
            data[index + 2] = 0;   // Blue
            }
        }
    }

    stbi_write_png("output.png", width, height, channels, data, width * channels);
    return 0;
}
