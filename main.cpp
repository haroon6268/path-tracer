#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glm/glm.hpp"
#include <memory>

glm::vec3 calculateColor(glm::vec2 pixelCoord)
{
  return {pixelCoord * 2.f - 1.f, 1};
}

struct ray{
  glm::vec3 origin;
  glm::vec3 dir;
  glm::vec3 at(float t)
  {
    return origin + (t*dir) ;
  }
};

int main()
{
    int width = 512;
    int height = 512;
    int channels = 3; // RGB
  
    auto pixels = std::make_unique<std::uint8_t[]>(width * height * channels);
    
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        const auto index = x + y * width;
        glm::vec2 pixelCoord = {x,y};
        glm::vec2 extent = {width-1, height-1};
        const auto color = calculateColor({pixelCoord/extent});
        pixels[index * 3 + 0] = color.x * 255;
        pixels[index * 3 + 1] = color.y * 255;
        pixels[index * 3 + 2] = color.z * 255;
      }
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_png("output.png", width, height, channels, pixels.get(), width * channels);
    return 0;
}
