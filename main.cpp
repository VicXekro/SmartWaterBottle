#include <wiringPi.h>
#include <stdio.h>
#include <thread>
#include <iostream>

#include "flow_meter.h"
#include "db/db_management.h"
#include "sync/bluetooth_server.h"


float liter_drank; //amount of water drank
bool isDrinking; //check if the flow meter is receiving water

//launch bluetooth server and transfer data using bluetooth.
static void handle_sync_data(){
		bluetooth_server::server();
	}

//handle the storage and update of water amount in sqlite db
static void handle_storage_water(){
	float previous_water_drank = 0;
		while(true){
			if(!isDrinking){
				//std::cout<<"not drinking\n";
				//std::cout<<liter_drank<<"\n";
				db_manager::update_water_db(liter_drank, previous_water_drank);
				//std::cout<<"after update water db method"<<std::endl;
				}
				//delay(150);
			}
	}

//handle the reading of water amount from flow meter
static void handle_flow_meter(flow_meter flow_m){
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
	std::thread water_storage_thread(handle_storage_water);
	
	std::thread sync_data_thread(handle_sync_data);
	
	flow_meter_thread.join();
	water_storage_thread.join();
	sync_data_thread.join();
	 
	return 0;
	}
