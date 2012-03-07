
// standby pins on BOTH motor drivers need to tie to HIGH for operation.
// direction CCW/CW control for motors through I2C
#define A1_IN1_I2C_BIT  1    // pin 4    
#define A1_IN2_I2C_BIT  0    // pin 5
#define B1_IN1_I2C_BIT  3    // pin 7
#define B1_IN2_I2C_BIT  2    // pin 6
#define A2_IN1_I2C_BIT  5    // pin 10
#define A2_IN2_I2C_BIT  4    // pin 9
#define B2_IN1_I2C_BIT  7    // pin 12
#define B2_IN2_I2C_BIT  6    // pin 11

// PWM control for motors
#define OUT_A1_PWM_PIN  5    // PWM_1_A
#define OUT_B1_PWM_PIN  6    // PWM_1_B
#define OUT_A2_PWM_PIN  9    // PWM_2_A
#define OUT_B2_PWM_PIN  10   // PWM_2_B
 
// Analog pin 4 to pin 15
// Analog pin 5 to pin 14

#define VERTICAL     0
#define SIDE         1
#define FRONT_LEFT   2
#define FRONT_RIGHT  3

#define VERTICAL_MOTOR     OUT_A1_PWM_PIN
#define SIDE_MOTOR         OUT_B1_PWM_PIN
#define FRONT_LEFT_MOTOR   OUT_A2_PWM_PIN
#define FRONT_RIGHT_MOTOR  OUT_B2_PWM_PIN

#define GET_MOTOR(x)           ((x & 0xC0) >> 6)
#define GET_MOTOR_DIRECTION(x) ((x & 0x20) >> 5)  // 1 is CCW, 0 CW
#define GET_MOTOR_VAL(x)       ((x & 0x1F) << 3) 
