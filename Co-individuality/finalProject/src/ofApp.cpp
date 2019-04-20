#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
     ofSetWindowTitle("SlitScan Blending");
    
    ofBackground(0);
	// ask user for IP address and ports we'll use for connections
    
    
    ofDisableArbTex();    // map image textures properly to of3DPrimitive meshes
    
	
	remoteIP = ofSystemTextBoxDialog("input remote IP (ex. 127.0.0.1) - where to send our image data");
	
	string rPortStr = ofSystemTextBoxDialog("input remote port (where we'll send data)");
	remotePort = ofToInt(rPortStr);
	
	string lPortStr = ofSystemTextBoxDialog("input local port (where we'll receive image data)");
	localPort = ofToInt(lPortStr);
	
	
	// set up sender to remote IP and port
	
	sender.setup(remoteIP, remotePort);
	
	// set up receiver on local connection port
	
	receiver.setup(localPort);
	
	// setup webcam
	
	w = 640;
	h = 480;
	
	grabber.setup(w,h);
	lineNum = 0;
	
	bytesPerLine = w * 3;	// # bytes per line = width * num channels (RGB)
	
	
	// allocate image where we'll store the pixels from the remote, line by line
	
	remoteImg.allocate(w,h,OF_IMAGE_COLOR);
    
    
    // setup the slitscan object
    
    slitScan = SlitScan(640, 480);  // create slit scan
    
    blendMode = OF_BLENDMODE_SCREEN;
    
    // setup the mesh
    
    mesh = ofMesh::plane(640, 480, 128, 96);
    meshExt = ofMesh::plane(640, 480, 128, 96);
    

}

//--------------------------------------------------------------
void ofApp::update(){
	
	grabber.update();	// update webcam
    
//    if (grabber.isFrameNew() )
//    {
//        // update the slit scans
//
//        slitScan.addLine(grabber.getTexture());
//
//        // grab the pixels to read color
//        ofPixels pix = slitScan.getPixels();
//
//        // loop through the mesh
//        for (int i=0; i<mesh.getVertices().size(); i++)
//
//
//        {
//
//            ofVec3f vert    = mesh.getVertex(i);
//
//            float imgX    = ofMap(vert.x, -320, 320, 0, pix.getWidth()-1);
//            float imgY    = ofMap(vert.y, -240, 240, 0, pix.getHeight()-1);
//            ofColor color    = pix.getColor(imgX, imgY);
//            vert.z    = ofMap( color.getBrightness(), 0, 255, 0, tex);
//
//            // update vert z
//            mesh.setVertex(i, vert);
//        }
//
//    }

	
	// RECEIVE
	
	
	// Check if new frame was received automatically
	// (the receiver runs in a separate thread)
	
    if ( receiver.frame() != remoteLineNum || grabber.isFrameNew() ) {
        
        
		
		if ( receiver.size() == bytesPerLine ) {	// data size match for 1 line
			
            updateRemoteImg();
            
            
            // loop through the mesh
            for (int i=0; i<meshExt.getVertices().size(); i++)
            {
                
                ofVec3f vert    = meshExt.getVertex(i);
                
                float imgX    = ofMap(vert.x, -320, 320, 0, remoteLinePix.getWidth()-1);
                float imgY    = ofMap(vert.y, -240, 240, 0, remoteLinePix.getHeight()-1);
                ofColor color    = remoteLinePix.getColor(imgX, imgY);
                vert.z    = ofMap( color.getBrightness(), 0, 255, 0, tex2);
                
                // update vert z
                meshExt.setVertex(i, vert);
            }
            

            
            // UPDATE THE LOCAL SLIT SCAN HERE
            
            // update the slit scans
            
            slitScan.addLine(grabber.getTexture());
            
            // grab the pixels to read color
            ofPixels pix = slitScan.getPixels();
            
            // loop through the mesh
            for (int i=0; i<mesh.getVertices().size(); i++)
                
                
            {
                
                ofVec3f vert    = mesh.getVertex(i);
                
                float imgX    = ofMap(vert.x, -320, 320, 0, pix.getWidth()-1);
                float imgY    = ofMap(vert.y, -240, 240, 0, pix.getHeight()-1);
                ofColor color    = pix.getColor(imgX, imgY);
                vert.z    = ofMap( color.getBrightness(), 0, 255, 0, tex);
                
                // update vert z
                mesh.setVertex(i, vert);
            }
            
			
		}
		else if ( receiver.size() != 0 ) {
			
			cout << "ERROR: Network received data with size: " << receiver.size() << " (doesn't match bytes per line)" << endl;
		}
		
	}
	
	
	
	// SEND
	
	
	sender.update();	// tries reconnect to remote if disconnected
	
	if (grabber.isFrameNew()){	// check for new frame
		
		// send whole frame:
		
		//		unsigned char * data = grabber.getPixels().getData();
		//		int size = grabber.getPixels().getTotalBytes();
		//		sender.send( data, size, lineNum );
		
		// send current line:
		
		unsigned char * pixData = grabber.getPixels().getData();
		
		int lineStart = bytesPerLine * lineNum;			// the pixel index at start of line
		unsigned char * line = pixData + lineStart;		// pointer to that pixel
		
		sender.send( line, bytesPerLine, lineNum);		// send the data at pointer, with line size, and line number as frame ID
		
		// increment line number
		
		lineNum++;
		if (lineNum >= h) lineNum = 0;
	}
	
	

}

void ofApp::updateRemoteImg()
{
    
    remoteLineNum = receiver.frame();
    // frame() returns the latest "frame ID" received (we are using this for line number ID)
    
    
    // if this was a whole image we could copy it directly:
    //        remoteImg.setFromPixels(  &receiver.data()[0], w, h, OF_IMAGE_COLOR );
    
    
    // set received data to pixels line
    
    remoteLinePix.setFromPixels( &receiver.data()[0], w, 1, 3);    // data, width, height, num channels
    
    /* --
     note: receiver.data() returns a vector -
     To get the data array at index i from a vector, you can use &vector[i]
     -- */
    
    // copy pixel data from line pixels to ofImage:
    
    int lineStart            = remoteLineNum * bytesPerLine;        // the start index of this line in the image data
    unsigned char * imgPtr    = remoteImg.getPixels().getData() + lineStart;
    
    // copy the memory block from the line pixel data to image data
    memcpy(imgPtr, remoteLinePix.getData(), bytesPerLine);
    
    remoteImg.update();    // update the image texture
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    
    ofEnableBlendMode(blendMode);
    
   

    
    
	// draw local
	
//    ofSetColor( 200, 255, 200 );
    //ofDrawRectangle( 0,0, ofGetWidth()*.5,ofGetHeight() );
//
	// draw webcam image
    
    cam.begin();
    
     ofRotateX(rotation);
    
//    slitScan.draw(20,20, 640, 480);
    
    slitScan.bind();

        mesh.draw();
    slitScan.unbind();
	
	//ofSetColor( 255 );
	//grabber.draw( 20, 20 );
	
	// print local line num
	
//    ofSetColor( 0 );
//    ofDrawBitmapString( "Local line num = " + ofToString( lineNum ), 20, h + 40 );
//
//    ofDrawBitmapString( "Sending to remote IP: " + remoteIP + " : " + ofToString( remotePort ), 20, h + 60 );
	
	
//
    // draw remote

   // ofTranslate( ofGetWidth() * .5, 0 );


//    ofSetColor( 200, 200, 255 );
    //ofDrawRectangle( 0,0, ofGetWidth()*.5,ofGetHeight() );

    // draw received image
//    ofSetColor( 255 );
    
    
//    remoteImg.draw( 20, 20 );
    
    remoteImg.getTexture().bind();
    
        meshExt.draw();
    
    remoteImg.getTexture().unbind();

    
//
    // print remote line num and FPS
//    ofSetColor( 0 );
    ofDrawBitmapString( "Remote line num = " + ofToString( remoteLineNum ), 20, h + 40 );

    ofDrawBitmapString( "Receiving on local port: " + ofToString( localPort ), 20, h + 60 );
    
    cam.end();
  ofDisableBlendMode();
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == 32){ // also ' ' for space as a character ASCI
        
        
        if (!textureOn){
            
            tex= 100;
            tex2= -100;
            
            
        }
        if(textureOn){
            
            tex= 10;
            tex2= 10;
            
            
        }
        textureOn= !textureOn;
        cout<<textureOn<<endl;
    }

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
    
//    if (!textureOn){
//
//        tex= 100;
//        tex2= -100;
//
//
//    }
//    if(textureOn){
//
//        tex= 10;
//        tex2= 10;
//
//
//    }
//    textureOn= !textureOn;
//    cout<<textureOn<<endl;

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
