// Serial & SoftwareSerial
#define MONITOR_RX_PORT 2
#define MONITOR_TX_PORT 3
#define MONITOR_BDRATE 57600
#define WIFLY_BDRATE   57600


SoftwareSerial monitorSerial(MONITOR_RX_PORT, MONITOR_TX_PORT);
int iIncomingByte = 0;
int i = 0;


