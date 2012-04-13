// I2C, pin 4 == SDA, pin 5 == SCL

// 0111 A2 A1 A0 (pin 3 pin 2 pin 1)
#define IO_EXPANDER_ADDR ((0x7 << 3) | 0x7) 

// 00011110
#define MAGNETOMETER_ADDR 0x1E 