#include "document_processor.h"

std::ifstream
Document_processor::getFile(const std::string& fileName) {
	std::ifstream file( fileName.c_str() ) ;
	return file ;
} /* End of getFile */

bool
Document_processor::fileExist(const std::string& fileName) {
	std::ifstream file(fileName.c_str()) ;
	return file.good() ; 
} /* End of fileExist */

bool
Document_processor::fileCanOpen(const std::string& fileName) {
	std::ifstream file ;
	file.open(fileName.c_str()) ;
	return file.is_open() ;
} /* End of fileCanOpen */


std::vector<std::string> 
Document_processor::split_string(const std::string& str, char delimiter) {
	std::vector<std::string> tokens ;
	std::string token ;
	std::istringstream tokenStream(str) ;
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token) ;
	}

	return tokens ;
} /* End of split_string */

bool
Document_processor::close(std::ifstream& file) {
	if (file.is_open()) {
		file.close() ;
		return true ;
	}
	return false ;
} /* End of close */