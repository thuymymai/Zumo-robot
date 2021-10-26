/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "kinh.h"

void assignment1(void) {
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(100,3400);     // moving forward
    motor_turn(72,20,1004); 
    motor_forward(100,2400);// turn
    motor_turn(72,20,1004); 
    motor_forward(100,2530);// turn
    motor_turn(50,20,2060);
    motor_turn(70,60,2400);
    motor_turn(50,20,660);
    motor_forward(100,1100);
    
    //motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
}

void tankturn(void) {
    int n, upper, lower; 
    lower = 262;
    upper = 786;
    n = (rand() % (upper-lower+1)) + lower;
    SetMotors(0,0,0,100,n);
    SetMotors(1,1,100,0,n);
}
    
void assignment3(void) {
    Ultra_Start();                          // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    vTaskDelay(3000);
    
    while(true) {
        motor_forward(150,50);
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        if (d<=10) {
            motor_forward(0,0);
            motor_backward(30,500);
            tankturn();
        }
    }
}
    
    
/* [] END OF FILE */
