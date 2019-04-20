#pragma once

#include "ofMain.h"
#include "pbNetwork.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

	int w, h;			// Width and height of image
	int size;			// Size of image data in bytes

	ofPixels linePix;
	ofImage image;		// Received image

	pbNetworkReceiver receiver;	//Network receiver
	int frameNum;
    
    
    ofVideoGrabber     grabber;        // Video grabber
    
    pbNetworkSenderSync sender;        // Network sender
    int lineNum;
    

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
