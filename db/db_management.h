#include <sqlite3.h>
#include "water_object.h"
#include <list>

class db_manager{
	private:
		static sqlite3* get_connector(); //return connector to handle db

		static void close_connection(sqlite3* connection); //close connection with db
		
		static void save_water_db(float water_drank); //store water_drank in db as new value
		
		static bool is_current_amnt_date_saved(); // check if there is water in db having date == current date
		
		static float get_water_current_date_db(); //return water in db having date == current date
		
	public:

		static void update_water_db(float water_drank, float& previous_water_drank); //update water value in db for current date

		static std::string get_current_time(); //return current date
		
		static std::list<water_object> get_all_water(); //return all the water amount saved in database
		
		static void set_is_sync(water_object& water_o ); //set is sync to 1 in db
		
		static void delete_sync_water();//remove all data that were sync from db
};
