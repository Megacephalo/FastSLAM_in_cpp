#include "low_variance_sampling.h"

void
Low_variance_sampling::sample(ParticleSet& particles, const std::vector<double>& all_weights) {
	std::vector<float> conv_vect ;
	for (std::vector<double>::const_iterator it = all_weights.begin() ; it != all_weights.end() ; it++) {
		conv_vect.push_back( (float)*it ) ;
	}

	sample(particles, conv_vect) ;
} /* End of sample */

void
Low_variance_sampling::sample(ParticleSet& particles, const std::vector<float>& all_weights) {
	int numParticles = (int)particles.size() ;

	float r = (float) math_.unifrnd(0, 1 / numParticles ) ;

	int n = 1 ;
	float c = all_weights.front() ;

	for (int i = 0 ; i < numParticles ; i++) {
		float U = (float) r + (i - 1) / numParticles ;
		while ( U > c ) {
			n++ ;
			c += all_weights.at(n) ;
		}

		particles.at(i) = particles.at(n) ;
		particles.at(i).weight = all_weights.at(n) ;
	}
} /* End of sample */