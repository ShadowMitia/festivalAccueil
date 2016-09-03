#include "ofApp.h"


constexpr int size{50};
constexpr int w{640};
constexpr int h{480};

//--------------------------------------------------------------
void ofApp::setup(){
  grabber.setup(w, h);

  a.load("a.png");
  aa.load("A.JPG");
  aa.resize(size, size);
  a.resize(size, size);
  p.load("p.png");
  pp.load("p.jpg");
  p.resize(size, size);
  pp.resize(size, size);
  o.load("o.png");
  oo.load("o.jpg");
  o.resize(size, size);
  oo.resize(size, size);
  i.load("i.png");
  ii.load("i.jpg");
  i.resize(size, size);
  ii.resize(size, size);
  l.load("l.png");
  ll.load("l.jpg");
  l.resize(size, size);
  ll.resize(size, size);

  box2d.init();
  box2d.setGravity(0, 10);
  box2d.createGround();
  box2d.setFPS(60.0);

  addLetter(box2d, aa, a, 300, 100);
  addLetter(box2d, pp, p, 350, 100);
  addLetter(box2d, oo, o, 400, 100);
  addLetter(box2d, ii, i, 450, 100);
  addLetter(box2d, ll, l, 500, 100);

  tmp.allocate(w, h);
  tmpCol.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::update() {
  box2d.update();

  grabber.update();
  if (grabber.isFrameNew()) {
    /*
    tmpCol.setFromPixels(grabber.getPixels(), 640, 480);
    tmp = tmpCol;
    tmp.threshold(80);
    */

    absdiff(grabber, previous, diff);
    diff.update();
    diff.mirror(false, true);
    // like ofSetPixels, but more concise and cross-toolkit
    copy(grabber, previous);
    finder.setThreshold(5);
    finder.setMinArea(50);
    finder.setMaxArea(500000);
    finder.findContours(diff);
  }

  if ((ofGetElapsedTimeMillis() - prevTime) > 3000) {
    addLetter(box2d, aa, a, ofRandom(0, w), 100);
    addLetter(box2d, pp, p, ofRandom(0, w), 100);
    addLetter(box2d, oo, o, ofRandom(0, w), 100);
    addLetter(box2d, ii, i, ofRandom(0, w), 100);
    addLetter(box2d, ll, l, ofRandom(0, w), 100);
    prevTime = ofGetElapsedTimeMillis();
  }

}

//--------------------------------------------------------------
void ofApp::draw() {
  /*
  tmp.draw(0, 0);
  if (finder.blobs.size() > 0) {
    ofSetColor(ofColor::blue);
    finder.blobs[0].draw();
  }
  */
  //diff.draw(0, 0);
  //finder.draw();

   ofSetColor(ofColor::red);
   edgeLine.clear();
   edgeLine.resize(finder.getContours().size());
   for (auto j = 0; j < finder.getContours().size(); j++) {
     if (finder.getContours()[j].size() <= 3){
       continue;
     }
     for (unsigned int i = 0; i < finder.getContours()[j].size(); i++) {
       auto pos = finder.getContours()[j][i];
       drawing.addVertex(pos.x, pos.y);
       drawing.setClosed(true);
       drawing.simplify();
       edgeLine[j].addVertexes(drawing);
       drawing.clear();
     }

     edgeLine[j].setPhysics(1.0, 0.0, 1.0);
     edgeLine[j].create(box2d.getWorld());
     edgeLine[j].updateShape();
   }
   ofPushMatrix();
   ofScale(1.5, 1.5);
   for (auto& e : edgeLine){
     e.draw();
   }
   ofPopMatrix();

   ofPushMatrix();
   ofSetColor(ofColor::blue);
   for (auto i = 0; i < letters.size(); ++i) {
     letters[i]->draw();
   }
   ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'l'){
    addLetter(box2d, aa, a, ofRandom(0, w), 100);
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
