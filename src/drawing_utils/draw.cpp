#include "draw.h"

void
Draw::Drawellipse(const Eigen::VectorXd& X, float a, float b, std::string color) {
	assert(X.size() == 3);
	const int NPOINTS = 100;
	Eigen::VectorXd vec = Eigen::VectorXd::LinSpaced(NPOINTS, 0, 2 * M_PI);
	int N = vec.size();

	Eigen::MatrixXd p = Eigen::MatrixXd::Ones(2,N);
	p.row(0) = a * vec.array().cos();
	p.row(1) = b * vec.array().sin();

	// //handle the rotation and translation
	float x0 = X(0), y0 = X(1), angle = X(2);
	Eigen::MatrixXd R = Eigen::MatrixXd(2,2);
	R << cos(angle), -sin(angle), sin(angle), cos(angle);

	Eigen::MatrixXd T = Eigen::MatrixXd::Ones(2,N);
	T.row(0) = x0*T.row(0);
	T.row(1) = y0*T.row(1);
	p = R*p + T;

	//for plotting purpuse only
	std::vector<float> Px, Py;
	for (int i = 0; i < N; i++) {
		Px.push_back(p(0,i));
		Py.push_back(p(1,i));
	}
	plt::plot(Px, Py, color);
} /* End of Drawellipse */

void
Draw::Drawprobellipse(Eigen::VectorXd x, const Eigen::MatrixXd& C, float alpha, std::string color) {
	float sxx = C(0, 0), syy = C(1, 1), sxy = C(0, 1);
	float a = sqrt(0.5*(sxx+syy+sqrt(pow(sxx-syy, 2)+4*pow(sxy,2))));   // always greater
	float b = sqrt(0.5*(sxx+syy-sqrt(pow(sxx-syy, 2)+4*pow(sxy,2))));   // always smaller

	//% Scaling in order to reflect specified probability
	a = a*sqrt(chi2invtable(alpha,2));
	b = b*sqrt(chi2invtable(alpha,2));	

	if (sxx < syy) {
	 float temp = a;
	 a = b;
	 b = temp;	
	}

	float angle = 0;
	//% Calculate inclination (numerically stable)
	if (sxx != syy)
	  angle = 0.5*atan(2*sxy/(sxx-syy));	
	else if (sxy == 0)
	  angle = 0;     //angle doesn't matter 
	else if (sxy > 0)
	  angle =  M_PI/4;
	else if (sxy < 0)
	  angle = -M_PI/4;
	x(2) = angle;
	Drawellipse(x,a,b,color);
} /* End of Drawprobellipse */



Draw::Draw() {
	//landmarking drawing setting
	landmarks_settings["color"] = "orange";
	landmarks_settings["linestyle"] = " ";
	landmarks_settings["marker"] = "+";
	landmarks_settings["markersize"] = "10";
	landmarks_settings["linewidth"] = "5";

	// particles drawing setting
	particle_settings["color"] = "green";
	particle_settings["linestyle"] = " ";
	particle_settings["marker"] = "o";
	particle_settings["markersize"] = "5";
	particle_settings["linewidth"] = "3.5";

	//observation drawing settings;
	obs_settings["color"] = "blue";
	obs_settings["linestyle"] = " ";
	obs_settings["marker"] = "o";
	obs_settings["markersize"] = "10";
	obs_settings["linewidth"] = "5";

	// pose drawing settings
	pose_settings["color"] = "red";
	pose_settings["linestyle"] = " ";
	pose_settings["marker"] = "+";
	pose_settings["markersize"] = "10";
	pose_settings["linewidth"] = "5";

	// trajectory setting
	traj_settings["markersize"] = "3";
	traj_settings["linewidth"] = "2";

	// line setting
	line_settings["color"] = "black";
	line_settings["linestyle"] = ":";
 } /* End of constructor */
 
void
Draw::Plot_state( const ParticleSetPtr& particles
				, const Eigen::VectorXd& mu
				, const Eigen::MatrixXd& sigma
				, const Particle& most_likely
				, const mapPointSet& landmarks
				, const Records& sensorRecords
				, const std::string& text) {
	Clear() ;
	draw_basic_frame(-2, 12, -2, 12) ;
	DrawLandMarks(landmarks) ;	
	plot_particles( particles ) ;
	Drawprobellipse(mu, sigma, 0.6, "r") ; // plot the most likely pose
	plot_point(mu(0), mu(1)) ;

	// draw robot
	Drawellipse(mu, 0.15, 0.15, "r") ;

	// Draw the landmarks as registered by the most likely particle
	DrawLandMarks(most_likely.landmarks) ;

	draw_trajectory(most_likely.history) ;

	// Draw the observation lines
	Draw_observation_beams(most_likely) ;

	// Show legend
	plt::text(8.5, 10.5, text) ;

	Pause() ;
} /* End of Plot_state */

void
Draw::draw_basic_frame( const int& x_lower, const int& x_upper
					  , const int& y_lower, const int& y_upper) {
	plt::xlim(x_lower, x_upper) ;
	plt::ylim(y_lower, y_upper) ;
} /* End of draw_basic_frame */

void
Draw::draw_trajectory(const std::vector<Eigen::VectorXd>& path, const std::string& color) {
	traj_settings["color"] = color ;

	std::vector<float> X, Y ;
	std::vector<Eigen::VectorXd>::const_iterator it ;
	for (it = path.begin() ; it != path.end() ; it++) {
		Eigen::VectorXd est_pose = *it ;
		float x = est_pose(0) ;
		float y = est_pose(1) ;

		X.push_back(x) ;
		Y.push_back(y) ;
	}

	plt::plot(X, Y, traj_settings) ;
} /* End of draw_trajectory */

void
Draw::DrawLandMarks(const LandmarkSet& landmarks) {
	std::vector<float> X, Y ;
	for (auto& landm : landmarks) {
		if (landm.observed) {
			X.push_back( landm.mu(0) ) ;
			Y.push_back( landm.mu(1) ) ;

			Drawprobellipse(landm.mu, landm.sigma, 0.4, "b") ;
		}
	}

	plt::plot(X, Y, obs_settings) ;
} /* End of DrawLandMarks */

void
Draw::DrawLandMarks(const mapPointSet& landmarks) {
	std::vector<float> X, Y;
	for (auto& landmark : landmarks) {
		X.push_back(landmark.x);
		Y.push_back(landmark.y);
	}
	plt::plot(X, Y, landmarks_settings) ;
} /* End of DrawLandMarks */

void
Draw::plot_particles(const ParticleSet& particles) {
	std::vector<float> X, Y ;
	ParticleSet::const_iterator particle ;
	for (particle = particles.begin() ; particle != particles.end() ; particle++) {
		Eigen::Vector3d pose = particle->state ;
		X.push_back( pose(0) ) ;
		Y.push_back( pose(1) ) ;
	}

	plt::plot(X, Y, particle_settings) ;
} /* End of plot_particles */

void
Draw::plot_particles(const ParticleSetPtr& particlesPtr) {
	std::vector<float> X, Y ;
	ParticleSet::const_iterator particle ;
	for (particle = particlesPtr->begin() ; particle != particlesPtr->end() ; particle++) {
		Eigen::Vector3d pose = particle->state ;
		X.push_back( pose(0) ) ;
		Y.push_back( pose(1) ) ;
	}

	plt::plot(X, Y, particle_settings) ;
} /* End of plot_particles */

void
Draw::plot_point(const float& x, const float& y) {
	plt::plot( {x}, {y}, pose_settings ) ;
} /* End of plot_point */

void
Draw::Draw_observation_beams(const Particle& particle) {
	float rob_pos_x = particle.state(0) ;
	float rob_pos_y = particle.state(1) ;
	for (auto& landm : particle.landmarks) {
		if ( landm.observed ) {
			// draw a line from (rob_pos_x, rob_pos_y) to (landm.x, landm.y)
			std::vector<float> X = {rob_pos_x, (float)landm.mu(0)} ;
			std::vector<float> Y = {rob_pos_y, (float)landm.mu(1)} ;
			plt::plot(X, Y, line_settings) ;
		}
	}
} /* End of Draw_observation_beams */

void
Draw::Pause(float seconds) {
	plt::pause(seconds);
} /* End of Pause */

void
Draw::Clear() {
	plt::clf();
} /* End of Clear */

void
Draw::Show() {
	plt::show();
} /* End of Show */

void
Draw::Save(std::string path) {
	plt::save(path);
} /* End of Save */