#include "water_object.h"

water_object::water_object(float water_amount_, std::string& date_, int is_sync_){
		water_amount = water_amount_;
		date = date_;
		is_sync = is_sync_;
	}

float water_object::get_water_amount(){
		return water_amount;
	}

int water_object::get_is_sync(){
		return is_sync;
	}
	
std::string& water_object::get_date(){
	return date;
	}
