
function setup() {
  createCanvas(windowWidth, windowHeight); // make the canvas

  // setup serial
  setupSerial();
  //init pixels
}

function draw() {
  background(0); // black background
  
  

}



//handle all serial coms 
function serialEvent() {
  // read a string from the serial port
  // until you get carriage return and newline:
  let inString = serial.readStringUntil("\r\n");
  //check to see that there's actually a string there:

  // call get readings
  print(inString);

  //
  //if (inString) {
  //  let data = split(inString, ":");
  //  //console.log(data[0]);
  //  //console.log(data[1]);
    
  //  let positionIndex = data[0];
  //  //let readings = split(data[1], " ");
  //  //console.log(readings);
  //  processData(positionIndex, readings);
  //  serial.write("x");
  //}
}

//this needs to be debugged using debugger! transfer to a local sketch!

