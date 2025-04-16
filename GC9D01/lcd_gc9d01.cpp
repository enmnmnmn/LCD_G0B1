#include "lcd_gc9d01.h"


LCD_GC9D01::LCD_GC9D01()
{
	screen_buffer = new uint8_t[(SCREEN_WIDTH* SCREEN_HEIGHT)* 2];
	buffer_size = (SCREEN_WIDTH * SCREEN_HEIGHT)* 2;
}

void LCD_GC9D01::SendData(uint8_t* data, size_t len)
{
    if (len == 0) return;

    LCD_DC(1);
    LCD_CS(0);
    HAL_SPI_Transmit_DMA(&LCD_SPI, data, len);
	while (HAL_SPI_GetState(&LCD_SPI) != HAL_SPI_STATE_READY);
    LCD_CS(1);
}

void LCD_GC9D01::SendCommand(uint8_t cmd)
{
    LCD_DC(0);
    LCD_CS(0);
    HAL_SPI_Transmit_DMA(&LCD_SPI, &cmd, 1);
    LCD_CS(1);
}

void LCD_GC9D01::Config(uint8_t cmd, size_t len, uint8_t* value)
{
    LCD_DC(0);
    LCD_CS(0);
    HAL_SPI_Transmit_DMA(&LCD_SPI, &cmd, 1);
	while (HAL_SPI_GetState(&LCD_SPI) != HAL_SPI_STATE_READY);
    
    LCD_DC(1);
    HAL_SPI_Transmit_DMA(&LCD_SPI, value, len);
	while (HAL_SPI_GetState(&LCD_SPI) != HAL_SPI_STATE_READY);
    LCD_CS(1);
}

void LCD_GC9D01::Config(uint8_t cmd)
{
	LCD_DC(0);
    LCD_CS(0);
    HAL_SPI_Transmit_DMA(&LCD_SPI, &cmd, 1);
    LCD_CS(1);
}

void LCD_GC9D01::Init()
{

    MX_SPI1_Init();
    MX_GPIO_Init();

	Delay(10);


    LCD_RES(0);
    Delay(10);
    LCD_RES(1);
    Delay(10);
	
	SendCommand(0xFE); //Inter Register Enable1	
	SendCommand(0xEF); //Inter Register Enable2

	
	 //内部寄存器使能80~8Fh
	Config(0x80, 1, (uint8_t[]){0xFF});
	Config(0x81, 1, (uint8_t[]){0xFF});
	Config(0x82, 1, (uint8_t[]){0xFF});
	Config(0x83, 1, (uint8_t[]){0xFF});
	Config(0x84, 1, (uint8_t[]){0xFF});
	Config(0x85, 1, (uint8_t[]){0xFF});
	Config(0x86, 1, (uint8_t[]){0xFF});
	Config(0x87, 1, (uint8_t[]){0xFF});
	Config(0x88, 1, (uint8_t[]){0xFF});
	Config(0x89, 1, (uint8_t[]){0xFF});
	Config(0x8a, 1, (uint8_t[]){0xFF});
	Config(0x8b, 1, (uint8_t[]){0xFF});
	Config(0x8c, 1, (uint8_t[]){0xFF});
	Config(0x8d, 1, (uint8_t[]){0xFF});
	Config(0x8e, 1, (uint8_t[]){0xFF});
	Config(0x8f, 1, (uint8_t[]){0xFF});
	
	Config(0x3A, 1, (uint8_t[]){0x05, });
	
	//设置翻转方式
	Config(0xEC, 1, (uint8_t[]){0x11, });

	//VGL大小
	Config(0x7E, 1, (uint8_t[]){0x7a, });
	
	//修改帧频
	Config(0x74, 7, (uint8_t[]){0x02, 0x0E, 0x00, 0x00, 0x28, 0x00, 0x00, });
	
	//内部电压调整
	Config(0x98, 1, (uint8_t[]){0x3E, });
	Config(0x99, 1, (uint8_t[]){0x3E, });
	 
	//内部porch设置
	Config(0xB5, 2, (uint8_t[]){0x0E, 0x0E, });
//	Config(0xB5, 3, (uint8_t[]){0x08, 0x08, 0x14});//default value
	
	//gip timing start
	Config(0x60, 4, (uint8_t[]){0x38, 0x09, 0x6D, 0x67,});	
	Config(0x63, 5, (uint8_t[]){0x38, 0xAD, 0x6D, 0x67, 0x05, });
	Config(0x64, 6, (uint8_t[]){0x38, 0x0B, 0x70, 0xAB, 0x6D, 0x67, });
	Config(0x66, 6, (uint8_t[]){0x38, 0x0F, 0x70, 0xAF, 0x6d, 0x67, });	
	Config(0x6A, 2, (uint8_t[]){0x00, 0x00, });
	Config(0x68, 7, (uint8_t[]){0x3B, 0x08, 0x04, 0x00, 0x04, 0x64, 0x67, });	
	Config(0x6C, 6, (uint8_t[]){0x22, 0x02, 0x02, 0x22, 0x22, 0x50, });	
	Config(0x6E, 32, (uint8_t[]){
		0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x13, 0x11, 
		0x0B, 0x09, 0x16, 0x15, 0x1D, 0x1E, 0x00, 0x00, 
		0x00, 0x00, 0x1E, 0x1D, 0x15, 0x16, 0x0A, 0x0C, 
		0x12, 0x14, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 	
	});
	
	//gip timing end
	//内部电压设定开始
	Config(0xA9, 1, (uint8_t[]){0x1B, });
	Config(0xA8, 1, (uint8_t[]){0x6B, });
	Config(0xA8, 1, (uint8_t[]){0x6D, });
	Config(0xA7, 1, (uint8_t[]){0x40, });
	Config(0xAD, 1, (uint8_t[]){0x47, });
	Config(0xAF, 1, (uint8_t[]){0x73, });
	Config(0xAF, 1, (uint8_t[]){0x73, });
	Config(0xAC, 1, (uint8_t[]){0x44, });
	Config(0xA3, 1, (uint8_t[]){0x6C, });
	Config(0xCB, 1, (uint8_t[]){0x00, });
	Config(0xCD, 1, (uint8_t[]){0x22, });
	Config(0xC2, 1, (uint8_t[]){0x10, });
	Config(0xC5, 1, (uint8_t[]){0x00, });
	Config(0xC6, 1, (uint8_t[]){0x0E, });
	Config(0xC7, 1, (uint8_t[]){0x1f, });
	Config(0xC8, 1, (uint8_t[]){0x0E, });
	
	//内部电压设定结束
	//选择single gate mode
	Config(0xbf, 1, (uint8_t[]){0x00, });

	//SOU相关调整
	Config(0xF9, 1, (uint8_t[]){0x20, });
	
	//vreg电压调整
	Config(0x9b, 1, (uint8_t[]){0x3b, });
	Config(0x93, 3, (uint8_t[]){0x33, 0x7f, 0x00, });
	
	//VGH/VGL CLK调整70，71h
	Config(0x70, 6, (uint8_t[]){0x0E, 0x0f, 0x03, 0x0e, 0x0f, 0x03, });
	Config(0x71, 3, (uint8_t[]){0x0e, 0x16, 0x03, });
	
	//内部电压调整
	Config(0x91, 2, (uint8_t[]){0x0e, 0x09});
	
	//vreg电压调整
	Config(0xc3, 1, (uint8_t[]){0x2c, });
	Config(0xc4, 1, (uint8_t[]){0x1a, });
	
	//gamma F1~F3h
	Config(0xf0, 6, (uint8_t[]){0x51, 0x13, 0x0c, 0x06, 0x00, 0x2f, });	 
	Config(0xf2, 6, (uint8_t[]){0x51, 0x13, 0x0c, 0x06, 0x00, 0x33, });
	Config(0xf1, 6, (uint8_t[]){0x3c, 0x94, 0x4f, 0x33, 0x34, 0xCf, });
	Config(0xf3, 6, (uint8_t[]){0x4d, 0x94, 0x4f, 0x33, 0x34, 0xCf, });
	
	//内存访问控制
	Config(0x36, 1, (uint8_t[]){
		// 0xC0,
      	// 0x60,
      	// 0xA0,
      	// 0x00,
		0x20,
	});
	
	SendCommand(0x11); //休眠模式
	Delay(1); 
	SendCommand(0x29); //显示器打开
	
	SendCommand(0x2C); //内存写入

	LCD_CS(1);
	Delay(1); 
	Clear(LCD_COLOR_WHITE);
}

bool LCD_GC9D01::IsOutOfBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	return (x > SCREEN_WIDTH || y > SCREEN_HEIGHT || x + width > SCREEN_WIDTH || y + height > SCREEN_HEIGHT);
}

uint8_t* LCD_GC9D01::GetBuffer()
{
	return screen_buffer;
}

Screen_Size LCD_GC9D01::GetScreenSize()
{
	return (Screen_Size){SCREEN_WIDTH, SCREEN_HEIGHT};
}

void LCD_GC9D01::CursorPos(uint16_t x, uint16_t y)
{
	x = 0, y = 0;
	uint16_t x1 = SCREEN_WIDTH - 1;
	uint16_t y1 = SCREEN_HEIGHT - 1;
	if(x > x1){
		uint16_t temp = x1;
		x1 = x;
		x1 = temp;
	}	
	if(y > y1){
		uint16_t temp = y1;
		y1 = y;
		y1 = temp;
	}

	uint8_t data0[4] = {0x00, 196, 0x01, 99}, data1[4] = {0x00, 60, 0x00, 99};
	// uint8_t data0[4] = {0x00, 0, 0x00, 40}, data1[4] = {0x00, 0, 0x00, 160};

	
	Config(0x2A, 4, data0);
	Config(0x2B, 4, data1);
	
	Config(0x2C);
}

void LCD_GC9D01::DrawRange(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    uint8_t data0[8] = {0x00, 0, 0x00, 40, 0x00, 0, 0x00, 160};

	Config(0x2B, 4, data0);
	Config(0x2A, 4, &data0[4]);

	SendCommand(0x2C);
}

void LCD_GC9D01::Pixel(uint16_t x, uint16_t y, uint16_t color)
{
	if (IsOutOfBounds(x, y, 0, 0)) return;
	size_t offset;

	x = SCREEN_WIDTH - x - 1;

	offset = (((SCREEN_WIDTH * y)+ x)* 2);
	screen_buffer[offset] = color >> 8;
	screen_buffer[offset + 1] = color;
}

void LCD_GC9D01::Write(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* image)
{
	size_t offset;
	uint16_t tmp;
	uint16_t width_new = (x + width > SCREEN_WIDTH) ? SCREEN_WIDTH - x : width;
	uint16_t height_new = (y + height > SCREEN_HEIGHT) ? SCREEN_HEIGHT - x : height;
	
	for (size_t _y = 0; _y < height_new; _y++) {
		for (size_t _x = 0; _x < width_new; _x++) {
			if (IsOutOfBounds(x, y, _x + 1, _y + 1)) continue;
			offset = ((_x* 2)+((width * 2)* _y));
			tmp = image[offset] << 8;
			tmp |= image[offset + 1];
			Pixel(x + _x, y + _y, tmp);
		}
	}
}

void LCD_GC9D01::Draw()
{
	CursorPos(0, 0);
	Config(0x2C);
	
	SendData(screen_buffer, buffer_size);
}

void LCD_GC9D01::Clear(uint16_t color)
{
	CursorPos(0, 0);
    uint8_t _color[2];
    _color[0] = color >> 8;
    _color[1] = color;

	for (size_t i = 0; i <(SCREEN_WIDTH * SCREEN_HEIGHT)* 2; i += 2) {
		screen_buffer[i] = _color[0];
		screen_buffer[i + 1] = _color[1];
	}
}

LCD_GC9D01::~LCD_GC9D01()
{
	delete[] screen_buffer;
	HAL_SPI_MspDeInit(&LCD_SPI);
    return;
}
