#include "mbed.h"
#include "motors_threads.h"

extern My_motor motor0;	//A,B,PWM
extern My_motor motor1;	//A,B,PWM
extern My_motor motor2;	//A,B,PWM
extern My_motor motor3;	//A,B,PWM
extern My_motor motor4;	//A,B,PWM
extern My_motor motor5;	//A,B,PWM
extern My_motor motor6;	//A,B,PWM
extern My_motor motor7;	//A,B,PWM


void UartRX(void);

int count=0;

extern Serial pc;

Thread t0, t1, t2, t3, t4, t5, t6, t7;

DigitalOut led1(LED1);



// threads
//uint8_t flag_thread1=0, flag_thread2=0;
extern int8_t flag_thread;

// for debug
DigitalOut test1(PC_10);
//My_DebugBuffer debugBuffer(300, 300);
uint8_t flag_buf=0;

Ticker tim;	

void time()
{
    static int i1=0;
    const int deltaT = 5; // ms        
    i1++;
    
    
    if(i1==deltaT)
    {
			test1=1;
			
			motor0.pot.Refresh();
      motor1.pot.Refresh();
			motor2.pot.Refresh();
			motor3.pot.Refresh();
			motor4.pot.Refresh();
			motor5.pot.Refresh();
			motor6.pot.Refresh();
			motor7.pot.Refresh();
			
			i1=0;
			
//			if(motor1.flagRotate==1)
//			{
//				//debugBuffer.WriteValue(pot1.omega);
//				//debugBuffer.WriteValue2(pot1.currentPosition);
//			}
			
			motor0.PidStep();
			motor1.PidStep();
			motor2.PidStep();
			motor3.PidStep();
			motor4.PidStep();			
			motor5.PidStep();
			motor6.PidStep();
			motor7.PidStep();
			
			test1=0;
    }

}




int main()
{
    pc.baud(256000);
    pc.attach(&UartRX);
    pc.printf("\n\n*** RTOS maneken start ***\n");
		
		tim.attach_us(&time, 5000);
	
		wait(1);

		t0.start(motor0_body);
		t1.start(motor1_body);
		t2.start(motor2_body);
		t3.start(motor3_body);
		t4.start(motor4_body);
		t5.start(motor5_body);
		t6.start(motor6_body);
	
		GoToNull();
		wait(2);
	
	
		//Trajectory1();
		
//		Trajectory2();
//		
//		Trajectory3();
//		
		//Trajectory4();
	
    while (true) 
    {
			
			
			led1 = !led1;
			wait(0.5);
    }
}
