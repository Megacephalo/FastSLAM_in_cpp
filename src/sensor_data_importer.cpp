#include "sensor_data_importer.h"

void
Sensor_data_importer::import_from(const std::string& fileName) {
	if ( !dproc_.fileExist(fileName) ) {
		std::cerr << "The file does not exist.\n" ;
		return ;
	}

	if ( !dproc_.fileCanOpen(fileName) ) {
		std::cerr << "The file cannot be openned or is corrupted.\n" ;
		return ;
	}

	std::ifstream file = dproc_.getFile(fileName) ;
	std::string line ;
	long long timestamp = 1 ; // start counting from 1 instead of 0

	long long prev_timestamp = 0 ;

	Sensor_record recordTimestamped ;

	while( std::getline(file, line) ) {
		// split the line into words
		std::vector<std::string> recv_line  = dproc_.split_string(line) ;

		if ( recv_line.front() == "ODOMETRY" ) {
			// if reaching the end of a timestamp's entry and the beginning of another
			if (prev_timestamp == timestamp) {
				all_perception_records_.push_back( recordTimestamped ) ;
				recordTimestamped.clear() ;

				timestamp ++ ;	
			}

			std::vector<std::string>::iterator it = recv_line.begin() + 1 ;
			float r1 = std::stof( *it ) ;
			float t = std::stof( *(it + 1) ) ;
			float r2 = std::stof( *(it + 2) ) ;
			recordTimestamped.odom = Odometry(timestamp, r1, t, r2) ;
		}
		else if ( recv_line.front() == "SENSOR" ) {
			std::vector<std::string>::iterator it = recv_line.begin() + 1 ;

			long long id = std::stoll( *it ) ;
			float range = std::stof(*(it + 1)) ;
			float bearing = std::stof( *(it + 2) ) ;

			recordTimestamped.observations.push_back( Observation_model(timestamp, id, range, bearing) ) ;
		}
		else {
			std::cerr << "Unrecognizable token\n" ;
			continue ;
		}

		// if reaching the end of a timestamp's entry and the beginning of another
		if ( prev_timestamp != timestamp ) {
			prev_timestamp = timestamp ;
		}
	} /* end of while */

	// Update the last entry if it has not being pushed into all_perception_records yet
	if (prev_timestamp == timestamp && !recordTimestamped.observations.empty() ) {
		all_perception_records_.push_back( recordTimestamped ) ;
	}

	dproc_.close(file) ;
} /* End of import_from */

Records
Sensor_data_importer::get() const {
	return all_perception_records_ ;
} /* End of get */

int
Sensor_data_importer::size() const {
	return (int) all_perception_records_.size() ;
} /* End of size */