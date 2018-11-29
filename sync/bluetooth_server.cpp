#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <iostream>

#include "bluetooth_server.h"
#include "../db/db_management.h"


void bluetooth_server::server(){
	
	struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client;
    socklen_t opt = sizeof(rem_addr);
    
    char local_address [18] = "B8:27:EB:F2:7E:56";
    
    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    str2ba(local_address,&loc_addr.rc_bdaddr);
    //loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // leave the connection open.
    while (true){
		client = accept(s, (struct sockaddr *)&rem_addr, &opt);

		ba2str( &rem_addr.rc_bdaddr, buf );
		fprintf(stderr, "accepted connection from %s\n", buf);
		memset(buf, 0, sizeof(buf));
		
		std::cout<<"enter gethering list"<<std::endl;

		std::list<water_object> list_water = db_manager::get_all_water();//get all the water amount stored in db
		
		std::cout<<"pass gethering list"<<std::endl;
		
		for(auto it = list_water.begin(); it != list_water.end(); ++it) {
			int send_bytes = 0;
			water_object w = *it;
			std::cout<<"Date water: "<<w.get_date()<<std::endl;
			if(w.get_is_sync() ==0){ //make sure that only not sync water amount are sent. 
				std::string info_to_send = std::to_string(w.get_water_amount())+ ";"+std::string(w.get_date()); //send water amount + date
				send_bytes = send(client, info_to_send.c_str(), info_to_send.length(), 0);
				if(send_bytes>0 && (w.get_date().compare(db_manager::get_current_time()) != 0)){
					db_manager::set_is_sync(w); //if was sent and date!=current_date, set is_sync == 1 
					}
			}
		}
		//db_manager::delete_sync_water();//remove water that were sync from db

		// close connection
		close(client);
	}
    close(s);
	}

/*int main(int argc, char** argv)
{
	bluetooth_server::server();
    return 0;
}*/
