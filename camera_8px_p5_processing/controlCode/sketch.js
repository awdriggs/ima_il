
//img vars
let pixelArray = []; //will be a 2d array
let pixelSize = 10; //make sliders for this data to tune after a photo is caputured.
let sliceSize = 1;
let numPasses = 1; //how many bakc and forth passes to make, darker images need more passes
let degress = 180;
let pos = 0;

//control variabls
let img = false;

function setup() {
  createCanvas(windowWidth, windowHeight); // make the canvas

  // setup serial
  setupSerial();
  //init pixels
}

function draw() {
  background(0); // black background
  
  //if there is an image ready, display it
  

}

function keyPressed(){
  if(key == "c"){
    startCapture();
  }
}


//handle all serial coms 
function serialEvent() {
  // read a string from the serial port
  // until you get carriage return and newline:
  let inString = serial.readStringUntil("\r\n");
  //check to see that there's actually a string there:

  // call get readings

  //
  if (inString) {
    let data = split(inString, ":");
    //console.log(data[0]);
    //console.log(data[1]);
    
    let positionIndex = data[0];
    let readings = split(data[1], " ");
    //console.log(readings);
    processData(positionIndex, readings);
    serial.write("x");
  }
}

//this needs to be debugged using debugger! transfer to a local sketch!

//write script to process the input
function processData(pos, newValues){
  if(pixelArray[pos]){
    for(let i = 0; i < newValues.length; i++){
      let prev = pixelArray[pos][i];
      prev = (prev + newValues[i])/2;
      pixelArray[pos][i] = prev;
    }
  } else {
    pixelArray[pos] = newValues;
  }
  
  console.log(pos, pixelArray[pos]);
}


//initialize the pixels
function resetPixels(){
  //double for, 180 by 8, put a 0 at each index position
}

function getReading(pos){
  //send servo to that postion and ask for a reading
}

function startCapture(){
  //atart the process to capture images
  pos = 0;

  for(let i = 0; i < numPasses; i++){
    //each pass is a back and forth sweep
    //sweep
    for(let d = 0; d < degrees; d++){
      //move through the degrees
      //call getReading(2);
      //
    }
  }
}

//process?
//flatten the array
//quick sort the array
//find the min value, this will be black
//find the max value, this will be white

//display image
//loop through the pixel array
//for each i value, draw a column
//for each j value, draw a pixel
//map the reading at pixelArray[i][j] from min/max to 0, 255 to get a gray value


