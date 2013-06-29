// ArudSPI_slave

////////////////////////////////////////////////////////////////////
///  ONLY the following line needs to be changed for each slave !!!!
#define THIS_SLAVE 1
//// end of slave specifics
////////////////////////////////////////////////////////////////////

#define SLAVE_ID THIS_SLAVE
#define SELECT_PIN 10
#define ACK_PIN 11
#define LED_PIN 13

char data;
boolean ledON = false;

void setup(){
  Serial1.begin(9600);
  while(!Serial1){;}  // necessary on some Arduinos, may as well keep it.
  pinMode(SELECT_PIN, INPUT);  // we will read from the 'select' pin
  pinMode(ACK_PIN, OUTPUT);    // and write to the ACK pin
  digitalWrite(ACK_PIN, LOW);  // init it to NACK
  pinMode(LED_PIN, OUTPUT);    // set LED_PIN to writing
  digitalWrite(LED_PIN, LOW);  // and init to' off'
}

void loop(){
  // all we do is get some data and do what it says
  // if there is data, do something, otherwise loop
  if(getData()){
    doSomethingWithData();
  }
}

boolean getData(){
  // if not selected, ensure ACK_PIN is LOW and do nothing!
  if(digitalRead(SELECT_PIN)==LOW){
    digitalWrite(ACK_PIN,LOW);
    return false;
  }
  // if we got here, the the SELECT_PIN is HIGH, 
  // so we need to read serial
  // first wait for something to be available to read
  while(!Serial1.available()){;} 
  // then read 1 byte into the 'data' variable
  while(Serial1.readBytes(&data,1) == 0) {;}
  // ACK the serial read
  digitalWrite(ACK_PIN,HIGH);
  return true;
}

// just to demonstrate that the slave is doing something  
// change the LED state at every reception of data.
void doSomethingWithData(){
  ledON = !ledON;
  if (ledON){
    digitalWrite(LED_PIN,HIGH);
  }
  else{
    digitalWrite(LED_PIN,LOW);
  }
}


