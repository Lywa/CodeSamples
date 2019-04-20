#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	
	//Set image size
	w = 640;
	h = 480;
	
	size = w * h * 3;

	//Starting network
	int port = 12345;
	int packetSize = 1024;
    
   
    string addr = "127.0.0.1";
    
    // ----  SEND ------
    
    sender.setup( addr, port, packetSize );
    lineNum = 0;
    
    //Starting camera
    grabber.listDevices();
    grabber.setDeviceID(1);
    grabber.setup(w,h);

    
    
    
    // ---- RECEIVE -----
//    receiver.setup(port, packetSize, true);
//    frameNum = 0;
//
//    image.allocate(w,h,OF_IMAGE_COLOR);
//
}

//--------------------------------------------------------------
void ofApp::update(){
    // ----  SEND ------
    
    sender.update();
    
    grabber.update();    //Update grabber state
    
    if (grabber.isFrameNew()){    //Check for new frame
        
        //Send frame via network
        //        unsigned char * pixels = grabber.getPixels().getData();
        //        sender.send( pixels, size, lineNum );
        
        // Send single line over network
        unsigned char * pixels = grabber.getPixels().getData();
        
        int lineStartIndex = w * 3 * lineNum;
        unsigned char * line = pixels + lineStartIndex;
        
        sender.send( line, w * 3, lineNum);
        
        lineNum++;
        if (lineNum >= h) lineNum = 0;
    }
    
    
    // ---- RECEIVE -----
    
    
//    // Check if new frame was received automatically
//    // (the receiver runs in a separate thread)
//
//    if ( receiver.frame() != frameNum ) {    // frame() returns the latest frame number received
//
//        frameNum = receiver.frame();
//
//        if ( receiver.size() == w * 3 ) {    // data size match for 1 line
//
//
//            //Set received data to image
////            image.setFromPixels(  &receiver.data()[0], w, h, OF_IMAGE_COLOR );
//
//
//            //Set received data to pixels line
//
//            linePix.setFromPixels( &receiver.data()[0], w, 1, 3);
//
//            // copy pixel data of ofImage
//
//            int lineStartIndex = w * 3 * frameNum;
//            unsigned char * imgPtr = image.getPixels().getData() + lineStartIndex;
//
//            // copy the memory from line pixels to image
//            memcpy(imgPtr, linePix.getData(), w * 3);
//
//            image.update();    // update the image texture
//
//        }
//        else {
//            cout << "ERROR: Network received data with bad size, check image sizes" << endl;
//        }
//
//    }
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   
    // ----  SEND ------
    
    //Draw camera image
    ofSetColor( 255 );
    grabber.draw( 20, 20 );
    
    //Print line num
    ofSetColor( 0 );
    ofDrawBitmapString( "Line num = " + ofToString( lineNum ), 20, h + 40 );
//
//     ofEnableBlendMode(OF_BLENDMODE_SCREEN);
//
//    // ---- RECEIVE -----
//    ofBackground( 200, 200, 255 );
//
//    //Draw received image
//    if ( image.isAllocated() ) {
//        ofSetColor( 255 );
//        image.draw( 20, 20 );
//    }
//
//    //Print frame id and FPS
//    ofSetColor( 0 );
//    ofDrawBitmapString( "Received frame/line num = " + ofToString( frameNum ), 20, h + 40 );
//
//    ofDisableBlendMode();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
