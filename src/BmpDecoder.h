#pragma once

#include <cstdint>
#include <vector>

class BmpDecoder
{
public:
    std::vector<uint16_t> extractImageData(const uint8_t bmp_data[], uint32_t data_size, int expectedWidth, int expectedHeight);

private:
#pragma pack(push, 1)
    struct BMPFileHeader
    {
        uint16_t fileType;
        uint32_t fileSize;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offsetData;
    };

    struct BMPInfoHeader
    {
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bitCount;
        uint32_t compression;
        uint32_t imageSize;
        int32_t xPixelsPerMeter;
        int32_t yPixelsPerMeter;
        uint32_t colorsUsed;
        uint32_t colorsImportant;
    };
#pragma pack(pop)
};
