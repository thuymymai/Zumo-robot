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
#include"anhuynh.h"


//An Huynh week 3 assignment 2
void w3Task2(void){
    Ultra_Start();
    motor_start(); //enable motor controller
    motor_forward(0,0); //set initial speed to zero
    vTaskDelay(3000);

    while(true){
        motor_forward(130,10);
        int d = Ultra_GetDistance();
        printf("distance = %d\r\n",d);
        if (d<=10) {
            motor_backward(0,0);
            motor_backward(35,300);

            motor_turn(0,65,1067);
        }
    }

}

// An Huynh week 4 assignment 2


#define STOP 2
 void w4Task2(void){
    struct sensors_ dig;
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    reflectance_start();
    IR_Start();
    motor_start();
    motor_forward(0,0);

    while(SW1_Read());
    vTaskDelay(1000);

    motor_forward(100,0);
    reflectance_digital(&dig);

    int count = 0;
    int line = 0;
    while(count < STOP){
             reflectance_digital(&dig);

            if((dig.L3 == 1) && (dig.L2 == 1) && (dig.L1 == 1) && (dig.R1 == 1) && (dig.R2 == 1) && (dig.R3 == 1)){
                count++;
                if(count == 1){
                    line = 1;
                }
                while((dig.L3 == 1) && (dig.L2 == 1) && (dig.L1 == 1) && (dig.R1 == 1) && (dig.R2 == 1) && (dig.R3 == 1) && count<STOP){
                    reflectance_digital(&dig);
                 }
             }
            if (line == 1){
                motor_forward(0,0);
                IR_wait();
                motor_forward(100,0);
                line = 0;
                while(true){
                    reflectance_digital(&dig);
                    motor_forward(100,0);
                    if(dig.L1 == 0 && dig.R1 == 1) {

                        SetMotors(0, 1, 20, 10, 10);
                     }
                    if(dig.L1 == 1 && dig.R1 == 0) {

                        SetMotors(1, 0, 10, 20, 10);
                    }
                    if(dig.R1 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1) {
                        SetMotors(1, 0, 100, 100, 262);
                        }
                    if(dig.L1 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
                        SetMotors(0, 1, 100, 100, 262);
                        }
                    if(dig.L3 == 1 && dig.R3 == 1) {
                        motor_forward(0,0);
                        motor_stop();
                        break;
                     }
                }

            }
        }
    motor_forward(0,0);
    motor_stop();
    while(true) {
        vTaskDelay(100);
    }
}
// An Huynh: Week 5 Assignment 1
void w5Task1 (void) {
    TickType_t timeMeasure = xTaskGetTickCount();
    TickType_t start_time = 0;
    while (true){
        while(SW1_Read());
        vTaskDelay(100);
        timeMeasure = xTaskGetTickCount();
        int interval = timeMeasure - start_time;
        print_mqtt("Zumo04/button", "Time interval is: %d milliseconds", interval);
        while(!SW1_Read());
        vTaskDelay(100);
        start_time = timeMeasure;
    }
}
//Kinh Truong week 4 assignment 1
void task1w4(void){
    struct sensors_ dig;
    int count = 0;
    int first = 0;

    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);

    reflectance_start();
    IR_Start();
    motor_start();
    motor_forward(0,0);

    while(SW1_Read());
    BatteryLed_Write(1);
    vTaskDelay(1000);
    BatteryLed_Write(0);

    reflectance_digital(&dig);
    motor_forward(100,0);

    while (count <= 5) {
        reflectance_digital(&dig);
        if(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
           count++;
            if (count == 1) {
                first = 1;
            }
            while ((dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) && count < 5){
             reflectance_digital(&dig);
            }
    }
        if (first == 1){
            motor_forward(0,0);
            IR_wait();
            motor_forward(100,0);
            first = 0;
        }
    }

    motor_forward(0,0);
    motor_stop();
}
//Kinh Truong week 5 assignment 2
void w5Task2(void) {

 	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);

    while(true) {

       motor_forward(100,10);
       int d = Ultra_GetDistance();
       if (d<=10) {
			motor_forward(0,0);
            motor_backward(30,500);
			int random;
   	        random = rand()%2;
            if (random == 0) {
		        random_turn_right();
		        print_mqtt("Zumo04/turn", "right");

                }
	        else {
		        random_turn_left();
		        print_mqtt("Zumo04/turn", "left");
                }
        }
    }
}


// An Huynh: line follower project
#define WAIT 1
#define END 3


void lineFollower()
{
    struct sensors_ dig;


    int count = 0, first = 0;
    int timestart;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);

    motor_start();
    IR_Start();
    motor_forward(0,0);

    motor_forward(255, 0);
    while(count < END)
    {
        reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1)
        {
            motor_forward(255,0);
        }

        if(dig.L1 == 0 && dig.R1 == 1) {

            SetMotors(0, 1, 100, 50, 20);

        }
        if(dig.L1 == 1 && dig.R1 == 0) {

            SetMotors(1, 0, 50, 100, 20);

        }
        if(dig.R1 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1) {

            SetMotors(1, 0, 100, 200, 20);

        }
        if(dig.L1 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {

            SetMotors(0, 1, 200, 100, 20);

        }

        if(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            count++;
            if (count == 1) {
                first = 1;
            }
            while(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1 && count < END)
            {
                reflectance_digital(&dig);
            }
        }
        if (first == 1) {
            motor_forward(0,0);
            print_mqtt("Zumo04/ready", "line %d", count);
            IR_wait();
            motor_forward(255,0);
            TickType_t startTime = xTaskGetTickCount();
            print_mqtt("Zumo04/start", "%d", startTime);
            timestart = startTime;
            first = 0;
        }

    }
    motor_forward(0,0);
    motor_stop();

    TickType_t stopTime = xTaskGetTickCount();
    print_mqtt("Zumo04/stop", "%d", stopTime);
    print_mqtt("Zumo04/time", "%d", stopTime - timestart);
}




void random_turn_right(void) {
	SetMotors(0,1,100,100,262);
	SetMotors(0,0,0,0,0);
}
void random_turn_left(void) {
	SetMotors(1,0,100,100,262);
	SetMotors(0,0,0,0,0);
}
// The maze project: contributed by  Kinh Truong
void themaze2(void) {

 	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);
    int x = 0 , y = 0;

    struct sensors_ dig;


    int count = 0, first = 0;
    int  turn = 0, coordinate = 0;
    int direction = 0;
    int timestart = 0;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    IR_Start();



    while(y < 13) {

       reflectance_digital(&dig);
       if (dig.L1 == 1 && dig.R1 == 1)
        {
            motor_forward(150,0);
        }

       if(dig.L1 == 0 && dig.R1 == 1) {

            SetMotors(0, 1, 100, 50, 20);

        }
       if(dig.L1 == 1 && dig.R1 == 0) {

            SetMotors(1, 0, 50, 100, 20);

        }

       int d = Ultra_GetDistance();
        if (d<=6 && coordinate == 1 && direction == 0) {
                random_turn_left();
                turn++;
                coordinate = turn%2;
            }
        if (d<=6 && coordinate == 1 && direction == 1) {
                random_turn_right();
                turn++;
                coordinate = turn%2;
            }
        if (d<=6 && x == 3) {
            motor_forward(0,0);

            random_turn_left();
            turn++;
            coordinate = turn%2;

        }

        if (d<=6 && x == -3) {
            motor_forward(0,0);

            random_turn_right();
            turn++;
            coordinate = turn%2;

        }

       if (d<=3) {
			motor_forward(0,0);
            motor_backward(30,500);
            int random;
   	        random = rand()%2;
            direction = random;

            if (random == 0) {
		        random_turn_right();
		        turn++;
                coordinate = turn%2;

                }
	        else {
		        random_turn_left();
                turn++;
                coordinate = turn%2;

                }


        }
       else {
            motor_forward(150,0);
        }

        if(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            count++;
            if (count == 1) {
                first = 1;
            }
            if (coordinate == 0) {
                y++;
                print_mqtt("Zumo04/position", "x = %d, y = %d\n",x,y);
            }
            else if (coordinate == 1 && direction == 0) {
                x++;
                print_mqtt("Zumo04/position", "x = %d, y = %d\n",x,y);
            }
            else if (coordinate == 1 && direction == 1) {
                x--;
                print_mqtt("Zumo04/position", "x = %d, y = %d\n",x,y);
            }

             if (x == 3)
            {
                motor_forward(150,150);
                random_turn_left();
                turn++;
                coordinate = turn%2;
                direction = 1;


            }
            if (x == -3)
            {
                motor_forward(150,150);
                random_turn_right();
                turn++;
                coordinate = turn%2;
                direction = 0;

            }
            if (y == 11 && x < 0 && coordinate == 0) {
                motor_forward(150,120);
                random_turn_right();
                turn++;
                coordinate = turn%2;
                direction = 0;
            }
            if (y == 11 && x > 0 && coordinate == 0) {
                motor_forward(150,120);
                random_turn_left();
                turn++;
                coordinate = turn%2;
                direction = 1;
            }
            if (y == 11 && x == 0 && direction == 1) {
                motor_forward(150,150);
                random_turn_right();
                turn++;
                coordinate = turn%2;

            }
            if (y == 11 && x == 0 && direction == 0) {
                motor_forward(150,150);
                random_turn_left();
                turn++;
                coordinate = turn%2;

            }

            if (count == 2) {
                x = 0;
                y = 0;

            }
            while(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
        }
        if(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {


            if (coordinate == 0) {
                y++;
                print_mqtt("Zumo04/position", "x = %d, y = %d\n",x,y);
            }
            while(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
            if (y == 11 && x == -3) {
                motor_forward(150,120);
                random_turn_right();
                turn++;
                coordinate = turn%2;
                direction = 0;
            }
        }
        if (dig.R3 == 0 && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
        {


            if (coordinate == 0) {
                y++;
                print_mqtt("Zumo04/position", "x = %d, y = %d\n",x,y);
            }
            while(dig.R3 == 0  && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
            {
                reflectance_digital(&dig);
            }
            if (y == 11 && x == 3) {
                motor_forward(150,120);
                random_turn_left();
                turn++;
                coordinate = turn%2;
                direction = 1;
            }


        }
        if (first == 1) {
            motor_forward(0,0);
            print_mqtt("Zumo04/ready", "maze");
            IR_wait();
            motor_forward(150,0);
            TickType_t startTime = xTaskGetTickCount();
            print_mqtt("Zumo04/start", "%d", startTime);
            timestart = startTime;
            first = 0;
        }

    }
    while (y == 13) {
        reflectance_digital(&dig);
       if (dig.L1 == 1 && dig.R1 == 1)
        {
            motor_forward(150,0);
        }

       if(dig.L1 == 0 && dig.R1 == 1) {

            SetMotors(0, 1, 100, 50, 20);

        }
       if(dig.L1 == 1 && dig.R1 == 0) {

            SetMotors(1, 0, 50, 100, 20);

        }
        if(dig.L3 == 0 && dig.L1 == 0 && dig.R3 == 0 && dig.R1 == 0) {
            motor_forward(0,0);
            y++;
        }
    }
    motor_forward(0,0);
    motor_stop();

    TickType_t stopTime = xTaskGetTickCount();
    print_mqtt("Zumo04/stop", "%d", stopTime);
    print_mqtt("Zumo04/time", "%d", stopTime - timestart);



}

/* [] END OF FILE */
