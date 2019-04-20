let serialValue;
 
let myOscillator;
let ampValue;
let freqValue;
let counter=1;
let counter2=1;
let counter3=1;
let counter4=1;
let counter5=1;
let counter6=1;
let counter7=1;
let counter8=1;

function setup() {
  createCanvas(1000, 1500);
  colorMode(HSB);
  background(10, 10, 10);
  // Instantiate our SerialPort object
  //serial = new p5.SerialPort();
  serial = new p5.SerialPort('149.31.124.151'); //to connect remotedly using local IP

  // Let's list the ports available
  var portlist = serial.list();

  // Assuming our Arduino is connected, let's open the connection to it
  // Change this to the name of your arduino's serial port
  serial.open("/dev/cu.usbmodem1411");

  // Register some callbacks

  // When we connect to the underlying server
  serial.on('connected', serverConnected);

  // When we get a list of serial ports that are available
  serial.on('list', gotList);

  // When we some data from the serial port
  serial.on('data', gotData);

  // When or if we get an error
  serial.on('error', gotError);

  // When our serial port is opened and ready for read/write
  serial.on('open', gotOpen);


  
}

// We are connected and ready to go
function serverConnected() {
  console.log("We are connected!");
}

// Got the list of ports
function gotList(thelist) {
  // theList is an array of their names
  for (var i = 0; i < thelist.length; i++) {
    // Display in the console
    console.log(i + " " + thelist[i]);
  }
}

// Connected to our serial device
function gotOpen() {
  console.log("Serial Port is open!");
}

// Ut oh, here is an error, let's log it
function gotError(theerror) {
  console.log('error', theerror);
}

// There is data available to work with from the serial port
function gotData() {
  while(serial.available() > 0) {
    serialValue = serial.read();
  }
 
  console.log('val',serialValue);
  
  
}

function draw() {
  // Polling method
  
  noFill();
  //stroke(255,255,255,100);
  //fill(20, 20, 20,5);
  //rect(0,0,width,height);
  //fill(255,255,255,5);
 
    //ampValue= Math.floor(map(serialValue,0,255,1,10));
    //ellipse(width/2,height/2,serialValue*40,serialValue*40);
    //console.log(serialValue);

    if(serialValue==1){
      stroke(counter%255,random(100),random(100));
      ellipse(875,125,serialValue*counter,serialValue*counter);
      //line(875,250+125,cos(PI)*counter+100,sin(PI)*counter+100);
      counter= counter +1;
      //console.log("counter" + counter);
    }

    if(serialValue==2){
      stroke(counter2%255,random(100),random(100));
      ellipse(875,575,serialValue*counter2,serialValue*counter2);
      counter2= counter2 +1;
      //console.log("counter" + counter);
    }
  
    if(serialValue==3){
      stroke(counter3%255,random(100),random(100));
      ellipse(125,575,serialValue*counter3,serialValue*counter3);
      counter3= counter3 + 1;
      //console.log("counter" + counter);
    }

    if(serialValue==4){
      stroke(counter4%255,random(100),random(100));
      ellipse(125,125,serialValue*counter4,serialValue*counter4);
      counter4= counter4 +1;
      //console.log("counter" + counter);
    }

    if(serialValue==5){
      stroke(counter5%255,random(100),random(100));
      ellipse(625,250,serialValue*counter5,serialValue*counter5);
      counter5= counter5 +1;
      //console.log("counter" + counter);
    }
  
    if(serialValue==6){
      stroke(counter6%255,random(100),random(100));
      ellipse(625,425,serialValue*counter6,serialValue*counter6);
      counter6= counter6 +1;
      //console.log("counter" + counter);
    }

    if(serialValue==7){
      stroke(counter7%255,random(100),random(100));
      ellipse(300,425,serialValue*counter7,serialValue*counter7);
      counter7= counter7+1;
      //console.log("counter" + counter);
    }
  
    if(serialValue==8){
      stroke(counter8%255,random(100),random(100));
      ellipse(300,250,serialValue*counter8,serialValue*counter8);
      counter8= counter8 +1;
      //console.log("counter" + counter);
    }
}