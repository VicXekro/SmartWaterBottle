#ifndef FLOW_METER_H
#define FLOW_METER_H

#include <wiringPi.h>
#include <stdint.h>
#include <string>


class flow_meter{
	private:
		unsigned int flow_sensor_pin; //IO pin receiving the data from flow meter device
		volatile uint16_t pulses; // count how many pulses!
		volatile uint8_t last_flow_pin_state; //tranck the state of the puls pin
		volatile uint32_t last_flow_rate_timer; //track time of how long it is been pulsing 
		volatile float flow_rate; //used to calculate a flow rate
		float liters; //amount of water drank
		
		std::string current_date; 
		std::string previous_date;
		
		std::string get_current_time();
	public:
		flow_meter(const unsigned int flow_sensor_pin_);
		float get_amount_drank();
		void operate_flow_meter(bool& isDrinking);
		void update_liter();
	};
#endif
