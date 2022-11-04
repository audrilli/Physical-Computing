// MQTT client details:
let broker = {
  hostname: "lars-z.cloud.shiftr.io",
  port: 443,
};

// client credentials:
let creds = {
  clientID: "p5",
  userName: "lars-z",
  password: "h57VsZfr5qpWt1tu",
};

// MQTT client:
let client;

// topics you want to subscribe to when you connect
let gyro = "/Gyro";
// let gyroThing;

let lastTimeSent = 0;
const sendInterval = 100;

//SoundSetup
let mySound;
let baseSound;
let addSound;
let playing = false;

//FreqSetUp
let osc;
osc = new p5.Oscillator("sine");

let freqNow = 100;
let freqLast = 100;
let alpha = 0.1;
let freqza = 1000;
let gamma = 1;

//variables recieved Message
let xa;
let ya;
let xg;
// let yg
// let zg
let za = 0.04;

//Frequency analyse
let fft;
angleMode(DEGREES);

function onSoundLoadSuccess(e){
  console.log("load sound success",e);
}
function onSoundLoadError(e){
  console.log("load sound error",e);
}
function onSoundLoadProgress(e){
  console.log("load sound progress",e);
}

function preload() {
  soundFormats("mp3");
  mySound = loadSound("soundassets/sound1.mp3",onSoundLoadSuccess,onSoundLoadError,onSoundLoadProgress);
  baseSound = loadSound("soundassets/baseTone1_mixdown.mp3",onSoundLoadSuccess,onSoundLoadError,onSoundLoadProgress);
  addSound = loadSound("soundassets/baseTon2_01.mp3",onSoundLoadSuccess,onSoundLoadError,onSoundLoadProgress);
  chordSound = loadSound("soundassets/chord.mp3",onSoundLoadSuccess,onSoundLoadError,onSoundLoadProgress,)
}

function setup() {
  // Create an MQTT client: 
  client = new Paho.MQTT.Client(broker.hostname, broker.port, creds.clientID);

  // set callback handlers for the client:
  client.onConnectionLost = onConnectionLost;
  client.onMessageArrived = onMessageArrived;

  // connect to the MQTT broker:
  client.connect({
    onSuccess: onConnect, // callback function for when you connect
    userName: creds.userName, // username
    password: creds.password, // password
    useSSL: true, // use SSL
  });

  fft = new p5.FFT(0.9,256);
}

function draw() {
  let cnv = createCanvas(windowWidth, windowHeight);
  cnv.mousePressed(canvasPressed);

  background(0);
  // noStroke();
  // fill(0);
  // circle(width / 2, height / 2, xa * 100);

  osc.amp(0.3);
  baseSound.setVolume(1);
  addSound.amp(0.5);
  chordSound.amp((map(xa,-2.5,2,0,1)));
console.log("volume chord Sound: ",chordSound.amp())
  // mySound.amp(0.1);

  //Freq filter
  freqza = (za*20);
  osc.freq(freqNow);
  freqLast = freqNow;
  freqNow = alpha * int(freqza) + (1 - alpha) * freqLast;
  // console.log(freqNow);

  //FFT Analization
  let spectrum = fft.analyze();

//stroke(255);
translate(width/2, height/2);
beginShape();


for(var  i = 0; i< spectrum.length; i++){
  var angle = map(i,0,spectrum.length,0,360);
  var amp = spectrum[i];
  // var transp = spectrum[i];
  var r = map(amp,0,256,100,200);
  var x = r*cos(angle);
  var y= r*sin(angle);
  // var a = spectrum[i];
  
  curveVertex(x,y,50);
//  console.log(i);
  
  // var y=map(amp,0,200,height,0);
  // line(i ,height, i,y );
  //circle(width/2 ,height/2, i/2, );
}
// fill(255,255,255,transp/4);
noFill();
stroke(255);  

endShape();
  // console.log(spectrum.length);
  

}
function canvasPressed() {
  // console.log(osc);
  if (!playing) {
    // mySound.play();
    baseSound.loop();
    osc.start();
    chordSound.loop();
    // addSound.play();

    console.log("playing");
  } else {
    // mySound.pause();
    baseSound.pause();
    osc.stop();
    chordSound.pause();
    // addSound.pause();

    console.log("stopped");
  }
  playing = !playing;
}

// called when the client connects
function onConnect() {
  console.log("Client is connected");
  client.subscribe(gyro);
}

// called when the client loses its connection
function onConnectionLost(response) {
  if (response.errorCode !== 0) {
    console.log(response.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  let receivedMessage = message.payloadString;
  let splitString = split(receivedMessage, ",");

  xa = float(splitString[0]);
  ya = float(splitString[4]);
  za = float(splitString[5]);

  xg = float(splitString[0]);
  yg = float(splitString[1]);
  zg = float(splitString[2]);

  // console.log("xa:", xa);
  // console.log("ya:", ya);
  console.log("za:", za);
  // console.log("xg:", xg);
  // console.log("yg:", yg);
  // console.log("zg:", zg);

  // let's split the message so we know which values we receive
  // startsWith() is a JavaScript function which checks if message starts with a particular word or series of characters
  // if(receivedMessage.startsWith("gz")){
  // let gyroVal = split(receivedMessage, ',');
  // gyroThing = gyroVal[1];
  // console.log(gyroThing);
}
