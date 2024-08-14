#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	currentPause = PARTICLE_RUN;

	currentColor = DEFAULT;

	currentlyRecording = false;

	currentlyPlaying = false;

    timeoutDuration = 3000;

	rectangleActive = false;

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
		p[i].setPause(currentPause);
		p[i].setColor(currentColor);
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
	if(currentlyPlaying){		
		if ((ofGetElapsedTimeMillis() - startTime) >= timeoutDuration || currentKeyIndex == 0){
			if(currentKeyIndex < keyLog.size()){
				processKey(keyLog[currentKeyIndex]);
				currentKeyIndex++;
				startTime = ofGetElapsedTimeMillis();
			}
			else{
				currentlyPlaying = false;
				
			}
		}	
	}	
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));


	if(rectangleActive == true){
		for(unsigned int i = 0; i < p.size(); i++){
			if(p[i].pos.x >= rectangleX0 && p[i].pos.x <= rectangleX1 && p[i].pos.y >= rectangleY0 && p[i].pos.y <= rectangleY1 
			|| p[i].pos.x <= rectangleX0 && p[i].pos.x >= rectangleX1 && p[i].pos.y <= rectangleY0 && p[i].pos.y >= rectangleY1
			|| p[i].pos.x >= rectangleX0 && p[i].pos.x <= rectangleX1 && p[i].pos.y <= rectangleY0 && p[i].pos.y >= rectangleY1
			|| p[i].pos.x <= rectangleX0 && p[i].pos.x >= rectangleX1 && p[i].pos.y >= rectangleY0 && p[i].pos.y <= rectangleY1){
				p[i].setMagnify(sqrt(5));
			}
			else{
				p[i].setMagnify(1);
			}
		}
	}
	else{
		for(unsigned int i = 0; i < p.size(); i++)
			p[i].setMagnify(1);
		
	}

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
		
	}

	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}
	if(rectangleActive){
		ofFill();
		ofSetColor(240,112,13,60);
		ofDrawRectangle(rectangleX0, rectangleY0, (rectangleX1 - rectangleX0), (rectangleY1 - rectangleY0));
	}

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	if(currentlyRecording){
		ofDrawBitmapString("Recording", 10, 75);
	}
	
	if(currentlyPlaying){

		std::string y("Replaying ");
		char asciiChar = static_cast<char>(keyLog[currentKeyIndex-1]);
		y.push_back(asciiChar);
		
		ofDrawBitmapString(y, 10, 75);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(currentlyPlaying){	
		if(key == 'c'){
			currentlyPlaying = false;			
		}		
	}
	else{
		processKey(key);

	}
}

void ofApp::processKey(int key){
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 	

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}	
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";

		if(currentlyRecording == true){
			keyLog.push_back(key);
		} 				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force"; 

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}								
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 	
		
		if(currentlyRecording == true){
			keyLog.push_back(key);
		}							
		resetParticles();
	}	
		
	if( key == ' ' ){
		resetParticles();

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}		
	}
	if(key == 's'){
		if(currentPause == PARTICLE_RUN){
			currentPause = PARTICLE_PAUSE;
		}
		else {
			currentPause = PARTICLE_RUN;
		}	
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].setPause(currentPause);
		}
		if(currentlyRecording == true){
			keyLog.push_back(key);
		}		
	}	
	if( key == 't'){
		if(currentColor == DEFAULT){
			currentColor = BLUE;
		}
		else if(currentColor == BLUE){
			currentColor = YELLOW;
		}
		else if(currentColor == YELLOW){
			currentColor = RED;
		}
		else if(currentColor == RED){
			currentColor = CUSTOM;
		}
		else{
			currentColor = DEFAULT;
		}
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].setColor(currentColor);
		}

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}		
	}
	if(key == 'd'){
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].vel.x = p[i].vel.x * 2.0; 
			p[i].vel.y = p[i].vel.y * 2.0;
		}

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}		
	}
	if(key == 'a'){
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].vel.x /= 2.0; 
			p[i].vel.y /= 2.0;
		}

		if(currentlyRecording == true){
			keyLog.push_back(key);
		}		
	}

	if(key == 'r'){
		if(currentlyRecording == true){
			currentlyRecording = false;
		}
		else{
			keyLog.clear();
			currentlyRecording = true;
		}
	}

	if(key == 'p'){
		if(currentlyPlaying == false){
			currentKeyIndex = 0;
			currentlyPlaying = true;
			startTime = ofGetElapsedTimeMillis();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_LEFT){
		rectangleActive = true;
		rectangleX1 = x;
		rectangleY1 = y;	
	}	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_LEFT){
		rectangleX0 = x;
		rectangleY0 = y;

		rectangleX1 = x;
		rectangleY1 = y;
	}
	if(button == OF_MOUSE_BUTTON_RIGHT && x >= rectangleX0 && x <= rectangleX1 && y >= rectangleY0 && y <= rectangleY1 
	|| button == OF_MOUSE_BUTTON_RIGHT && x <= rectangleX0 && x >= rectangleX1 && y <= rectangleY0 && y >= rectangleY1
	|| button == OF_MOUSE_BUTTON_RIGHT && x >= rectangleX0 && x <= rectangleX1 && y <= rectangleY0 && y >= rectangleY1
	|| button == OF_MOUSE_BUTTON_RIGHT && x <= rectangleX0 && x >= rectangleX1 && y >= rectangleY0 && y <= rectangleY1){
		rectangleActive = false;	
	}
}				

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(button == OF_MOUSE_BUTTON_LEFT){
		rectangleX1 = x;
		rectangleY1 = y;
		
	}

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
