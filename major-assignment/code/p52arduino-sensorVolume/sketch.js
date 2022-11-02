// const { Amplitude } = require("../../../../../../../../../.vscode/extensions/samplavigne.p5-vscode-1.2.11/p5types");

let msg;
let serialOptions = { baudRate: 9600 };
let serial;
let clicked = false;
let portInfo = { usbVendorId: 0x3eb, usbProductId: 0x2145 };
let serialData = 0;
let playing = false;
let xa = 0.0;
let za = 0.4;
let freqNow = 300;
let freqLast = 300;
let alpha = 0.01;
let freqza = 1000;

//Sounds load
let mySound;
let osc;
osc = new p5.Oscillator(300);
//osc.setType(square);
function preload() {
  soundFormats("mp3");
  mySound = loadSound("soundassets/sound1");
}

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
  //Sound Setup
}

function draw() {
  // background(255);
  // circleChange();
  let cnv = createCanvas(200, 200);
  cnv.mousePressed(canvasPressed);
  background(0, 0, 0);
  text("play", 10, 20);

  newVolume = serialData / 1023;
  // console.log(newVolume);
  mySound.setVolume(1);
  //console.log("new: ",za);


  freqza = za * 500;
  osc.freq(freqNow);
  freqLast = freqNow;
  freqNow = (alpha * int(freqza)) + ((1 - alpha) * freqLast);
  console.log(freqNow);
}

function canvasPressed() {
  console.log(osc);
  if (!playing) {
    // mySound.play();
    osc.start();
    console.log("playing");
  } else {
    // mySound.pause();
    osc.stop();
    console.log("stopped");
  }
  playing = !playing;
}

/*
function playOscillator(){
  osc.start();
  osc.amp(0.5);
  osc.freq(500+(1-za)*1000);

}
*/

function circleChange() {
  circle(150, 150, map(serialData, 0, 1023, 0, 255));
  fill(0, 0, 255);
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
  // console.log("onSerialDataReceived", newData);
  msg.html("onSerialDataReceived: " + newData);
  serialData = newData;
  // console.log(serialData);
  let splitString = split(serialData, ",");
  // console.log(splitString[0]);

  // xa = float(splitString[0]);
  za = float(splitString[5]);

  //console.log(za);
}

async function serialWriteTextData() {
  const data = new Uint8Array([14, 201, 108, 255, 11]);

  if (serial.isOpen()) {
    console.log("Writing to serial: ", data);
    serial.writeLine("<" + data + ">");
  }
}

async function serialWriteNumberData() {
  if (clicked) {
    serial.writeLine("<" + 0 + ">");
    console.log(0);
  } else {
    serial.writeLine("<" + 1 + ">");
    console.log(1);
  }
  clicked = !clicked;
}
