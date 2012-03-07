// Serial & SoftwareSerial
#define MONITOR_RX_PORT 2
#define MONITOR_TX_PORT 3
#define MONITOR_BDRATE 57600
#define WIFLY_BDRATE 115200

// I2C, pin 4 == SDA, pin 5 == SCL
#define IO_EXPANDER_ADDR ((0x7 << 3) | 0x7) // 0111 A2 A1 A0 (pin 3 pin 2 pin 1)

// UDP
#define LOCAL_PORT   9999
#define REMOTE_PORT  9876
#define REMOTE_IP    192.168.2.7
