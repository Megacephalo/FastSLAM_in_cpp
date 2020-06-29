#ifndef _MAP_IMPORTER_H_
#define _MAP_IMPORTER_H_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "common_typedefs.h"
#include "document_processor.h"
#include "map_point.h"

class Map_Importer {
  public:
  	Map_Importer() ;
  	void import_from (const std::string& fileName) ;
  	mapPointSet landmarks() const ;
  	int landmark_size() const ;
  private:
  	mapPointSet landmarks_ ;
  	Document_processor dproc_ ;
} ; /* End of class */

#endif /*  _MAP_IMPORTER_H_ */