#include "Image.h"
#include <fstream>
#include <iostream>
#include <vector>

const float EPS = 0.5;
const int BYTES = 3;
const int MODULE = 4;
Color::Color() {
    r_ = 0;
    g_ = 0;
    b_ = 0;
}
Color::Color(float r, float b, float g) {
    r_ = r;
    g_ = g;
    b_ = b;
}
Color::~Color() = default;
bool Color::operator!=(const Color& other) const {
    return (!((std::abs(other.r_ - r_) < EPS) && (std::abs(other.b_ - b_) < EPS) && (std::abs(other.g_ - g_) < EPS)));
};

Image::Image(int width, int length) {
    width_ = width;
    length_ = length;
    colors_ = std::vector<std::vector<Color>>(length, std::vector<Color>(width));
}

Image::~Image() = default;

Color Image::GetColor(int x, int y) const {
    return colors_[y][x];
}
bool Image::operator==(const Image& other) const {
    if (other.GetLength() == length_ && other.GetWidth() == width_) {
        for (int y = 0; y < length_; y++) {
            for (int x = 0; x < width_; x++) {
                if (colors_[y][x] != other.GetColor(x, y)) {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

void Image::SetColor(const Color& color, int x, int y) {
    colors_[y][x].r_ = color.r_;
    colors_[y][x].g_ = color.g_;
    colors_[y][x].b_ = color.b_;
}
int Image::GetWidth() const {
    return width_;
};
int Image::GetLength() const {
    return length_;
};
std::vector<std::vector<Color>>& Image::GetData() {
    return colors_;
};
void Image::SetWidth(int value) {
    width_ = value;
};
void Image::SetLength(int value) {
    length_ = value;
};
void Image::Read(const std::string& path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw OpenError();
    }
    const int file_size_header = 14;
    unsigned char file_header[file_size_header];
    file.read(reinterpret_cast<char*>(file_header), file_size_header);

    if ((file_header[B_INDEX] != 'B') || (file_header[M_INDEX] != 'M')) {
        file.close();
        throw WrongFileType();
    }
    const int information_header_size = 40;

    unsigned char info_header[information_header_size];
    file.read(reinterpret_cast<char*>(info_header), information_header_size);

    width_ = info_header[WIDTH_OF_IMAGE_IND_4] + (info_header[WIDTH_OF_IMAGE_IND_5] << BYTE) +
             (info_header[WIDTH_OF_IMAGE_IND_6] << TWO_BYTES) + (info_header[WIDTH_OF_IMAGE_IND_7] << THREE_BYTES);
    length_ = info_header[LENGTH_OF_IMAGE_IND_8] + (info_header[LENGTH_OF_IMAGE_IND_9] << BYTE) +
              (info_header[LENGTH_OF_IMAGE_IND_10] << TWO_BYTES) + (info_header[LENGTH_OF_IMAGE_IND_11] << THREE_BYTES);
    colors_ = std::vector<std::vector<Color>>(length_, std::vector<Color>(width_));
    const int indent_size = ((MODULE - (width_ * BYTES) % MODULE) % MODULE);

    for (int y = 0; y < length_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char color[3];
            const float normalise = 255.0f;
            file.read(reinterpret_cast<char*>(color), 3);
            colors_[y][x].r_ = static_cast<float>(color[2]) / normalise;
            colors_[y][x].g_ = static_cast<float>(color[1]) / normalise;
            colors_[y][x].b_ = static_cast<float>(color[0]) / normalise;
        }
        file.ignore(indent_size);
    }
    file.close();
    std::cout << "Red successfully" << std::endl;
};
void Image::Write(const char* path) const {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw OpenError();
    }

    unsigned char indent[] = {0, 0, 0};
    const int indent_size = ((MODULE - (width_ * BYTES) % MODULE) % MODULE);

    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + width_ * length_ * 3 + indent_size * width_;

    unsigned char file_header[file_header_size];

    for (size_t i = 0; i < file_header_size; ++i) {
        file_header[i] = 0;
    }
    file_header[B_INDEX] = 'B';
    file_header[M_INDEX] = 'M';

    const auto binary_const = 0xFF;
    file_header[FILE_SIZE_BYTE_2] = file_size;
    file_header[FILE_SIZE_BYTE_3] = file_size >> BYTE;
    file_header[FILE_SIZE_BYTE_4] = file_size >> TWO_BYTES;
    file_header[FILE_SIZE_BYTE_5] = file_size >> THREE_BYTES;
    file_header[TOTAL_SIZE_IND] = file_header_size + info_header_size;

    unsigned char information_header[info_header_size];

    for (size_t i = 0; i < info_header_size; ++i) {
        information_header[i] = 0;
    }

    information_header[INFO_HEADER_SIZE_BYTE] = info_header_size;

    information_header[WIDTH_OF_IMAGE_IND_4] = width_;
    information_header[WIDTH_OF_IMAGE_IND_5] = (width_ >> BYTE) & binary_const;
    information_header[WIDTH_OF_IMAGE_IND_6] = (width_ >> TWO_BYTES) & binary_const;
    information_header[WIDTH_OF_IMAGE_IND_7] = (width_ >> THREE_BYTES) & binary_const;

    information_header[LENGTH_OF_IMAGE_IND_8] = length_;
    information_header[LENGTH_OF_IMAGE_IND_9] = (length_ >> BYTE) & binary_const;
    information_header[LENGTH_OF_IMAGE_IND_10] = (length_ >> TWO_BYTES) & binary_const;
    information_header[LENGTH_OF_IMAGE_IND_11] = (length_ >> THREE_BYTES) & binary_const;
    information_header[PLANES_BYTE_12] = 1;
    information_header[PLANES_BYTE_13] = 0;
    const int pixel_density = 24;
    information_header[PIXEL_DENSITY_IND] = pixel_density;

    file.write(reinterpret_cast<char*>(file_header), file_header_size);
    file.write(reinterpret_cast<char*>(information_header), info_header_size);

    for (int y = 0; y < length_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const float normalise = 255.0f;
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r_ * normalise);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g_ * normalise);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b_ * normalise);

            unsigned char color[] = {b, g, r};
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char*>(indent), indent_size);
    }

    file.close();
    std::cout << "Created successfully";
}
