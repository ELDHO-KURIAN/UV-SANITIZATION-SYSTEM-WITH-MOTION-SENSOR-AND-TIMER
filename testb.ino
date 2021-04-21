float value = 34285;                   //Preload timer value (3035 for 4 seconds)
int tmr=0;
int tmr1=0;
int val=0;
int a;
int b;
int c;
int clk;
int count=0;
void setup()
{
  digitalWrite(3,HIGH);
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(5,OUTPUT);
  noInterrupts();                       // disable all interrupts
  
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = value;                        // preload timer
  TCCR1B |= (1 << CS10)|(1 << CS12);    // 1024 prescaler 
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();  // enable all interrupts
 
}

ISR(TIMER1_OVF_vect)                    // interrupt service routine for overflow
{
  TCNT1 = value;  // preload timer
  if(val==1){
  tmr=tmr+2;
  Serial.println(tmr);
  Serial.println(c); 
}
if(val==2){
  tmr1=tmr1+2;
}
}

void loop()
{
  digitalWrite(7,HIGH);
  a=digitalRead(4);
 
  c=analogRead(A0);
  if(a==1){
     digitalWrite(6,HIGH);
     digitalWrite(3,HIGH);
    val=1;
  }
 
 if(tmr>=1220){
     val=0;
     tmr=0;
     digitalWrite(3,HIGH);
     digitalWrite(6,LOW);
     digitalWrite(2,LOW);
     Serial.println("time out");
      digitalWrite(5,HIGH);
      delay(600);
       digitalWrite(5,LOW);
       
       
  }
  

if(tmr>=20 && tmr<=25){
  digitalWrite(3,LOW);
  digitalWrite(5,HIGH);
}



  if(val==1){
   if(tmr>=25){
     digitalWrite(5,LOW);
     digitalWrite(2,HIGH);
    if(c>=715){
    
      digitalWrite(2,LOW);
    digitalWrite(5,LOW);
    digitalWrite(5,HIGH);
      delay(600);
       digitalWrite(5,LOW);
     val=2;
     Serial.println("alert");
  }
  }
  }

if(val==2){
  digitalWrite(5,LOW);
  if(a==1){
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
    digitalWrite(6,LOW);
    val=0;
     tmr=0;
     tmr1=0;
      Serial.println("btn pressed");
      digitalWrite(5,HIGH);
      delay(300);
       digitalWrite(5,LOW);
      
  }
if(tmr1>=25){
  tmr1=0;
    if(c>=715){
      clk=clk+1; 
       Serial.println(clk);
    }else{
      tmr1=0;
      digitalWrite(5,HIGH);
      delay(600);
       digitalWrite(5,LOW);
       delay(600);
       digitalWrite(5,HIGH);
       delay(600);
       digitalWrite(5,LOW);
       delay(600);
       digitalWrite(5,HIGH);
       delay(600);
       digitalWrite(5,LOW);
      val=1;
      clk=0;
       Serial.println("resume");
    }

    if(clk>=4){
      clk=0;
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
    digitalWrite(6,LOW);
    val=0;
     tmr=0;
     digitalWrite(5,HIGH);
      delay(600);
       digitalWrite(5,LOW);
     Serial.println("deactive");
      
    }
  }
  
}





  
}
