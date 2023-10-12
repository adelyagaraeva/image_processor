#pragma once
#include <vector>
#include <string>

const int B_INDEX = 0;
const int M_INDEX = 1;
const int INFO_HEADER_SIZE_BYTE = 0;
const int PLANES_BYTE_12 = 12;
const int PLANES_BYTE_13 = 13;
const int FILE_SIZE_BYTE_2 = 2;
const int FILE_SIZE_BYTE_3 = 3;
const int FILE_SIZE_BYTE_4 = 4;
const int FILE_SIZE_BYTE_5 = 5;
const int TOTAL_SIZE_IND = 10;
const int BYTE = 8;
const int TWO_BYTES = 16;
const int THREE_BYTES = 24;
const int WIDTH_OF_IMAGE_IND_4 = 4;
const int WIDTH_OF_IMAGE_IND_5 = 5;
const int WIDTH_OF_IMAGE_IND_6 = 6;
const int WIDTH_OF_IMAGE_IND_7 = 7;
const int LENGTH_OF_IMAGE_IND_8 = 8;
const int LENGTH_OF_IMAGE_IND_9 = 9;
const int LENGTH_OF_IMAGE_IND_10 = 10;
const int LENGTH_OF_IMAGE_IND_11 = 11;
const int PIXEL_DENSITY_IND = 14;
class OpenError {};
class WrongFileType {};

struct Color {
    float r_, g_, b_;
    Color();
    Color(float r, float b, float g);
    ~Color();
    bool operator!=(const Color& other) const;
};
class Image {
public:
    Image(int width, int length);
    ~Image();

    Color GetColor(int x, int y) const;
    int GetWidth() const;
    int GetLength() const;
    void SetWidth(int);
    void SetLength(int);
    void SetColor(const Color& color, int x, int y);
    void Write(const char* path) const;
    void Read(const std::string& path);
    std::vector<std::vector<Color>>& GetData();
    bool operator==(const Image& other) const;

private:
    int width_;
    int length_;
    std::vector<std::vector<Color>> colors_;
};
