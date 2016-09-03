#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

  a.load("a.png");
  a.resize(75, 75);
  p.load("p.png");
  p.resize(75, 75);
  o.load("o.png");
  o.resize(75, 75);
  i.load("i.png");
  i.resize(75, 75);
  l.load("l.png");
  l.resize(75, 75);

  box2d.init();
  box2d.setGravity(0, 0);
  box2d.createGround();
  box2d.setFPS(60.0);

  auto addLetter = [this](ofxBox2d& box2d, ofImage img){
      ofxCvGrayscaleImage tmp;
      ofxCvColorImage tmpCol;
      ofxCvContourFinder finder;
      tmpCol.setFromPixels(img.getPixels());
      tmp = tmpCol;
      tmp.threshold(180);
      finder.findContours(tmp, 5, 5000, 1, true);
      auto c = make_shared<CustomPolygonLetter>();
      c->setup(box2d, finder.blobs[0].pts, img);
      letters.push_back(c);
  };

  addLetter(box2d, a);
  addLetter(box2d, p);
  addLetter(box2d, o);
  addLetter(box2d, i);
  addLetter(box2d, l);
}

//--------------------------------------------------------------
void ofApp::update() {
  box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  /*
  tmp.draw(0, 0);
  if (finder.blobs.size() > 0){
    ofSetColor(ofColor::blue);
    finder.blobs[0].draw();
  }
  */
  ofSetColor(ofColor::white);

  ofTranslate(0, 100);
  ofScale(3, 3);
  for (auto i = 0; i < letters.size(); ++i) {
      ofTranslate(100 + 10 * i, 0);
      letters[i]->draw();
  }
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
