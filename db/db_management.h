#include <sqlite3.h>

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
		
		static void send_data(); //send data in db with is_sync == 0
};
