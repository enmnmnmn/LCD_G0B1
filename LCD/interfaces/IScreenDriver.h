#pragma once
#include <stdint.h>
#include <stddef.h>


typedef struct {
    uint16_t width;
    uint16_t height;
} Screen_Size;

class IScreenDriver {
    public:
        void virtual Init() = 0;
        void virtual Config(uint8_t cmd, size_t len, uint8_t* value) = 0;
        void virtual Config(uint8_t cmd) = 0;
        void virtual CursorPos(uint16_t x, uint16_t y) = 0;
        void virtual DrawRange(uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
        void virtual Pixel(uint16_t x, uint16_t y, uint8_t* data) = 0;
        void virtual Write(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* image) = 0;
        void virtual Draw() = 0;
        void virtual Clear(uint16_t color) = 0;
        bool virtual IsOutOfBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
        uint8_t virtual *GetBuffer() = 0;
        Screen_Size virtual GetScreenSize() = 0;
        virtual ~IScreenDriver() = default;
};
