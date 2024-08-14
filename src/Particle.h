#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

enum particlePause{
	PARTICLE_RUN = 0,
	PARTICLE_PAUSE
};

enum particleColor{
	DEFAULT = 0,
	BLUE,
	YELLOW,               
	RED,
	CUSTOM
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();
		void setPause(particlePause newPause);
		void setColor(particleColor newColor);
		void setMagnify(double mag);
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		float magnify;
		
		
		particleMode mode;
		particlePause pause;
		particleColor color;
		
		vector <glm::vec3> * attractPoints; 
};
