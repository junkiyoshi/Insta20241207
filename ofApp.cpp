#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->line.clear();

	ofSeedRandom(39);
	auto base_radius = 280;
	auto len = 35;
	ofColor color;

	for (int m = 0; m < 360; m += 120) {

		for (int k = 0; k < 7; k++) {

			auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			color.setHsb(ofMap(k, 0, 7, 0, 255), 255, 255);

			for (int i = 0; i < len; i++) {

				auto deg = m + ofGetFrameNum() * 2.88 + i * 2.88;
				auto vertex = glm::vec3(base_radius * cos(deg * DEG_TO_RAD), base_radius * sin(deg * DEG_TO_RAD), 0);

				auto location = glm::vec3(
					ofMap(ofNoise(noise_param.x, i * 0.03 + ofGetFrameNum() * 0.03), 0, 1, -50, 50),
					ofMap(ofNoise(noise_param.y, i * 0.03 + ofGetFrameNum() * 0.03), 0, 1, -50, 50),
					ofMap(ofNoise(noise_param.z, i * 0.03 + ofGetFrameNum() * 0.03), 0, 1, -50, 50));

				this->line.addVertex(vertex + location);
				this->line.addColor(ofColor(color, ofMap(i, 0, len, 0, 255)));
				if (i > 1) {

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->line.drawWireframe();

	this->cam.end();

	/*
	int start = 500;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}