#include <wiringPi.h>
#include <stdio.h>
#include <thread>
#include "flow_meter.h"
#include <iostream>

float liter_drank; //amount of water drank
bool isDrinking; //check if the flow meter is receiving water

void handle_transfer_data(){
		while(true){
			if(!isDrinking){
				std::cout<<"not drinking\n";
				}
			}
	}

void handle_flow_meter(flow_meter flow_m){
	while(true){
		flow_m.operate_flow_meter(isDrinking);
		flow_m.update_liter();
		liter_drank = flow_m.get_amount_drank();
		delay(1);
		}
	}

int main(int argc, char** argv){
	wiringPiSetup();
	flow_meter flow_m(3);
	
	std::thread flow_meter_thread(handle_flow_meter, flow_m);
	std::thread data_transfer_thread(handle_transfer_data);
	flow_meter_thread.join();
	data_transfer_thread.join();
	 
	return 0;
	}
