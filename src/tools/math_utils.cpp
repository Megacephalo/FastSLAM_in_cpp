#include "math_utils.h"

float
Math_utils::normalize_angle(float phi) {
	while(phi <= -M_PI) {
		phi += 2 * M_PI ;
	}
	while(phi > M_PI) {
		phi -= 2 * M_PI ;
	}

	return phi ;
} /* End of normalize_angle */

float
Math_utils::normrnd( const float& mu, const float& sigma
  				   , const Random_machine_type& rd_type) {
	float rand_num = 0. ;
	switch(rd_type) {
		case MERSENNE_TWISTER: {
			std::mt19937 gen( rd_() ) ;
			std::normal_distribution<float> dist(mu, sigma) ;
			rand_num = dist( gen ) ;
			break ;
		}
		case KNUTH_B: {
			std::knuth_b gen( rd_() ) ;
			std::normal_distribution<float> dist(mu, sigma) ;
			rand_num = dist( gen ) ;
			break ;
		}
		case DEFAULT: {
			std::default_random_engine gen( rd_() ) ;
			std::normal_distribution<float> dist(mu, sigma) ;
			rand_num = dist( gen ) ;
			break ;
		}
	}

	return rand_num ;
} /* End of normrnd */

float
Math_utils::unifrnd( const float& lower_bound, const float& upper_bound
  				   , const Random_machine_type& rd_type) {
	float rand_num = 0. ;
	switch(rd_type) {
		case MERSENNE_TWISTER: {
			std::mt19937 gen( rd_() ) ;
			std::uniform_real_distribution<float> dist(lower_bound, upper_bound) ;
			rand_num = dist( gen ) ;
			break ;
		}
		case KNUTH_B: {
			std::knuth_b gen( rd_() ) ;
			std::uniform_real_distribution<float> dist(lower_bound, upper_bound) ;
			rand_num = dist( gen ) ;
			break ;
		}
		case DEFAULT: {
			std::default_random_engine gen( rd_() ) ;
			std::uniform_real_distribution<float> dist(lower_bound, upper_bound) ;
			rand_num = dist( gen ) ;
			break ;
		}
	}

	return rand_num ;
} /* End of unifrnd */