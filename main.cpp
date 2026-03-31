#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include "glm/glm.hpp"
#include <memory>

struct ray{
  glm::vec3 origin;
  glm::vec3 dir;
  glm::vec3 at(float t)
  {
    return origin + (t*dir) ;
  }
};

glm::vec3 calculateColor(ray ray)
{
  glm::vec3 unitVector = glm::normalize(ray.dir);
  auto a = 0.5f * (unitVector.y + 1.0f);
  return (1.0f-a) * glm::vec3{1.0f, 1.0f, 1.0f} + a*glm::vec3{0.5f, 0.7f, 1.0f};
}

int main(int argc, char* argv[])
{
    double aspectRatio = 16.0/9.0;
    int width = 400;

    int height = static_cast<int>(width / aspectRatio);
    height = height < 1 ? 1 : height;
  

    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (static_cast<double>(width)/height);
    double focalLength = 1.0;
    glm::vec3 cameraCenter{0, 0, 0};
    
    glm::vec3 viewportU {viewportWidth, 0, 0};
    glm::vec3 viewportV {0, -viewportHeight, 0};

    glm::vec3 pixelDeltaU {viewportU / static_cast<float>(width)};
    glm::vec3 pixelDeltaV {viewportV / static_cast<float>(height)};

    glm::vec3 viewportUpperLeft {cameraCenter - glm::vec3(0, 0, focalLength) - viewportU/2.0f - viewportV/2.0f};
    glm::vec3 pixel00Loc {viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV)};




    int channels = 3; // RGB
  
    auto pixels = std::make_unique<std::uint8_t[]>(width * height * channels);
    
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        const auto index = x + y * width;


        glm::vec3 pixelCenter {pixel00Loc + (static_cast<float>(x) * pixelDeltaU) + (static_cast<float>(y) * pixelDeltaV)};
        glm::vec3 rayDirection {pixelCenter - cameraCenter};
        ray r {cameraCenter, rayDirection};
        
        const auto color = calculateColor(r);
        pixels[index * 3 + 0] = color.x * 255;
        pixels[index * 3 + 1] = color.y * 255;
        pixels[index * 3 + 2] = color.z * 255; 
      }
    }
    stbi_write_png("output.png", width, height, channels, pixels.get(), width * channels);

    std::cout << "finished" << std::endl;
    return 0;
}
