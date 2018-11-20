#include <string>

class water_object{
	private:
		float water_amount;
		std::string date;
		int is_sync;
		
	public:
		water_object(float water_amount_, std::string& date_, int is_sync_);
		float get_water_amount();
		std::string& get_date();
		int get_is_sync();
	};
