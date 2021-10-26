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
#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void mymPrint(void);
void motorRun(void);
void grid(void);
void mqtt3(void);
void sumo(void);
void assignment2(void);
void motorRun(void);
void assignment4(void);
void assignment5(void);
void w4Task1(void);
void themaze(void);
void obstacle(int x);
void move_per_block(void) ;
void random_turn_right(void);
void random_turn_left(void);





/* [] END OF FILE */
