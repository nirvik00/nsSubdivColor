#include "ofApp.h"

#include "Area.h"
#include "Pt.h"
#include "Rect.h"
#include "ctrlVector.h"


void ofApp::setup() {
	srand(time(NULL));
	ofSetWindowTitle("Subdivision");
	vecIniRect.clear();
	vecOutRect.clear();
	vecParentVec.clear();
	vecBoundaryRect.clear();
	
	/* ONE RECT ONLY */
	//int U = 2; int V = 1;

	/* MULTIPLE RECTS */
	int U = 4; int V = 2;

	for (unsigned int i = 300; i < 300 * U; i += 325) {
		for (unsigned int j = 0; j < 300 * V; j += 325) {
			a = Pt(50 + i, 50 + j);
			b = Pt(a.x + 300, a.y);
			c = Pt(a.x + 300, b.y + 150);
			d = Pt(a.x, c.y);
			

			/* AREA */
			float totalArea = ar.getTotalAr();
			ar.initSubdiv();
			ar.constructGraph();
			ar.displayGraph();
			cout << "\n------------------------------\n" << std::endl;

			//ar.displayGraph();
			vector<Parent> parentVec; parentVec.clear();
			parentVec = ar.getParentVec();
			//vecParentVec.push_back(parentVec);

			/* CONTROL */
			ctrlVector cv; // control vector
			vector<int> cvV;// initialize the control vector
			cvV.clear(); // clear the control vector
			cvV = cv.newIntVector(NUM);

			/* RECTANGLE */
			Rect R0; // Initialize the rectangle
			Rect r = R0.genIniRect(a, 1, 2, totalArea); // setup the initial rectangle
			r.setParentVec(parentVec); // set the area tree to the rect
			r.setIntVector(cvV); // generate & set control vector to Rect
			vecIniRect.push_back(r); //make a vector of initial rectangles
			vecBoundaryRect.push_back(r);
			r.clrState();
			r.subdivide(r, 0, 0, parentVec[0]); // construct the vectors of rects from initial rect

			vector<Rect> rv;
			rv.clear();
			rv = r.getRectVector();// get the vector of output vectors
			vecOutRect.push_back(rv); // vector of output vectors from subdivision of initial rectangles
		}
	}
}

void ofApp::update() {

}

void ofApp::draw() {
	ofBackground(255, 255, 255);
	ofSetColor(255, 255, 255); ofFill(); ofDrawRectangle(0, 0, 1200, 750); ofNoFill();
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Press 'c' to change color scheme", 10, 600);
	ofDrawBitmapString("Press 'p' to take a  screen-shot", 10, 615);
	ofDrawBitmapString("Nirvik Saha\nDennis Shelden\nJohn Haymaker", 10, 650);
	for (int i = 0; i < vecBoundaryRect.size(); i++) {
		Rect R = vecBoundaryRect[i];
		vecBoundaryRect[i].drawRect(3);
		/* index of rect */
		ofSetColor(0, 0, 0);
		ofDrawBitmapString(to_string(i), R.getA().x - 20, R.getA().y + 10);
	}
	for (int i = 0; i < colrArStructVec.size(); i++) {
		float this_ar = colrArStructVec[i].area;
		int re = colrArStructVec[i].re;
		int gr = colrArStructVec[i].gr;
		int bl = colrArStructVec[i].bl;
		ofSetColor(re, gr, bl); 
		float x = 50; float y = 50+25*i; float w = 15; float h = 15;
		ofFill();  ofDrawRectangle(x, y, w, h);
		ofSetColor(0, 0, 0);
		string pr = to_string(i) + ". " + to_string((int)this_ar);
		ofDrawBitmapString(pr, x + 25, y+12.5);
	}

	for (int i = 0; i < vecOutRect.size(); i++) {
		for (int j = 0; j < vecOutRect[i].size(); j++) {
			Rect p = vecOutRect[i][j];
			Pt m = p.getCen(); float ar = p.getCoordArea();
			int re, gr, bl, index;
			int sum = 0;
			for (int i = 0; i < colrArStructVec.size(); i++) {
				float this_ar = colrArStructVec[i].area;
				if (fabs(this_ar - ar) < 1){
					re = colrArStructVec[i].re;
					gr = colrArStructVec[i].gr;
					bl = colrArStructVec[i].bl;
					index = i;
					sum++;
					break;
				}
			}
			p.drawRect(re, gr, bl);
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(index, m.x, m.y);
		}
	}
}

void ofApp::keyPressed(int key){
	if ((key == 'c') || (key == 'p')) {
		//do not set-up
	}else{
		setup();
	}	
	if (key == 'c') {
		colrArStructVec = ar.genColorVec();
	}
	if (key == 'p') {
		global_counter++;
		ofImage screenshot;
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.saveImage("img"+to_string(global_counter) + ".png");
	}
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){
}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
