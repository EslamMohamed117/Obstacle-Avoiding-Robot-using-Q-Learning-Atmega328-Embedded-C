#include <avr/delay.h>
#include <avr/io.h>
#include <math.h>
#include <stdbool.h>
#include "Ultarasonic/Ultrasonic_Interface.h"
#include "Ultarasonic/DIO/DIO_Interface.h"
#include "RC_Controling_interface.h"
#include "ServoMotor.h"
#include "avr//eeprom.h"
#define Q_ROW 4
#define Q_COL 4


bool Obstacle;
int distance;
//LEARNING RATE
float ALPHA = 0.1;   
//DISCOUNT FACTOR 
float GAMMA = 0.5;   
//EXPLORATION PARAMETER 
float EPSILON = 0.90; 
//REWARD FOR PERFORMING AN ACTION
int REWARD;         
//Number of Iterations for learning  
int EPISODES  = 100;
//Set the state of the robot with 0
int STATE = 0;
/*Action Performed by the robot
  0: Stop
  1: backward
  2: right
  3: left  */                        
int ACTION = 0;
//Random number between 1 and 0 @ used for Epsilon                    
float PROB;            
                
int NEXT_STATE;                 
#define STATES 4           
#define NUMBER_OF_ACTIONS 4 


/*
Q Table 
each row represent a state
each column represent an action
*/
float Q[STATES][NUMBER_OF_ACTIONS] = {{0.0,0.0,0.0,0.0},  
                                      {0.0,0.0,0.0,0.0},  
                                      {0.0,0.0,0.0,0.0},  
                                      {0.0,0.0,0.0,0.0}};
/*
Rewards
each row represent a state
each column represent an action
*/

int REWARDS[STATES][NUMBER_OF_ACTIONS] = {{-10,-2,10,10}, 
                                          {-10,-2,10,-10}, 
                                          {-10,-2,-10,10}, 
                                          {-10,10,-10,-10}
											  };  
                                          
//Q LEARNING UPDATE PARAMETERS
float Q_OLD;
float Q_NEW;
float Q_MAX;


//Saving the q table into the eeprom
void save_q_table()
{
	uint16_t loc=0;
	
	for(int i=0; i<Q_ROW; i++)
	{
		for(int k=0; k<Q_COL; k++)
		{
			eeprom_write_float((float*)loc,Q[i][k]);
			loc=loc+4;
		}
	}
}
//Retriving the q table from the eeprom
void retrive_q_table()
{
	uint16_t loc=0;
	
	for(int i=0; i<Q_ROW; i++)
	{
		for(int k=0; k<Q_COL; k++)
		{
			Q[i][k]=eeprom_read_float((float *) loc);
			loc=loc+4;
		}
	}
}


 // Returns a number between 0 and 1
float RANDOM()
{
  return (rand() % 100)/100.0;
}
// Decaying a number by 2%
float DECAY(float PARAMETER)
{
  return PARAMETER*0.98;
}

bool Obstacle_Avoider()
{
	distance=ultarasonic_distance();
	if(distance<40)
	{
		
		Obstacle = true;
	}
	else
	{
		Obstacle = false;
	}
	_delay_ms(10);
	return Obstacle;
}

/*
Get the current state of the robot
3: There are right and left obstacles
2: There is a right obstacle
1: There is a left obstacle
0: There are no obstacles
*/
u16 GET_STATE()
{	
  bool Obstacle_left = false;
  bool Obstacle_right = false;
  set_servo_angel(90);
  _delay_ms(5000);
  Obstacle_right = Obstacle_Avoider();
  set_servo_angel(-90);
  _delay_ms(5000);
  Obstacle_left = Obstacle_Avoider();
  set_servo_angel(0);
  _delay_ms(5000);  
  if(Obstacle_right && Obstacle_left)
  {
	  return 3; 
  }
  else if(Obstacle_right)
  {
    return 2;
  }
  else if(Obstacle_left)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//Getting the maximum q value for the next state
float MAX(float Q_Table[][4],int NEXT_S)
{
	float LIST[4];
	float MAX_VALUE;
	for(int b = 0; b<=3; b++)
	{
		LIST[b] = Q[NEXT_S][b];
	}
	MAX_VALUE= LIST[0];
	for(int j = 1; j<=3 ; j++)
	{
		if(MAX_VALUE < LIST[j])
		{
			MAX_VALUE = LIST[j];
		}
	}
	return MAX_VALUE;
}

 /*THIS FUNCTION UPDATES THE Q TABLE AND Q VALUES. THIS UPDATE KEEPS ON HAPPENING UNTILL THE 
  MAIN LOOP ENDS. AT THE END OF EPISODES THE Q TABLE IS FILLED WITH VARIOUS VALUES. THE GREATER
  THE VALUES THE GREATER IMPORTANCE THE ACTION HAS AT THAT PARTICULAR STATE. "Q_OLD" IS OLD VALUE
  THAT THE Q MATRIX HAS.THIS IS THE VALUE WHICH GETS UPDATED EVENTUALLY. Q_NEW IS THE NEW Q_VALUE 
  WHICH IS CALCULATED BY THE Q LEARNING FORMULA. THE Q LEARNING FORMULA USED HERE IS BASED ON 
  BELLMAN EQUATION USES TEMPORAL DIFFERENCE LEARNING APPROACH.(MONTE CARLO APPROACH WILL NOT
  WORK IN THIS CASE OF OBSTACLE AVOIDING ROBOT.*/
void Update(float Q_TABLE[][NUMBER_OF_ACTIONS] , int S, int NEXT_S, int A, int R, float LEARNING_RATE, float DISCOUNT_FACTOR)
{
 Q_OLD = Q_TABLE[S][A];
 Q_MAX = MAX(Q_TABLE, NEXT_S);
 Q_NEW = (1-LEARNING_RATE)*Q_OLD + LEARNING_RATE*(R + DISCOUNT_FACTOR*Q_MAX);
 Q_TABLE[S][A] = Q_NEW;                
}

//Getting the index of the maximum q value for the current state
int ARGMAX(float Q_Table[10][4],int S)
{
   float ARRAY[4];
   float MAX_VALUE;
   int MAX_INDEX;
   for(int b = 0; b<=3; b++)
	{
	ARRAY[b] = Q[S][b];
	}
   MAX_VALUE= ARRAY[0];
   for(int j = 1; j<=3 ; j++)
	{
	  if(MAX_VALUE < ARRAY[j])
		{
		MAX_VALUE = ARRAY[j];
		MAX_INDEX = j;
		}
	}
  return MAX_INDEX;
}



void Train() 
{
	for(int I =0; I<EPISODES; I++)
	{
		while(true)
		{			   
			forward();     
			Obstacle = Obstacle_Avoider();
            if(Obstacle)
			{  
				//Looping over states to train the robot for each one of them
				NEXT_STATE = (STATE+1) % STATES; 
				break;
			}
		}
		/*
		 Depending on the random number generated and the Epsilon value 
		 we chose either to explore the actions randomly 
		 or exploiting the actions from the q table
		*/
		PROB = RANDOM();
		if (PROB<=EPSILON)     
		{
			ACTION = rand() % NUMBER_OF_ACTIONS;
		}
		else                  
		{
			ACTION = ARGMAX(Q,STATE);
		}
		  
		switch (ACTION)
		{			  
			case 0:
			break;
			
			case 1:
			backward();
			break;
			
			case 2:
            right();
		    break;	   
			
			case 3:
			left();
			break;
		}
		_delay_ms(10000);
		stop();
		REWARD = REWARDS[STATE][ACTION];
		_delay_ms(500); 
		Update(Q,STATE,NEXT_STATE,ACTION,REWARD,ALPHA ,GAMMA);
		STATE = NEXT_STATE;
		EPSILON = DECAY(EPSILON);      
	}
	save_q_table();
}


void Test()
{
	retrive_q_table();
	while(true)
	{
		forward();
		Obstacle = Obstacle_Avoider();
		if(Obstacle)
		{
			stop();
			_delay_ms(3000);
			//Get the current state of the robot
			STATE = GET_STATE();  
			//Get the maximum q
			ACTION = ARGMAX(Q,STATE);
			switch (ACTION)
			{
				case 0:
				break;
				 
				case 1:
				backward();
				break;
				
				case 2:
				backward();
				_delay_ms(3000);
				stop();
				right();
				break;
				
				case 3:
				backward();
				_delay_ms(3000);
				stop();
				left();
				break;
			}
			_delay_ms(10000);
			stop();
		}
	}
}



//bool EEPROM_is_empty()
//{
	//char A;
	//bool empty=true;
	//for(int i=0; i<4; i++)
	//{
		//A=eeprom_read_byte((uint8_t*)i);
		//if(A != 0xFF)
		//{
			//empty =false;
			//break;
		//}
	//}
	//return empty;
//}
