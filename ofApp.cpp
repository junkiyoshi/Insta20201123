#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(150, 3);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.008, avg.y * 0.008, avg.z * 0.008, ofGetFrameNum() * 0.003);

		float noise_radius = 150;
		if (noise_value > 0.48 && noise_value < 0.52) {

			noise_radius = ofMap(noise_value, 0.48, 0.52, 150, 250);
		}
		else if(noise_value >= 0.52) {

			noise_radius = 250;
		}

		int index = this->mesh.getNumVertices();

		this->mesh.addVertex(glm::normalize(avg) * (noise_radius + 25));
		this->mesh.addVertex(glm::normalize(triangle.getVertex(0)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(1)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(2)) * noise_radius);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.43);
	ofRotateY(ofGetFrameNum() * 0.65);

	ofSetColor(39);
	this->mesh.drawFaces();

	ofSetColor(239);
	this->mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}