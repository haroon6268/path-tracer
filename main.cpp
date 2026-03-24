#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glm/glm.hpp"
#include <iostream>
#include <memory>

glm::vec3 calculateColor(glm::uvec2 pos)
{
  auto x = pos.x;
  auto y = pos.y;

  if((x/16) % 2 == 0 ^ (y/16) % 2 == 0)
  {
    return {0,0,0};
  }
  else
  {
    return {1, 1, 1};
  }
}

int main()
{
  std::cout << "Hello World!" << std::endl;
    int width = 512;
    int height = 512;
    int channels = 3; // RGB
  
    auto pixels = std::make_unique<std::uint8_t[]>(width * height * channels);
    
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        const auto index = x + y * width;
        const auto color = calculateColor({x,y});
        pixels[index * 3 + 0] = color.x * 255;
        pixels[index * 3 + 1] = color.y * 255;
        pixels[index * 3 + 2] = color.z * 255;
      }
    }

    stbi_write_png("output.png", width, height, channels, pixels.get(), width * channels);
    return 0;
}
