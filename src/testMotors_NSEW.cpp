#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "mraa.h"
#include "SparkFun_pca9685_Edison.h"

// Definitions
#define motorN 0
#define motorS 1
#define motorE 2
#define motorW 3
using namespace std;

int main() {
	unsigned char newPrescalar ;
	int done = 0 ;
	float pwmFreq = 550 ;
	float basePWM = 0 ;
	char stopBase ;

	mraa::I2c* pwm_i2c;
	pwm_i2c = new mraa::I2c(1);

	pca9685 pwm(pwm_i2c, 0x40);
	pwm.setFreq(pwmFreq) ; // Sets PWM Freq to 600 Hz

	sleep(2) ;

	/* Increases the Base PWM Duty Cycle to all four motors */

	int checkForOne ;
	cin.clear(); // Flush input buffer stream
	while (cin.get() != '\n')
	{
	    continue;
	}
	while( basePWM < 100 ){
		cout << "Type 1 to quit increasing Base PWM " << endl ;
		cin >> checkForOne ;
		if (checkForOne == 1)
			break ;
		cout << "Base PWM =" << basePWM << endl ;
		basePWM = basePWM + 0.25;
		pwm.setChlDuty(motorN, basePWM);
		pwm.setChlDuty(motorS, basePWM);
		pwm.setChlDuty(motorE, basePWM);
		pwm.setChlDuty(motorW, basePWM);
		sleep(1) ;
	}



	/* Play with Motors */

	float P_offset = 0;
	float R_offset = 0;
	float Y_offset = 0;
	cin.clear(); // Flush input buffer stream
	while (cin.get() != '\n')
	{
	    continue;
	}

	checkForOne = 0 ;
	char command ;

	while(checkForOne != 1){
		cout << "Type 8 or 2 to change pitch angle, 4 or 6 to change roll angle" << endl ;
		cout << "Type 9 at any point to increase Base PWM" << endl ;
		cout << "Type 3 at any point to decrease Base PWM" << endl ;
		cout << "Type 1 at any point quit and kill motors" << endl ;
	    cin >> command ;
	    switch ( command )
		 {
			 case 8:
				P_offset = P_offset - 0.25 ;
				pwm.setChlDuty(motorN, basePWM + P_offset);
				pwm.setChlDuty(motorS, basePWM - P_offset);
				break ;
			 case 2:
				P_offset = P_offset + 0.25 ;
				pwm.setChlDuty(motorN, basePWM + P_offset);
				pwm.setChlDuty(motorS, basePWM - P_offset);
				break ;
			 case 4:
				R_offset = R_offset - 0.25 ;
				pwm.setChlDuty(motorE, basePWM + R_offset);
				pwm.setChlDuty(motorW, basePWM - R_offset);
				break ;
			 case 6:
				R_offset = R_offset + 0.25 ;
				pwm.setChlDuty(motorE, basePWM + R_offset);
				pwm.setChlDuty(motorW, basePWM - R_offset);
				break ;
			 case 9:
				basePWM = basePWM + .5 ;
				pwm.setChlDuty(motorN, basePWM + P_offset);
				pwm.setChlDuty(motorS, basePWM - P_offset);
				pwm.setChlDuty(motorE, basePWM + R_offset);
				pwm.setChlDuty(motorW, basePWM - R_offset);
				break ;
			 case 3:
				basePWM = basePWM - .5 ;
				pwm.setChlDuty(motorN, basePWM + P_offset);
				pwm.setChlDuty(motorS, basePWM - P_offset);
				pwm.setChlDuty(motorE, basePWM + R_offset);
				pwm.setChlDuty(motorW, basePWM - R_offset);
				break ;
			 case 1:
				checkForOne = 1;
				break ;
			 default :
				break ;
		 }


	    usleep(10000) ;
	} // End While Loop

	pwm.setChlDuty(motorN, 0);
	pwm.setChlDuty(motorS, 0);
	pwm.setChlDuty(motorE, 0);
	pwm.setChlDuty(motorW, 0);



  return 0;
}

