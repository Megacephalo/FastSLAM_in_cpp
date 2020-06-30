#ifndef _DRAW_H_
#define _DRAW_H_

#include <map>
#include <Eigen/Dense>
#include <cassert>
#include <math.h>
#include <vector>

#include "particle.h"
#include "sensor_record.h"
#include "common_typedefs.h"

#include "chisquare.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

class Draw {
  private:
  	std::map<std::string, std::string> landmarks_settings ;
  	std::map<std::string, std::string> obs_settings ;
	std::map<std::string, std::string> particle_settings ;
	std::map<std::string, std::string> pose_settings ;
	std::map<std::string, std::string> traj_settings ;
	std::map<std::string, std::string> line_settings ;

	void Drawellipse(const Eigen::VectorXd& X, float a, float b, std::string color) ;

  public:
	Draw() ;
	void Plot_state( const ParticleSetPtr& particles
				   , const Eigen::VectorXd& mu
				   , const Eigen::MatrixXd& sigma
				   , const Particle& most_likely
				   , const mapPointSet& landmarks
				   , const Records& sensorRecords
				   , const std::string& text = std::string("")) ;
	void draw_basic_frame( const int& x_lower = -2, const int& x_upper = 12
						 , const int& y_lower = -2, const int& y_upper = 12) ;
	void Drawprobellipse( Eigen::VectorXd x
						, const Eigen::MatrixXd& C
						, float alpha
						, std::string color) ;
	void DrawLandMarks(const mapPointSet& landmarks) ;
	void DrawLandMarks(const LandmarkSet& landmarks) ;
	void draw_trajectory(const std::vector<Eigen::VectorXd>& path, const std::string& color = "magenta") ;
	void plot_particles(const ParticleSet& particles) ;
	void plot_particles(const ParticleSetPtr& particlesPtr) ;
	void plot_point(const float& x, const float& y) ;
	void Draw_observation_beams(const Particle& particle) ;
	void Pause(float seconds = 0.01) ;
	void Clear() ;
	void Show() ;
	void Save(std::string path) ;
};

#endif /* _DRAW_H_ */