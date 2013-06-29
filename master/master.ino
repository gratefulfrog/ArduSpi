// ArudSPI_master

#define LED_PIN 13

const int slavePause = 2000,
          nbSlaves = 2,
          select = 0,
          ack = 1,
          slaves[nbSlaves][2] = {{2,3},//slave O {Select,ack}
                                 {4,5}};  //slave 1 {Select,ack}

// some pretend data to send to the slaves
char dataOut[nbSlaves] = {'x','y'};

void setup(){
  Serial.begin(9600);
  for (int i=0;i<nbSlaves;i++){
    pinMode(slaves[i][select], OUTPUT);   
    digitalWrite(slaves[i][select], LOW);
    pinMode(slaves[i][ack], INPUT);   
  }
  pinMode(LED_PIN, OUTPUT);
  waitForSlaves();
}

void waitForSlaves(){
  // pulse LED for 5 seconds before going to the loop.
  // this gives time to turn on the slaves,
  // it is preferable to turn the slaves on before the master
  for(int i=0;i<5;i++){
    delay(1000);
    pulse(1);
  }
}

void loop(){
  for (int i=0;i<nbSlaves;i++){
    // give visual feedback that we are about to write to a slave
    // the number of pulses = 3*SlaveID
    pulse(i+1);
    writeSlave(i,dataOut[i]);
    delay(slavePause);
  }
}

void pulse(int c){
  // pulse the LED 3 * (arg+1) times
  for(int i=0;i<3*c;i++){
    digitalWrite(LED_PIN,HIGH);
    delay(200);
    digitalWrite(LED_PIN,LOW);
    delay(200);
  }
}

void writeSlave(int id, char data){
  // select salve
  digitalWrite(slaves[id][select],HIGH);
  // send off the data
  Serial.write(data); 
  // wait for the slave to ACK receptions
  while(digitalRead(slaves[id][ack]) == LOW){;}
  // deselect the slave
  digitalWrite(slaves[id][select],LOW);
}
