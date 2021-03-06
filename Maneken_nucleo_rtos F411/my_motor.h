#ifndef MY_MOTOR_H
#define MY_MOTOR_H

#include "mbed.h"
#include "my_potentiometer.h"
#include "my_pid.h"
#include "my_debugBuffer.h"


class My_motor
{
 
    protected:
 
    public:
            
        DigitalOut direct1;
        DigitalOut direct2;
        PwmOut speed;
        My_pid Pid;
				My_potentiometer pot;
				//My_DebugBuffer debugBuffer;
		
        char flag_start;
        char flagRotate;
        char flag_dir;
        float omega;
        int pulse_enc;
        char direction;
		
				char flagInvertPosition;
				int8_t position;
				static const int8_t positionMin = 0;
				static const int8_t positionMax = 100;
				static const int8_t positionStop = -1;
        
        My_motor(PinName dir1, PinName dir2, PinName pwm, PinName adc_pin, float _min, float _max, float _delta) 
					: direct1(dir1), direct2(dir2), speed(pwm), pot(adc_pin, _min, _max, _delta)//, debugBuffer(100)
        {
						wait(0.1);
//					
//						positionMin = 0;
//						positionMax = 100;
//						positionStop = -1;
						position = positionStop;
					
            flag_start=0;
            flagRotate=0;
            flag_dir=0;
            SetSpeed(0);
            direction=0;
						Stop();
					flagInvertPosition=0;
        }
        
				void SetPosition(int8_t pos)
				{
					if(flagInvertPosition == 0)
					{
						position = pos;
					}
					else
					{
						position = positionMax - pos;
					}
				}
				
				int8_t GetPosition()
				{
					if(flagInvertPosition == 0)
					{
						return position;
					}
					else
					{
						return positionMax - position;
					}
				}
				
        void SetSpeed(float sp)
        {
					if( pot.IsMaxValue() && direction == 1)
					{
						speed=1;
						return;
					}
					
					if(pot.IsMinValue() && direction == 2)
					{
						speed=1;
						return;
					}
					
					if(sp>1)
					{
						speed=0;
					}
					else if(sp<0)
					{
						speed=1;
					}
					else
					{
						speed= 1-sp;
					}

					if( GetSpeed() != 0 && direction != 0)
					{
						flagRotate=1;
					}
					else
					{
						flagRotate=0;
					}
        }
        
        float GetSpeed()
        {
            return 1-speed;    
        }
				
				void PidStep()
				{
					if(Pid.enabled == 1)
					{
						float newSpeed;
						newSpeed = Pid.CalculatePid(pot.currentPosition)/100 + GetSpeed();
						
						SetSpeed(newSpeed);
						//debugBuffer.WriteValue(newSpeed);
					}
				}
        
        void SetDirection(int dir)
        {
            if(dir==1)
            {
                direction=1;
                direct1=1;
                direct2=0;
            }
            else if(dir==2)
            {
                direction=2;
                direct1=0;
                direct2=1;
            }
            else
            {
                direction=0;
                direct1=0;
                direct2=0;
            }
						
						if( GetSpeed() != 0 && direction != 0)
						{
							flagRotate=1;
						}
						else
						{
							flagRotate=0;
						}
        }
        
        void AnotherDirection()
        {
            if(direction==1)
            {
                SetDirection(2);
            }
            else if(direction==2)
            {
                SetDirection(1);
            }
        }
        void Stop()
        {
            SetDirection(0);
            SetSpeed(0);
            flagRotate=0;
						Pid.ResetOnZero();
					
        }

};

#endif


