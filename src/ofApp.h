#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"

class CustomPolygonLetter {
  std::shared_ptr<ofxBox2dPolygon> polygon;
  ofImage texture;
  ofMesh mesh;

public:

  void setup(ofxBox2d& world, std::vector<ofPoint> pts, ofImage tex) {
    texture = tex;
    //texture.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    //texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
    polygon = std::make_shared<ofxBox2dPolygon>();
    polygon->addVertices(pts);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //mesh.addVertex(ofVec2f(texture.getWidth()/2, texture.getHeight()/2));
    mesh.addVertices(pts);
    for (auto i = 0; i < pts.size() -1 ; i++) {
      mesh.addTexCoord(pts[i]);
      //mesh.addTexCoord(ofVec2f(texture.getWidth() / 2,texture.getHeight() / 2));
      mesh.addTexCoord(pts[i+1 % pts.size()]);
    }

    //cout << "#v: " << mesh.getNumVertices() << " #tc: " << mesh.getNumTexCoords() << " #p: " << polygon->getPoints().size() << '\n';
    //polygon->setPhysics(1.0, 0.3, 0.3);
    polygon->setPhysics(0.0, 0.0, 0);
    polygon->create(world.getWorld());

  }

  void draw() {
    auto center = polygon->getCentroid2D();
    ofSetColor(ofColor::white);
    polygon->draw();
    //texture.bind();
    texture.setAnchorPoint(texture.getWidth() / 2, texture.getHeight() / 2);
    texture.draw(center.x, center.y);
    //texture.unbind();

    /*
    ofSetColor(ofColor::red);
    for (auto i = 0; i < 10; i++) {
      auto pos = polygon->getPoints()[i];
      cout << "x: " << pos.x << " " << " y: " << pos.y << '\n';
      ofDrawCircle(pos, 1);
    }
    */

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


  std::vector<std::shared_ptr<CustomPolygonLetter>> letters;
};
