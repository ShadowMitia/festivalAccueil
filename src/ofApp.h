#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class CustomPolygonLetter {
  std::unique_ptr<ofxBox2dPolygon> polygon;
  ofImage texture;
  ofMesh mesh;

public:

  void setup(ofxBox2d& world, std::vector<ofPoint> pts, ofImage tex, int x, int y) {
    texture = tex;
    //texture.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    //texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
    polygon = std::make_unique<ofxBox2dPolygon>();
    polygon->addVertices(pts);

    //mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //mesh.addVertex(ofVec2f(texture.getWidth()/2, texture.getHeight()/2));
    mesh.addVertices(pts);
    for (auto i = 0; i < pts.size() -1 ; i++) {
      mesh.addTexCoord(pts[i]);
      //mesh.addTexCoord(ofVec2f(texture.getWidth() / 2,texture.getHeight() / 2));
      mesh.addTexCoord(pts[i+1 % pts.size()]);
    }
    polygon->setPhysics(1.0, 0.3, 0.3);
    polygon->create(world.getWorld());
    polygon->setPosition(x, y);
  }

  void draw() {
    auto center = polygon->getPosition();
    /*
    ofSetColor(ofColor::white);
    polygon->draw();
    */
    texture.setAnchorPoint(texture.getWidth() / 2, texture.getHeight() / 2);
    ofPushMatrix();
    texture.draw(center.x, center.y);
    ofPopMatrix();


  }

};

class ofApp : public ofBaseApp {


public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
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

  ofxBox2d box2d;

  ofImage a, p, o, i, l;
  ofImage aa, pp, oo, ii, ll;

  std::vector<std::shared_ptr<CustomPolygonLetter>> letters;

  ofVideoGrabber grabber;

  std::vector<ofxBox2dEdge> edgeLine;
  ofPolyline drawing;

  ofxCvGrayscaleImage tmp;
  ofxCvColorImage tmpCol;
  ofxCvContourFinder f;

  ofPixels previous;
  ofImage diff;

  // a scalar is like an ofVec4f but normally used for storing color information
  cv::Scalar diffMean;
  ContourFinder finder;

  int prevTime = 0;

   void addLetter(ofxBox2d& box2d, ofImage img, ofImage img2, int x, int y){
      tmpCol.setFromPixels(img.getPixels());
      tmp = tmpCol;
      tmp.threshold(120);
      f.findContours(tmp, 5, 10000, 1, true);
      auto c = make_shared<CustomPolygonLetter>();
      c->setup(box2d, f.blobs[0].pts, img2, x, y);
      letters.push_back(c);
  };

};
