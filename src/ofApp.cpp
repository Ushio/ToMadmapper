#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	_toSpoutFbo.allocate(512, 512);
	_spoutsender.CreateSender("kokeshi", _toSpoutFbo.getWidth(), _toSpoutFbo.getHeight());

	glGenTextures(1, &_spoutTexture);
	glBindTexture(GL_TEXTURE_2D, _spoutTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _toSpoutFbo.getWidth(), _toSpoutFbo.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	float elapsed = ofGetElapsedTimef();

	ofEnableAlphaBlending();
	_toSpoutFbo.begin();
	ofClear(128);
	ofDrawCircle(_toSpoutFbo.getWidth() * 0.5 + sin(elapsed) * 200.0, _toSpoutFbo.getHeight() * 0.5, 100);

	{
		// Grab the screen into the local spout texture
		glBindTexture(GL_TEXTURE_2D, _spoutTexture);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, _toSpoutFbo.getWidth(), _toSpoutFbo.getHeight());
		glBindTexture(GL_TEXTURE_2D, 0);

		// Send the texture out for all receivers to use
		_spoutsender.SendTexture(_spoutTexture, GL_TEXTURE_2D, _toSpoutFbo.getWidth(), _toSpoutFbo.getHeight());
	}
	_toSpoutFbo.end();

	ofClear(0);

	ofDisableBlendMode();
	_toSpoutFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
