#include <iostream>
#include <sqlite3.h>
#include <string>
#include <ctime>

//return slqite3 object to operate on database. 
sqlite3* get_connector(){
		sqlite3* DB;
		int exit = 0;
		exit = sqlite3_open("smart_water.db", &DB);
		
		return DB;
	}
	
//close the sql connection	
void close_connection(sqlite3* connection){
		sqlite3_close(connection);
	}

//save amount water in db
void save_water_db(float water_drank){
	sqlite3* DB = get_connector();
	char* messageError;
	std::string sql_query = std::string("INSERT INTO Water (water_qt, date, is_sync)")+
				"VALUES("+ std::to_string(water_drank)+", date('now','localtime'), 0)";
	sqlite3_exec(DB, sql_query.c_str(),NULL,0,&messageError);
	close_connection(DB);
	}

//get current time and output a string representing the date
std::string get_current_time(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::string date = std::to_string(1900 + ltm->tm_year)+"-"+std::to_string(1 + ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday);
	return date;
	}
	
int main(int argc, char** argv) 
{ 
    //save_water_db(9);
    std::string date = get_current_time();
    std::cout<<date<<std::endl;
    return (0); 
} 
