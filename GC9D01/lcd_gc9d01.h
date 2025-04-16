#pragma once

#include "lcd_gc9d01_config.h"

typedef struct {
    uint16_t width;
    uint16_t height;
} Screen_Size;


class LCD_GC9D01{
    
    protected:
        uint8_t* screen_buffer;
        size_t buffer_size;

        void SendData(uint8_t* data, size_t len);
        void SendCommand(uint8_t cmd);

    public: 
        LCD_GC9D01();

        void Init();

        void Config(uint8_t cmd, size_t len, uint8_t* value);

        void Config(uint8_t cmd);

        void CursorPos(uint16_t x, uint16_t y);

        void DrawRange(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

        void Pixel(uint16_t x, uint16_t y, uint16_t color);

        void Write(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* image);

        void Draw();

        void Clear(uint16_t color);

        bool IsOutOfBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

        uint8_t *GetBuffer();

        Screen_Size GetScreenSize();

        ~LCD_GC9D01();
};
