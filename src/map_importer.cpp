#include "map_importer.h"

Map_Importer::Map_Importer()
{} /* End of default constructor */

void
Map_Importer::import_from (const std::string& fileName) {
	if ( !dproc_.fileExist(fileName) ) {
		std::cerr << fileName << " does not exist.\n" ;
		return ;
	}

	if ( !dproc_.fileCanOpen(fileName) ) {
		std::cerr << fileName << " cannot be openned or is corrupted.\n" ;
		return ;
	}

	std::ifstream file = dproc_.getFile(fileName) ;

	std::string line ;
	while( std::getline(file, line) ) {
		std::vector<std::string> recv_line = dproc_.split_string(line) ;

		MapPoint feature ;
		feature.id = std::stoll( recv_line.at(0) ) ;
		feature.x = std::stof( recv_line.at(1) ) ;
		feature.y = std::stof( recv_line.at(2) ) ;

		landmarks_.push_back( feature ) ;
	}
} /* End of import_from */

mapPointSet
Map_Importer::landmarks() const {
	return landmarks_ ;
} /* End of grid */

int
Map_Importer::landmark_size() const {
	return (int) landmarks_.size() ;
} /* End of */