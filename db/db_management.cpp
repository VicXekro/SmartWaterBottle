#include <iostream>
#include <sqlite3.h>
#include <string>
#include <ctime>

#include "db_management.h"

//return slqite3 object to operate on database. 
sqlite3* db_manager::get_connector(){
		sqlite3* DB;
		int exit = 0;
		exit = sqlite3_open("db/smart_water.db", &DB);
		
		if(exit != SQLITE_OK){
			std::cout<<"error on connector"<<sqlite3_errmsg(DB)<<std::endl;
			}
		
		return DB;
	}
	
//close the sql connection	
void db_manager::close_connection(sqlite3* connection){
		sqlite3_close(connection);
	}

//save amount water in db
void db_manager::save_water_db(float water_drank){
	sqlite3* DB = get_connector();
	char* messageError;
	std::string sql_query = std::string("INSERT INTO water (water_qt, date, is_sync)")+
				"VALUES("+ std::to_string(water_drank)+", date('now','localtime'), 0)";
	sqlite3_exec(DB, sql_query.c_str(),NULL,0,&messageError);
	close_connection(DB);
	}


//check if the water of the day was already saved 	
bool db_manager::is_current_amnt_date_saved(){
	std::string current_date = get_current_time();
	
	sqlite3_stmt *stmt;
	sqlite3* DB = get_connector();
	std::string sql_query = std::string("SELECT * FROM water Where date = '")+current_date+"'";
	
	int ret_code = 0;
	ret_code = sqlite3_prepare_v2(DB, sql_query.c_str(), sql_query.length(),&stmt,NULL);
	
	if(ret_code == SQLITE_OK){
		
		while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
			const unsigned char* date = sqlite3_column_text(stmt,2);
			
			if(date){
				sqlite3_finalize(stmt);
				close_connection(DB);
				return true;
				}
			}
		}	
		
	sqlite3_finalize(stmt);
	close_connection(DB);

	return false;
	}
	
//fetch the water in db having the same date as current date.
float db_manager::get_water_current_date_db(){
	std::string current_date = get_current_time();
	float water_amount = 0;
	
	sqlite3_stmt *stmt;
	sqlite3* DB = get_connector();
	std::string sql_query = std::string("SELECT * FROM Water Where date = '")+current_date+"'";
	
	int ret_code = 0;
	ret_code = sqlite3_prepare_v2(DB, sql_query.c_str(), sql_query.length(),&stmt,NULL);
	if(ret_code == SQLITE_OK){
		while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
			water_amount = (float) sqlite3_column_double(stmt,1);
			}
		}
		sqlite3_finalize(stmt);
		close_connection(DB);
		return water_amount;
	}

/*update the amount of water in the database
 * save water of the day if not exist else
 * update the amount of water in db	
*/
void db_manager::update_water_db(float water_drank, float& previous_water_drank){
	float db_water = 0;
	if(is_current_amnt_date_saved()){
		std::cout<<"in update db method"<<std::endl;
		char* errorM;
			
		if(water_drank != previous_water_drank){
			previous_water_drank = water_drank - previous_water_drank;
			db_water = get_water_current_date_db();
			
			sqlite3* DB = get_connector();
			
			db_water = (previous_water_drank > db_water)? (previous_water_drank):(previous_water_drank+db_water);
			
			std::cout<<"water to be saved: "<<db_water<<std::endl;
			
			std::string sql_query = std::string("UPDATE water set water_qt = ")+std::to_string(db_water)+
						std::string(" WHERE date = '")+get_current_time()+"';";
			
			sqlite3_exec(DB, sql_query.c_str(),NULL,0,&errorM);
			//std::cout<<errorM<<std::endl;
			
			previous_water_drank = water_drank;
			close_connection(DB);
			}else{std::cout<<"amount didn't changed"<<std::endl;}
		}
	else{
		save_water_db(water_drank);
		}
	}

//get current time and output a string representing the date
std::string db_manager::get_current_time(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::string date = std::to_string(1900 + ltm->tm_year)+"-"+std::to_string(1 + ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday);
	return date;
	}
	
/* send data on the raspberrypi to the mobile application using bluetooth. 
 */
void db_manager::send_data(){
	//std::cout<<"sending data"<<std::endl;
	}
	
/*int main(int argc, char** argv) 
{ 
    //save_water_db(9);
    //std::string date = db_manager::get_current_time();
    //std::cout<<db_manager::get_water_current_date_db()<<std::endl;
    float g = 1;
    db_manager::update_water_db(g);
 
    return (0); 
}*/ 
