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
#include"mym.h"
//test
void mymPrint(void)
{
    printf("\nHello World!\n");

    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 } 

/*I do all the assignments for practicing reason
group functions are added to main.c*/

//week 3 assignment 1
void motorRun(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(118,3000);    
    motor_turn(43,0,1200);    
    motor_forward(85,3000); 
    motor_turn(43,0,1200);         
    motor_forward(115,2500);
    motor_turn(43,0,1200); 
   for(int i=0; i <75; i++)
    {
        motor_turn(15, 10, 50);
    }
    for (int i=0; i <145; i++)
    {
        motor_turn(10, 10, 50);
    }
    for (int i=0; i <40; i++)
    {
        motor_turn(20, 10, 50);
    }
    for (int i=0; i <110; i++)
    {
        motor_turn(10, 10, 50);
    }
    for (int i=0; i <40; i++)
    {
        motor_turn(18, 10, 50);
    }
    motor_forward(95,950);
    motor_stop(0, 0);
}

//week 3 assignment 2
void assignment2(void)
{ 
    Ultra_Start();
    motor_start();  
    
    motor_forward(50,100);
    while(true)
    {   
        int distance = Ultra_GetDistance();
        if(distance <= 10)
        {
            motor_backward(50,100);
            motor_turn(0,120,350);
            motor_forward(50,100);
        }
    }
    motor_stop(0, 0);
}


//week 4 assignment 1
void ladder(void)
{
    int count = 0;
    struct sensors_ dig;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    
    IR_Start();
    IR_flush(); 
    motor_start();
    motor_forward(0,0);
    
    while(SW1_Read() == 1) //wait for button
    { 
        motor_forward(0,0);
        vTaskDelay(50);
        
    }
    vTaskDelay(500);
    
    while(true)
    {
        reflectance_digital(&dig);
        if ((dig.R1 || dig.L1) && !(dig.R3 && dig.L3)) //go if center sensors are on line
        { 
            motor_forward(50, 10);
        }
        if (dig.R3 && dig.L3)   //if all sensors are on the line
        { 
            count++;
            
            if (count == 1)          //first line
            { 
                motor_forward(0,0);
                IR_wait();          //wait for IR signal
            }
            if(count == 5)           //skip to line 5
            {   
                motor_forward(0,0);
                motor_stop();
                break;  
            }
            while(dig.R3 && dig.L3) 
            { 
                reflectance_digital(&dig);
                motor_forward(50, 10);
            }
        }
    }
    
}

//week 4 assignment 2
void curve(void)
{
    struct sensors_ dig;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    
    IR_Start();
    motor_start();
    motor_forward(0,0);
    
    while(SW1_Read() == 1) //wait for button
    { 
        motor_forward(0,0);
        vTaskDelay(50);
    }
    
    vTaskDelay(500);
    
    reflectance_digital(&dig);
    
    while (!(dig.R3 && dig.L3))         //if center sensors are on line
    {   
        motor_forward(60, 20);
        reflectance_digital(&dig);
    }
        motor_forward(0,0);
        IR_wait();
        reflectance_digital(&dig);
    
    while (dig.L3 && dig.R3) 
    {
        motor_forward(30,10);
        reflectance_digital(&dig);
    }
    while(true)
    {
        reflectance_digital(&dig);
        motor_forward(100,0);
        if(dig.L1 == 0 && dig.R1==1) 
        {
            SetMotors(0, 1, 20, 10, 10);
        }
        if(dig.L1 == 1 && dig.R1==0) 
        {
            SetMotors(1, 0, 10, 20, 10);
        }
        reflectance_digital(&dig);
        if ((dig.R2 && dig.L3)||(dig.L3 && dig.R2)) 
        {
            motor_forward(0,0); 
            break;
        }            
    }   
}

//week4 assignment 3  
void grid(void)
{
    int count = 0;
    struct sensors_ dig;
        
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
        
    IR_Start();
    IR_flush(); 
        
    motor_start();
    motor_forward(0,0);
       
    while(SW1_Read() == 1)      //loop until button is pressed
    { 
        motor_forward(0,0);
        vTaskDelay(50);   
    }
    vTaskDelay(500);
    
    while(true)
    {
        reflectance_digital(&dig);
        if (dig.R3 && dig.L3)   //if all sensors are on black line
        { 
            count++;
            if (count == 1)      //first line
            { 
                motor_forward(0,0); 
                IR_wait();      //wait for IR signal
            }
            if(count == 2)       //second line
            { 
                motor_turn(15, 120, 500);
            }
            if(count == 3 || count == 4)     //2 intersections
            {
                motor_forward(60,20); 
                motor_turn(120, 15, 500);
            }
            if(count == 5)           //last line
            {
                motor_forward(0,0);
                break;
            }
            while(dig.R3 && dig.L3) {       //continue while on line
                reflectance_digital(&dig);
                motor_forward(60,20);
            }
        }
       
        reflectance_digital(&dig);   //align robot
        while ((dig.L1 && dig.R1) && !(dig.L3 && dig.R3)) 
        {     
            motor_forward(60,20);
            reflectance_digital(&dig);
        }
        while (!(dig.L3 && dig.R3) &&  (dig.L2 && dig.L1 )) 
        {     
            motor_turn(20, 135, 40);
            reflectance_digital(&dig);   
        }
        while ((dig.R2 && dig.R3) && !(dig.L2 && dig.L3)) {
            motor_turn(125, 20, 40);
            reflectance_digital(&dig);
        }
    } 
}


//week5 assignment 3
void mqtt3(void)
{
    int count = 0;
    struct sensors_ dig;
    int timeStart = 0;
    TickType_t start, end;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
   
    IR_Start();
    IR_flush();
    motor_start();
    motor_forward(0,0);
     
    while(true)
    {  
    reflectance_digital(&dig);
        if ((dig.R1 || dig.L1) && !(dig.R3 && dig.L3))   //go in if center sensors are on line
        {
            motor_forward(50, 10);
        }
        if (dig.R3 && dig.L3) 
        { 
            count++;
            
            if (count == 1)
            {  
                motor_forward(0,0);
                IR_wait(); 
                start = xTaskGetTickCount();
                print_mqtt("Zumo04/start", "%d", start);
                timeStart = start;         //set it to global variable
            }   
            if(count == 2) 
            { 
                motor_forward(0,0);    
                break;      
            }

            while(dig.R3 && dig.L3) { 
                reflectance_digital(&dig);
                motor_forward(50, 10);
            }
            end = xTaskGetTickCount();
            print_mqtt("Zumo04/end", "%d", end);
            int ticktime = end - timeStart;
            print_mqtt("Zumo04/lap", "The elapsed time is %d s", ticktime);  
        }          
    }
}

//Sumo wrestling project
void sumo(void)
{
    struct sensors_ dig;
    TickType_t start, stop, turn;
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    IR_Start();
    IR_flush();
    Ultra_Start();
    motor_start();
    motor_forward(0,0);

    vTaskDelay(100);
    
    reflectance_digital(&dig);
    while(dig.R1 == 1 || dig.L1 == 1)   //go in if center sensors are on line
    {
        motor_forward(60,20);
        reflectance_digital(&dig);
    }
    motor_forward(0, 0);
    print_mqtt("Zumo04/ready", "zumo");
    IR_wait(); 
    motor_forward(100, 30);
    start = xTaskGetTickCount();
    print_mqtt("Zumo004/start", "%d", start);
    
    while(true)
    {   
        int distance = Ultra_GetDistance();
        if(distance < 20)   //motor turn when sees obstacle
        {
            motor_turn(200, 10, 100); 
        }
            
        reflectance_digital(&dig);
        if(dig.L3 || dig.L2 || dig.R3 || dig.R2)    //robot stays inside the ring
        {
            motor_backward(100, 50);        
            motor_turn(200, 10, 100);
        }
        turn = xTaskGetTickCount();
        print_mqtt("Zumo04/obstacle", "%d", turn);
        
        while(!(dig.L3 || dig.R2 || dig.L1 || dig.R3 || dig.L2 || dig.R1))  
        {
            reflectance_read(&dig); 
            motor_forward(100, 10);     //go forward if see no line
        }
        if(SW1_Read() == 0) {   //if button pressed robot stop
            stop = xTaskGetTickCount();
            print_mqtt("Zumo04/stop", "%d", stop);
            int runTime = stop - start;
            print_mqtt("Zumo04/time", "%d ms", runTime);
            motor_forward(0,0);
            motor_stop();
            break;
        }
    } 
}

//test
void maze(void)
{
    int y = 0;
    int x = 0;
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	

	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);

	motor_forward(100,0);
    reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,0);
        }
        
        if(dig.L1 == 0 && dig.R1 == 1) {  
                       
            SetMotors(0, 1, 100, 50, 20);
            
        }
        if(dig.L1 == 1 && dig.R1 == 0) {
                        
            SetMotors(1, 0, 50, 100, 20);
            
        }
	if(dig.L3 == 1 && dig.R3 == 1) {

	SetMotors(0, 0, 0, 0, 0);
	}
    while(y < 12) {
		int d = Ultra_GetDistance();
		if (d <= 11) {
			motor_turn(250, 0, 210);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
				if (x == 3) {
					motor_turn(0, 250, 210);
                    printf("x = %d\n", x);
					if (d <= 11) {
						motor_turn(0, 250, 210);
						motor_forward(100,0);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
							if (x == -3) {
								motor_turn(250, 0, 210);
							}
			
						}
					}	
				}
			}
		}
		else {
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
			}
		}
	}
}
		
//Kinh
void themaze(void) {

	int x = 0 , y = 0;
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	

	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);

	motor_forward(100,0);
	
	move_per_block();
	while (y < 12) {
		reflectance_digital(&dig);
		int d = Ultra_GetDistance();
		if (d <= 11) {
			obstacle(x);
		}
		else {
            
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
			}
		}
	}
}
//Kinh
void obstacle(int x)
		 {	
            struct sensors_ dig;
            int d = Ultra_GetDistance();
			random_turn_right();
			motor_forward(100,0);
			reflectance_digital(&dig);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
				printf("\nx = %d\n", x);
				if (x == 3) {
					random_turn_left();
					if (d <= 11) {
						random_turn_left();
						motor_forward(100,0);
						reflectance_digital(&dig);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
							if (x == -3) {
								random_turn_right();
							}
			
						}
					}	
				}
			}
		}
//Kinh        
void move_per_block(void) {
    struct sensors_ dig;
	reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,0);
        }
        
        if(dig.L1 == 0 && dig.R1 == 1) {  
                       
            SetMotors(0, 1, 100, 50, 20);
            
        }
        if(dig.L1 == 1 && dig.R1 == 0) {
                        
            SetMotors(1, 0, 50, 100, 20);
            
        }
	if(dig.L3 == 1 && dig.R3 == 1) {

	SetMotors(0, 0, 0, 0, 0);
	
	}
}
void random_turn_right(void) {
	SetMotors(0,1,100,100,262);
	SetMotors(0,0,0,0,0);
}
void random_turn_left(void) {
	SetMotors(1,0,100,100,262);
	SetMotors(0,0,0,0,0);
}

void testmaze(void)
{
	struct sensors_ dig;
    int y = 1;
    int x = 4;
    int d;
	
	IR_Start(); 
	IR_flush();
    Ultra_Start();
	reflectance_start();
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    motor_start(); //motor start
	motor_forward(0,0);
    vTaskDelay(500);
    
    reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,20);
        }
   
    for(;;)
        {
            reflectance_digital(&dig);
            d = Ultra_GetDistance();
            if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R3==1 && dig.R2==1 && dig.R1==1 && d>20 && x==4)
            {
                motor_forward(100,25);
                y++;
            }
        
             //when detected blocker turn left   
            else if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R3==1 && dig.R2==1 && dig.R1==1 && d<20)
            {
                motor_turn(0, 250, 210); // set LeftMotor 
                motor_forward(100,230); //
                x--;
                printf("\nx1 = %d\n", x);
				
				//when reach the next line try to turn right 
				if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R1==1 && dig.R2==1 && dig.R3==1)
				{
					motor_turn(250, 0, 210);// set RightMotor 
                    motor_forward(100,230);
					y++;
            
					//if there have block turn laft
					if(d<20)
					{
						motor_forward(100,25); // set forward  
						x--;
					}
            
					//if nothing go forward
					else
					{   
						motor_forward(100,25); // set forward  
						y++;
					}
				}
				
				}
			}
			
		}


void themaze1(void) 
{
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	
	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);
	
	motor_forward(100,0);
	
	int x = 0 , y = 0, count = 0;
	while (count <= 1) {
   	
		reflectance_digital(&dig);
        if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            count++;
            if (count == 1)
            {
                motor_forward(0, 0);
                IR_wait();
                motor_forward(100, 0);
                count = 2;
            }
         }
    }
	while (y < 12) {
		int d = Ultra_GetDistance();
		reflectance_digital(&dig);
        
		if (d <= 7) {
            printf("d is %d\n", d);
			random_turn_right();
			motor_forward(100,0);
            reflectance_digital(&dig);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
                printf("x = %d\n", x);
				if (x == 3) {
					random_turn_left();
					if (d <= 7) {
						random_turn_left();
						motor_forward(100,0);
                        reflectance_digital(&dig);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
                            printf("x = %d\n", x);
							if (x == -3) {
								random_turn_right();
							}
			
						}
					}	
				}
			}
		}
		else {
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
                printf("y = %d\n", y);
			}
		}
	}
}


void themazedraft(void) 
{

 	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);
    int x = 0 , y = 0;
    
    struct sensors_ dig;
    
    int count = 0, first = 0;
    int  turn = 0, coordinate = 0;
    int direction = 0;
    int timestart;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    IR_Start();
    
    while(true) {
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
       if(dig.L3 == 1 && dig.R3 == 1) {
                        
            motor_forward(0,0);
            
        }
       int d = Ultra_GetDistance();
       if (d<=8 && x == 3) {
            motor_forward(0,0);
            motor_backward(30,100);
            random_turn_left();
            turn++;
            coordinate = turn%2; 
            printf("random%d\n", turn);
            printf("rancdom%d\n", coordinate);
        }
        
        if (d<=8 && x == -3) {
            motor_forward(0,0);
            motor_backward(30,100);
            random_turn_right();
            turn++;
            coordinate = turn%2; 
            printf("random%d\n", turn);
            printf("rancdom%d\n", coordinate);
        }
            
       if (d<=6) {
			motor_forward(0,0);
            motor_backward(30,100);
            int random;
   	        random = rand()%2;
            direction = random;

            if (random == 0) {
		        random_turn_right();
		        print_mqtt("Zumo04/turn", "right");
		        turn++;
                coordinate = turn%2; 
                printf("random%d\n", turn);
                printf("rancdom%d\n", coordinate);
                }
	        else {
		        random_turn_left();
		        print_mqtt("Zumo04/turn", "left");
                turn++;
                coordinate = turn%2; 
                printf("random%d\n", turn);
                printf("rand%d\n", coordinate);
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
                printf("y=%d\n",y);
            }
            else if (coordinate == 1 && direction == 0) {
                x++;
                printf("x=%d\n",x);
            }
            else if (coordinate == 1 && direction == 1) {
                x--;
                printf("x=%d\n",x);
            }
            
             if (x == 3) 
            {
                motor_forward(150,150);
                random_turn_left();
                turn++;
                coordinate = turn%2;
                direction = 1;
                printf("turn =%d\n", turn);
                printf("coordinate=%d\n", coordinate);
              
            }
            if (x == -3) 
            {
                motor_forward(150,150);
                random_turn_right();
                turn++;
                coordinate = turn%2;
                direction = 0;
                printf("%d\n", turn);
                printf("%d\n", coordinate);
                
            }
            if (count == 2) {
                x = 0;
                y = 0;
                printf("y=%d\n",y);
            }
            while(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
            
        }
        if(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            if (y == 11 && x == -3) {
                motor_forward(150,150);
                random_turn_right();
            }
           
            if (coordinate == 0) {
                y++;
                printf("y=%d\n",y);
            }
            while(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
          
        }
        if (dig.R3 == 0 && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
        {
             
            
            if (coordinate == 0) {
                y++;
                printf("y=%d\n",y);
            }
            while(dig.R3 == 0  && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
            {
                reflectance_digital(&dig);
            }
          

        }
        if (y == 11 && x==3) {
                
                random_turn_left();
                motor_forward(150,250);
                printf("rechendturn\n");
                
            if (x == 2) 
            {
			    motor_forward(255,0);
                if(x==0){
                    random_turn_right();
                    motor_forward(255,0);
			    if (dig. R3 && dig.L3 == 0)
                {
                    motor_forward(0,0);
                }
		    }
		} 
        }
        if (first == 1) {
            motor_forward(0,0);
            print_mqtt("Zumo04/ready", "line %d", count);
            IR_wait();
            motor_forward(200,0);
            TickType_t startTime = xTaskGetTickCount();
            print_mqtt("Zumo04/start", "%d", startTime);
            timestart = startTime;
            first = 0;
        }
         
    }
    
}


=======
>>>>>>> 5e980cf... Added weekly assignments and Sumo project

//week5 assignment 3
void mqtt3(void)
{
    int count = 0;
    struct sensors_ dig;
    int timeStart = 0;
    TickType_t start, end;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
   
    IR_Start();
    IR_flush();
    motor_start();
    motor_forward(0,0);
     
    while(true)
    {  
    reflectance_digital(&dig);
        if ((dig.R1 || dig.L1) && !(dig.R3 && dig.L3))   //go in if center sensors are on line
        {
            motor_forward(50, 10);
        }
        if (dig.R3 && dig.L3) 
        { 
            count++;
            
            if (count == 1)
            {  
                motor_forward(0,0);
                IR_wait(); 
                start = xTaskGetTickCount();
                print_mqtt("Zumo04/start", "%d", start);
                timeStart = start;         //set it to global variable
            }   
            if(count == 2) 
            { 
                motor_forward(0,0);    
                break;      
            }

            while(dig.R3 && dig.L3) { 
                reflectance_digital(&dig);
                motor_forward(50, 10);
            }
            end = xTaskGetTickCount();
            print_mqtt("Zumo04/end", "%d", end);
            int ticktime = end - timeStart;
            print_mqtt("Zumo04/lap", "The elapsed time is %d s", ticktime);  
        }          
    }
    while(true) 
    { 
        vTaskDelay(100);    //loop so that zmain doesn't end
    }
}

//Sumo wrestling project
void sumo(void)
{
    struct sensors_ dig;
    TickType_t start, stop, turn;
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    IR_Start();
    IR_flush();
    Ultra_Start();
    motor_start();
    motor_forward(0,0);

    vTaskDelay(100);
    
    reflectance_digital(&dig);
    while(dig.R1 == 1 || dig.L1 == 1)   //go in if center sensors are on line
    {
        motor_forward(60,20);
        reflectance_digital(&dig);
    }
    motor_forward(0, 0);
    print_mqtt("Zumo04/ready", "zumo");
    IR_wait(); 
    motor_forward(100, 30);
    start = xTaskGetTickCount();
    print_mqtt("Zumo004/start", "%d", start);
    
    while(true)
    {   
        int distance = Ultra_GetDistance();
        if(distance < 20)   //motor turn when sees obstacle
        {
            motor_turn(200, 10, 100); 
        }
            
        reflectance_digital(&dig);
        if(dig.L3 || dig.L2 || dig.R3 || dig.R2)    //robot stays inside the ring
        {
            motor_backward(100, 50);        
            motor_turn(200, 10, 100);
        }
        turn = xTaskGetTickCount();
        print_mqtt("Zumo04/obstacle", "%d", turn);
        
        while(!(dig.L3 || dig.R2 || dig.L1 || dig.R3 || dig.L2 || dig.R1))  
        {
            reflectance_read(&dig); 
            motor_forward(100, 10);     //go forward if see no line
        }
        if(SW1_Read() == 0) {   //if button pressed robot stop
            stop = xTaskGetTickCount();
            print_mqtt("Zumo04/stop", "%d", stop);
            int runTime = stop - start;
            print_mqtt("Zumo04/time", "%d ms", runTime);
            motor_forward(0,0);
            motor_stop();
            break;
        }
    }
    while(true) {
        vTaskDelay(100);    //loop so that zmain doesn't end
    }   
}

//test
void maze(void)
{
    int y = 0;
    int x = 0;
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	

	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);

	motor_forward(100,0);
    reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,0);
        }
        
        if(dig.L1 == 0 && dig.R1 == 1) {  
                       
            SetMotors(0, 1, 100, 50, 20);
            
        }
        if(dig.L1 == 1 && dig.R1 == 0) {
                        
            SetMotors(1, 0, 50, 100, 20);
            
        }
	if(dig.L3 == 1 && dig.R3 == 1) {

	SetMotors(0, 0, 0, 0, 0);
	}
    while(y < 12) {
		int d = Ultra_GetDistance();
		if (d <= 11) {
			motor_turn(250, 0, 210);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
				if (x == 3) {
					motor_turn(0, 250, 210);
                    printf("x = %d\n", x);
					if (d <= 11) {
						motor_turn(0, 250, 210);
						motor_forward(100,0);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
							if (x == -3) {
								motor_turn(250, 0, 210);
							}
			
						}
					}	
				}
			}
		}
		else {
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
			}
		}
	}
}
		
//Kinh
void themaze(void) {

	int x = 0 , y = 0;
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	

	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);

	motor_forward(100,0);
	
	move_per_block();
	while (y < 12) {
		reflectance_digital(&dig);
		int d = Ultra_GetDistance();
		if (d <= 11) {
			obstacle(x);
		}
		else {
            
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
			}
		}
	}
}
//Kinh
void obstacle(int x)
		 {	
            struct sensors_ dig;
            int d = Ultra_GetDistance();
			random_turn_right();
			motor_forward(100,0);
			reflectance_digital(&dig);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
				printf("\nx = %d\n", x);
				if (x == 3) {
					random_turn_left();
					if (d <= 11) {
						random_turn_left();
						motor_forward(100,0);
						reflectance_digital(&dig);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
							if (x == -3) {
								random_turn_right();
							}
			
						}
					}	
				}
			}
		}
//Kinh        
void move_per_block(void) {
    struct sensors_ dig;
	reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,0);
        }
        
        if(dig.L1 == 0 && dig.R1 == 1) {  
                       
            SetMotors(0, 1, 100, 50, 20);
            
        }
        if(dig.L1 == 1 && dig.R1 == 0) {
                        
            SetMotors(1, 0, 50, 100, 20);
            
        }
	if(dig.L3 == 1 && dig.R3 == 1) {

	SetMotors(0, 0, 0, 0, 0);
	
	}
}
void random_turn_right(void) {
	SetMotors(0,1,100,100,262);
	SetMotors(0,0,0,0,0);
}
void random_turn_left(void) {
	SetMotors(1,0,100,100,262);
	SetMotors(0,0,0,0,0);
}

void testmaze(void)
{
	struct sensors_ dig;
    int y = 1;
    int x = 4;
    int d;
	
	IR_Start(); 
	IR_flush();
    Ultra_Start();
	reflectance_start();
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    motor_start(); //motor start
	motor_forward(0,0);
    vTaskDelay(500);
    
    reflectance_digital(&dig);
        if (dig.L1 == 1 && dig.R1 == 1) 
        {
            motor_forward(100,20);
        }
   
    for(;;)
        {
            reflectance_digital(&dig);
            d = Ultra_GetDistance();
            if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R3==1 && dig.R2==1 && dig.R1==1 && d>20 && x==4)
            {
                motor_forward(100,25);
                y++;
            }
        
             //when detected blocker turn left   
            else if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R3==1 && dig.R2==1 && dig.R1==1 && d<20)
            {
                motor_turn(0, 250, 210); // set LeftMotor 
                motor_forward(100,230); //
                x--;
                printf("\nx1 = %d\n", x);
				
				//when reach the next line try to turn right 
				if(dig.L3==1 && dig.L2==1 && dig.L1==1 && dig.R1==1 && dig.R2==1 && dig.R3==1)
				{
					motor_turn(250, 0, 210);// set RightMotor 
                    motor_forward(100,230);
					y++;
            
					//if there have block turn laft
					if(d<20)
					{
						motor_forward(100,25); // set forward  
						x--;
					}
            
					//if nothing go forward
					else
					{   
						motor_forward(100,25); // set forward  
						y++;
					}
				}
				
				}
			}
			
		}


void themaze1(void) 
{
	struct sensors_ dig;
	reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
	reflectance_start();
	
	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);
	
	motor_forward(100,0);
	
	int x = 0 , y = 0, count = 0;
	while (count <= 1) {
   	
		reflectance_digital(&dig);
        if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            count++;
            if (count == 1)
            {
                motor_forward(0, 0);
                IR_wait();
                motor_forward(100, 0);
                count = 2;
            }
         }
    }
	while (y < 12) {
		int d = Ultra_GetDistance();
		reflectance_digital(&dig);
        
		if (d <= 7) {
            printf("d is %d\n", d);
			random_turn_right();
			motor_forward(100,0);
            reflectance_digital(&dig);
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				x++;
                printf("x = %d\n", x);
				if (x == 3) {
					random_turn_left();
					if (d <= 7) {
						random_turn_left();
						motor_forward(100,0);
                        reflectance_digital(&dig);
						if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
							x--;
                            printf("x = %d\n", x);
							if (x == -3) {
								random_turn_right();
							}
			
						}
					}	
				}
			}
		}
		else {
			motor_forward(100,0); 
			if (dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1) {
				y++;
                printf("y = %d\n", y);
			}
		}
	}
}


void themazedraft(void) 
{

 	Ultra_Start();               // Ultra Sonic Start function
	motor_start();              // enable motor controller
	motor_forward(0,0);         // set speed to zero to stop motors
	vTaskDelay(3000);
    int x = 0 , y = 0;
    
    struct sensors_ dig;
    
    int count = 0, first = 0;
    int  turn = 0, coordinate = 0;
    int direction = 0;
    int timestart;
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000);
    IR_Start();
    
    while(true) {
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
       if(dig.L3 == 1 && dig.R3 == 1) {
                        
            motor_forward(0,0);
            
        }
       int d = Ultra_GetDistance();
       if (d<=8 && x == 3) {
            motor_forward(0,0);
            motor_backward(30,100);
            random_turn_left();
            turn++;
            coordinate = turn%2; 
            printf("random%d\n", turn);
            printf("rancdom%d\n", coordinate);
        }
        
        if (d<=8 && x == -3) {
            motor_forward(0,0);
            motor_backward(30,100);
            random_turn_right();
            turn++;
            coordinate = turn%2; 
            printf("random%d\n", turn);
            printf("rancdom%d\n", coordinate);
        }
            
       if (d<=6) {
			motor_forward(0,0);
            motor_backward(30,100);
            int random;
   	        random = rand()%2;
            direction = random;

            if (random == 0) {
		        random_turn_right();
		        print_mqtt("Zumo04/turn", "right");
		        turn++;
                coordinate = turn%2; 
                printf("random%d\n", turn);
                printf("rancdom%d\n", coordinate);
                }
	        else {
		        random_turn_left();
		        print_mqtt("Zumo04/turn", "left");
                turn++;
                coordinate = turn%2; 
                printf("random%d\n", turn);
                printf("rand%d\n", coordinate);
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
                printf("y=%d\n",y);
            }
            else if (coordinate == 1 && direction == 0) {
                x++;
                printf("x=%d\n",x);
            }
            else if (coordinate == 1 && direction == 1) {
                x--;
                printf("x=%d\n",x);
            }
            
             if (x == 3) 
            {
                motor_forward(150,150);
                random_turn_left();
                turn++;
                coordinate = turn%2;
                direction = 1;
                printf("turn =%d\n", turn);
                printf("coordinate=%d\n", coordinate);
              
            }
            if (x == -3) 
            {
                motor_forward(150,150);
                random_turn_right();
                turn++;
                coordinate = turn%2;
                direction = 0;
                printf("%d\n", turn);
                printf("%d\n", coordinate);
                
            }
            if (count == 2) {
                x = 0;
                y = 0;
                printf("y=%d\n",y);
            }
            while(dig.L3 == 1 && dig.L2 == 1 && dig.L1 == 1 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
            
        }
        if(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
        {
            if (y == 11 && x == -3) {
                motor_forward(150,150);
                random_turn_right();
            }
           
            if (coordinate == 0) {
                y++;
                printf("y=%d\n",y);
            }
            while(dig.L3 == 0 && dig.L2 == 0 && dig.R1 == 1 && dig.R2 == 1 && dig.R3 == 1)
            {
                reflectance_digital(&dig);
            }
          
        }
        if (dig.R3 == 0 && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
        {
             
            
            if (coordinate == 0) {
                y++;
                printf("y=%d\n",y);
            }
            while(dig.R3 == 0  && dig.R2 == 0 && dig.L1 == 1 && dig.L2 == 1 && dig.L3 == 1)
            {
                reflectance_digital(&dig);
            }
          

        }
        if (y == 11 && x==3) {
                
                random_turn_left();
                motor_forward(150,250);
                printf("rechendturn\n");
                
            if (x == 2) 
            {
			    motor_forward(255,0);
                if(x==0){
                    random_turn_right();
                    motor_forward(255,0);
			    if (dig. R3 && dig.L3 == 0)
                {
                    motor_forward(0,0);
                }
		    }
		} 
        }
        if (first == 1) {
            motor_forward(0,0);
            print_mqtt("Zumo04/ready", "line %d", count);
            IR_wait();
            motor_forward(200,0);
            TickType_t startTime = xTaskGetTickCount();
            print_mqtt("Zumo04/start", "%d", startTime);
            timestart = startTime;
            first = 0;
        }
         
    }
    
}

/* [] END OF FILE */
