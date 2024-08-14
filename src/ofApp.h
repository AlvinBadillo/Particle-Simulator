#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void processKey(int key);
		
		particleMode currentMode;
		string currentModeStr; 
		particlePause currentPause;
		particleColor currentColor;

		ofTimer timer;

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;
		vector <int> keyLog;

		float rectangleX0;
		float rectangleY0;
		float rectangleX1;
		float rectangleY1;
		int timeoutDuration;
		unsigned int startTime;
		unsigned int currentKeyIndex;

		bool currentlyRecording;
		bool currentlyPlaying;
		bool rectangleActive;
		
};
