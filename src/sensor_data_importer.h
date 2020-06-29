#ifndef _ODOMETRY_DATA_IMPORTER_H_
#define _ODOMETRY_DATA_IMPORTER_H_

#include <string>
#include <vector>

#include "odometry.h"
#include "observation.h"
#include "sensor_record.h"
#include "common_typedefs.h"
#include "document_processor.h"

class Sensor_data_importer {
  public:
  	void import_from(const std::string& fileName) ;
  	Records get() const ;
  	int size() const ;
  private:
  	Document_processor dproc_ ;
  	Records all_perception_records_ ;
} ; /* End of class */

#endif /* _ODOMETRY_DATA_IMPORTER_H_ */