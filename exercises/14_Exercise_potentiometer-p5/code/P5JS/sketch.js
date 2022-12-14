let msg;
let serialOptions = { baudRate: 9600 };
let serial;
let clicked = false;
let portInfo = { usbVendorId: 0x3EB, usbProductId: 0x2145 }
let serialData = 0

function setup() {
  createCanvas(300, 300);
  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);
 
  // If we have previously approved ports, attempt to connect with them
  // serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  
  // Add in a lil <p> element to provide messages. This is optional
  msg = createP("");
}

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(portInfo, serialOptions);
  }
}

function draw() {
  //background(255);
  background(0,0,serialData);

  if (serialData ==255) {
    background(0,0,0)
    
  } else {
    background(0,0,serialData);
    
  }
  circleChange();
  
  //sendValue();
}

function circleChange(){
  circle(150,150,serialData,100);
  fill(0,0,255);
  noStroke();
}

/**
 * Callback function by serial.js when there is an error on web serial
 * 
 * @param {} eventSender 
 */
 function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  msg.html(error);
}

/**
 * Callback function by serial.js when web serial connection is opened
 * 
 * @param {} eventSender 
 */
function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  msg.html("Serial connection opened successfully");
}

/**
 * Callback function by serial.js when web serial connection is closed
 * 
 * @param {} eventSender 
 */
function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  msg.html("onSerialConnectionClosed");
}

/**
 * Callback function serial.js when new web serial data is received
 * 
 * @param {*} eventSender 
 * @param {String} newData new data received over serial
 */
function onSerialDataReceived(eventSender, newData) {
  console.log("onSerialDataReceived", newData);
  msg.html("onSerialDataReceived: " + newData);
  serialData = newData;
}

async function serialWriteTextData() {
  const data = new Uint8Array([14, 201, 108, 255, 11]); 

  if (serial.isOpen()) {
    console.log("Writing to serial: ", data);
    serial.writeLine("<" + data + ">");
  }
}

async function serialWriteNumberData(){
  if(clicked){
    serial.writeLine("<" + 0 + ">");
    console.log(0)
    
  }else{
    serial.writeLine("<" + 1 + ">");
    console.log(1)
  }
 clicked = !clicked;
}