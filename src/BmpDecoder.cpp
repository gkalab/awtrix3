#include <cstring>

#include "BmpDecoder.h"

std::vector<uint16_t> BmpDecoder::extractImageData(const uint8_t bmp_data[], uint32_t data_size, int expectedWidth, int expectedHeight)
{
    if (data_size < sizeof(BMPFileHeader) + sizeof(BMPInfoHeader))
    {
        return {};
    }
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::memcpy(&fileHeader, bmp_data, sizeof(fileHeader));
    std::memcpy(&infoHeader, bmp_data + sizeof(fileHeader), sizeof(infoHeader));
    const int width = infoHeader.width;
    const int height = infoHeader.height;
    if (fileHeader.fileType != 0x4D42 // 'BM' in ASCII
        || width != expectedWidth || height != expectedHeight || infoHeader.bitCount != 16)
    {
        return {};
    }

    const int rowPadding = (4 - (width * 2 % 4)) % 4;
    std::vector<uint16_t> imageData(width * height);
    const uint8_t *pixelData = bmp_data + fileHeader.offsetData;
    for (int y = 0; y < height; y++)
    {
        const uint8_t *rowPtr = pixelData + y * (width * 2 + rowPadding);
        for (int x = 0; x < width; x++)
        {
            uint16_t pixel;
            std::memcpy(&pixel, rowPtr + x * 2, sizeof(pixel));
            imageData[(height - 1 - y) * width + x] = pixel;
        }
    }
    return imageData;
}
