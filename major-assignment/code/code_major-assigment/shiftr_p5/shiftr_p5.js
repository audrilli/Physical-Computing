
// MQTT client details:
let broker = {
  hostname: 'lars-z.cloud.shiftr.io',
  port: 443
 };

// client credentials:
let creds = {
  clientID: 'p5',
  userName: 'lars-z',
  password: 'LjqFVFUPPVy63GyF'
};

// MQTT client:
let client;


// topics you want to subscribe to when you connect
let gyro = '/Gyro';
let gyroThing;

let lastTimeSent = 0;
const sendInterval = 100;


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
    useSSL: true   // use SSL
  } );
}

function draw() {
  
  background(220);
  noStroke();
  fill(0);
  circle(width/2,height/2,gyroThing*100);
}

// called when the client connects
function onConnect() {
  console.log('Client is connected');
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
  
  //let's split the message so we know which values we receive
  //startsWith() is a JavaScript function which checks if message starts with a particular word or series of characters
  if(receivedMessage.startsWith("gyro")){
    let gyroVal = split(receivedMessage, ',');
    gyroThing = gyroVal[1];
    console.log(gyroThing);
  }
}
