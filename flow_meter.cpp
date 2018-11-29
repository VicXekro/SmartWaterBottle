#include "flow_meter.h" 
#include <iostream>
#include <bluetooth/bluetooth.h>

flow_meter::flow_meter(const unsigned int  flow_sensor_pin_){
	/*
	 * get the pin and set its mode.
	 * initialize the rest of variables;
	 */
	 flow_sensor_pin = flow_sensor_pin_;
	 pulses = 0;
	 last_flow_rate_timer = 0;
	 
	 current_date = get_current_time();
	 previous_date = get_current_time();
	 
	 pinMode(flow_sensor_pin, INPUT);
	 digitalWrite(flow_sensor_pin, HIGH);
	 last_flow_pin_state = digitalRead(flow_sensor_pin);
	 std::cout<<"FLow meter initialization completed"<<"\n";
	}

float flow_meter::get_amount_drank(){
	//return the actual amount of water drank
		current_date = get_current_time();
		if(current_date.compare(previous_date) == 0){
			return liters;
		}
		else{
			//new day started, set the amount of water to zero for the new day.
			liters = 0;
			previous_date = current_date;
			return liters;
		}
			
	}

void flow_meter::operate_flow_meter(bool& isDrinking){
	//std::cout<<"Operate flow meter\n";
		uint8_t x = digitalRead(flow_sensor_pin);
		//std::cout <<"X value is: "<<unsigned(x)<<"\n";
		if(x == last_flow_pin_state){
			last_flow_rate_timer++; 
			isDrinking = false;
			return; //nothing changed 
			}
		if(x==HIGH){
			isDrinking = true;
			pulses++;//low to high transition
			}
		last_flow_pin_state = x;
		flow_rate = 1000.0;
		flow_rate /= last_flow_rate_timer; //in hertz
		last_flow_rate_timer = 0;
		//std::cout<<"Finished operation\n";
	}
	
void flow_meter::update_liter(){
	//this method update the amount of water
	//plastic sensor; use this formula
		liters = pulses;
		liters /=7.5;
		liters /=60.0;
		//std::cout<<liters<<" liters\n";
	}

std::string flow_meter::get_current_time(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::string date = std::to_string(1900 + ltm->tm_year)+"-"+std::to_string(1 + ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday);
	return date;
	}
