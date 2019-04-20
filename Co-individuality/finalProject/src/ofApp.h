#pragma once

#include "ofMain.h"
#include "pbNetwork.h"
#include "SlitScan.hpp"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    
    void updateRemoteImg();

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
	
	pbNetworkSenderSync sender;	// send to specific IP
	pbNetworkReceiver receiver;	// receive from any
	
	ofVideoGrabber grabber;
	int w, h, bytesPerLine;
	
	string remoteIP;
	int remotePort, localPort;
	
	int lineNum;
	
	int remoteLineNum;
	
	ofPixels remoteLinePix;	// this will contain the latest received line
	ofImage remoteImg;		// this will accumulate the lines as a remote slit scan
    
    ofVideoGrabber vid;
    SlitScan slitScan;
    
    ofMesh mesh;
    ofMesh meshExt;
    
    float rotation = 180;
    
    ofBlendMode blendMode;
    
    ofEasyCam cam;
    
    int tex= 10;
    int tex2= 10;
	
    bool textureOn = false;
};
