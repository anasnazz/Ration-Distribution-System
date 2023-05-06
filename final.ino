#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <HX711.h>

#define SS_PIN 49
#define RST_PIN 48
#define Password_Lenght 4
const byte ROWS = 4;
const byte COLS = 3;

//Loadcell 1 pins
#define LOADCELL_DOUT_PIN1 22
#define LOADCELL_SCK_PIN1 23

//Loadcell 2 pins
#define LOADCELL_DOUT_PIN2 24
#define LOADCELL_SCK_PIN2 25

//Loadcell 3 pins
#define LOADCELL_DOUT_PIN3 26
#define LOADCELL_SCK_PIN3 27

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, 12}; 
byte colPins[COLS] = {8, 7, 6}; 
byte data_count = 0;

Servo myservo1;
Servo myservo2;
Servo myservo3;
HX711 scale1;
HX711 scale2;
HX711 scale3;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27,20,4);

int statusSensor;
int user=0;
int a=0;
int b=0;
char key;
char nikey;
String rfidCard = "";
String username;
String cardtype;
String Master;
char keytemp = 'a';
char passcode;
char Data[5];
int qty=0;
int Quantity[5];
int balance;
int rice1;int ru11 = 0;int ru12 = 0;int ru13 = 0;
int rice2;int ru21 = 0;int ru22 = 0;int ru23 = 0;
int rice3;int ru31 = 0;int ru32 = 0;int ru33 = 0;
int kerosene;int ku1 = 0;int ku2 = 0;int ku3 = 0;
float weight = 0.0;
float wgt = 0.0;
float initwgt1 = 0.0;
float initwgt2 = 0.0;
float initwgt3 = 0.0;
double flow;
unsigned long pulse_freq;

void setup() {
    pinMode(42, INPUT);
    pinMode(44, OUTPUT);
    pinMode(2, INPUT);
    pinMode(30,OUTPUT);
    pinMode(0,OUTPUT);
    Serial.begin(9600);
    digitalWrite(30,HIGH);
    attachInterrupt(0, pulse, RISING);
    SPI.begin();
    myservo1.attach(38);
    myservo2.attach(39);
    myservo3.attach(40);
    myservo1.write(150);
    myservo2.write(150);
    myservo3.write(150);
    rfid.init();
    lcd.init();
    lcd.backlight();
    lcdstart();

    // Loadcell 1
    scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
    scale1.set_scale();
    scale1.tare();
    scale1.set_scale(7040);

    // Loadcell 2
    scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
    scale2.set_scale();
    scale2.tare();
    scale2.set_scale(7040);

    // Loadcell 3
    scale3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
    scale3.set_scale();
    scale3.tare();
    scale3.set_scale(7040);
    initwgtscale();
    lcd.clear();lcd.print("Put your card to the reader...");
    Serial.println("Put your card to the reader...");


}


void loop() {
  if(rfidCard=="")
  {
    getid();
  }
  else
  {
    buzzer(2000);
    lcd.clear();
    card1();
    card2();
    card3();
    lcdstart();
    lcd.print("Put your card to the reader...");
    b = 0;

  }
}

void pulse () // Interrupt function

{
  pulse_freq++;
}

void initwgtscale(void)
{
  Serial.println("Load containers");
  key = "00";
  lcd.clear();lcd.setCursor(3,2);lcd.print("Press any key");
  lcd.setCursor(5,3);lcd.print("to continue");
  while (key != keytemp )
  {
    key = keypad.getKey();
    setkey();
  }
  lcd.clear();lcd.setCursor(5,1);lcd.print("Measuring");
  Serial.println("Measuring...");
  for (int k = 0; k <=19;k++)
  {
    initwgt1 = scale1.get_units();
    initwgt2 = scale2.get_units();
    initwgt3 = scale3.get_units();
    lcd.setCursor(k,3);lcd.print(">");
    delay(150);
  }
  lcd.clear();lcd.setCursor(0,0);lcd.print("Container 1 : ");lcd.print(initwgt1);
  lcd.setCursor(0,1);lcd.print("Container 2 : ");lcd.print(initwgt2);
  lcd.setCursor(0,2);lcd.print("Container 3 : ");lcd.print(initwgt3);
  delay(2000);

}

void buzzer(int time)
{
  digitalWrite(44, HIGH);
  delay(time);
  digitalWrite(44, LOW);
}

void getid(void) {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
    }
    rfid.halt();
  }
}

void lcdstart(void)
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Welcome");
  delay(500);
  lcd.clear();
}

void card1(void)
{
  if (rfidCard=="163 204 136 17")
  {
    user=1;
    scrn1();
    Serial.println("Card 1");
    nikeypoint:;
    scrn2();
    proc();
    statusSensor = 0;
    if (a==1)
    {
      goto nikeypoint;
    }
    
    a=0;
    keytemp = 'a';
    data_count = 0;
    rfidCard = "";
    
  }
}

void card2(void)
{
  if (rfidCard=="121 87 190 153")
  {
    user=2;
    scrn1();
    Serial.println("Card 2");
    nikeypoint:
    scrn2();
    qtyproc();
    proc();
    if (a==1)
    {
      goto nikeypoint;
    }
    
    a=0;
    keytemp = 'a';
    data_count = 0;
    rfidCard = "";
    
  }
}

void card3(void)
{
  if (rfidCard=="243 128 162 11")
  {
    user=3;
    scrn1();
    Serial.println("Card 3");
    nikeypoint:
    scrn2();
    qtyproc();
    proc();
    if (a==1)
    {
      goto nikeypoint;
    }
    
    a=0;
    keytemp = 'a';
    data_count = 0;
    rfidCard = "";
    
  }
}


void scrn1(void)
{
  namedec();
  key = "00";
  lcd.clear();lcd.setCursor(3,1);lcd.print("Card Detected");
  delay(500);
  lcd.clear();lcd.setCursor(0,0);lcd.print("User Name : ");lcd.print(username);
  lcd.setCursor(0,1);lcd.print("Card Type : ");lcd.print(cardtype);
  lcd.setCursor(0,2);lcd.print("Balance : ");lcd.print(balance);
  lcd.setCursor(0,3);lcd.print("<<<Press any key>>>");

  while (key != keytemp )
  {
    key = keypad.getKey();
    setkey();
  }
  Serial.println(key);
  while (b==0)
  {
    authentication();
    data_count = 0;
  }

}

void scrn2(void)
{
    a=0;
    lcd.clear();lcd.setCursor(2,1);lcd.print("Press * key to exit");
    delay(500);
    lcd.clear();lcd.setCursor(2,1);lcd.print("Select your item");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);lcd.print("1.Rice 1 : ");lcd.print(String(rice1));lcd.print("kg");
    lcd.setCursor(0,1);lcd.print("2.Rice 2 : ");lcd.print(String(rice2));lcd.print("kg");
    lcd.setCursor(0,2);lcd.print("3.Rice 3 : ");lcd.print(String(rice3));lcd.print("kg");
    lcd.setCursor(0,3);lcd.print("4.Kerosene : ");lcd.print(String(kerosene));lcd.print("ml");
    key = '00';
    data_count = 0;
    while (key != keytemp )
    {
      key = keypad.getKey();
      setkey();
    }
    lcd.clear();
    if (key =='*')
    {
      a=0;
      goto scrn2break;
    }

//Quantity  
    lcd.setCursor(0,0);lcd.print("Enter quantity : ");
    if (key == '4')
    {
      while (data_count <= Password_Lenght - 1)
      {
        passcode = keypad.getKey();
        if (passcode == '#')
        {
          goto label2;
        }
        else if (passcode)
        {
          Quantity[data_count] = passcode;
          lcd.print(passcode);
          data_count++;
        }
        //delay(500);
        //Serial.println("Done kerosene");
      }
      label2:;
    }
    else
    {
      while (data_count <= Password_Lenght - 3)
      {
        passcode = keypad.getKey();
        if (passcode == '#')
        {
          goto label3;
        }
        else if(passcode)
        {
          Quantity[data_count] = passcode;
          lcd.print(passcode);
          data_count++;
        }
        //delay(500);
      }
      label3:;
    }
    qtyproc();
    if (key == '1')
    {
      if (rice1 > 0)
      {
        if (qty > rice1)
        {
          lcd.clear();lcd.setCursor(0,0);lcd.print("Limit exceed");
          lcd.setCursor(0,2);lcd.print("Try again");
          buzzer(2000);
          //delay(1000);
          a=1;
          key = '00';

        }
      }
      else
      {
        lcd.clear();lcd.setCursor(0,0);lcd.print("Monthly limit");
        buzzer(2000);
        //delay(1000);
      }
    }
    else if (key == '2')
    {
      if (rice2 > 0)
      {
        if (qty > rice2)
        {
          lcd.clear();lcd.setCursor(0,0);lcd.print("Limit exceed");
          lcd.setCursor(0,2);lcd.print("Try again");
          buzzer(2000);
          a=1;
          key = '00';

        }
      }
      else
      {
        lcd.clear();lcd.setCursor(0,0);lcd.print("Monthly limit");
        buzzer(2000);
      }
    }
    else if (key == '3')
    {
      if (rice3 > 0)
      {
        if (qty > rice3)
        {
          lcd.clear();lcd.setCursor(0,0);lcd.print("Limit exceed");
          lcd.setCursor(0,2);lcd.print("Try again");
          buzzer(2000);
          a=1;
          key = '00';

        }
      }
      else
      {
        lcd.clear();lcd.setCursor(0,0);lcd.print("Monthly limit");
        buzzer(2000);
      }
    }
    else if (key == '4')
    {
      if (kerosene > 0)
      {
        if (qty > kerosene)
        {
          lcd.clear();lcd.setCursor(0,0);lcd.print("Limit exceed");
          lcd.setCursor(0,2);lcd.print("Try again");
          buzzer(2000);
          a=1;
          key = '00';

        }
      }
      else
      {
        lcd.clear();lcd.setCursor(0,0);lcd.print("Monthly limit");
        buzzer(2000);
      }
    }
    scrn2break:;
  
}

void qtyproc(void)
{
    Serial.println(data_count);
    if (data_count==1)
    {
        qty = Quantity[0]-48;
        Serial.println(qty);
    }
    else if (data_count==2)
    {
        //Serial.println("T2");
        qty = ((Quantity[0]-48)*10)+(Quantity[1]-48);
        Serial.println(qty);
    }
    else if (data_count==3)
    {
        qty = ((Quantity[0]-48)*100)+((Quantity[1]-48)*10)+(Quantity[2]-48);
        Serial.println(qty);
    }
    else if (data_count==4)
    {
        qty = ((Quantity[0]-48)*1000)+((Quantity[1]-48)*100)+((Quantity[2]-48)*10)+(Quantity[3]-48);
        Serial.println(qty);
    }

}

void proc(void)
{
    wgt = qty*1;
    if (key == '1')
    {
        if (rice1 > 0)
        {
            rice1 = rice1 - qty;
            Serial.println(rice1);
            while (a==0)
            {
                weight = scale1.get_units();
                if ( weight >= (initwgt1-wgt))
                {
                  statusSensor = digitalRead (42);
                  if (statusSensor == 0)
                  {
                    digitalWrite(44, LOW);
                    lcd.clear();lcd.setCursor(0,0);lcd.print("Bag detected");
                    myservo1.write(100);
                    Serial.println(weight);
                    lcd.clear();lcd.setCursor(0,0);lcd.print("Weight : ");lcd.setCursor(10,0);lcd.print(wgt-(initwgt1-weight));
                  }
                  else{
                    lcd.clear();lcd.setCursor(0,0);lcd.print("Put your bag");
                    digitalWrite(44, HIGH);
                  }
                }
                else
                {
                  myservo1.write(150);
                  Serial.println("closed");
                  initwgt1 = (initwgt1-wgt);
                  if (user==1)
                  {
                    ru11 = ru11 + qty;
                  }
                  else if (user==2)
                  {
                    ru12 = ru12 + qty;
                  }
                  else if (user==3)
                  {
                    ru13 = ru13 + qty;
                  }
                  a=1;
                }
            }
        }
        else{
            a=1;
        }
    }   
    else if (key == '2')
    {
      if (rice2 > 0)
      {
        rice2 = rice2 - qty;
        Serial.println(rice2);
        while (a==0)
        {
          weight = scale2.get_units();
          if ( weight >= (initwgt2-wgt))
          {
            statusSensor = digitalRead (42);
            if (statusSensor == 0)
            {
              digitalWrite(44, LOW);
            lcd.clear();lcd.setCursor(0,0);lcd.print("Bag detected");
            myservo2.write(100);
            Serial.println(weight);
            lcd.clear();lcd.setCursor(0,0);lcd.print("Weight : ");lcd.setCursor(10,0);lcd.print(wgt-(initwgt2-weight));
            }
            else{
              lcd.clear();lcd.setCursor(0,0);lcd.print("Put your bag");
              digitalWrite(44, HIGH);
            }
          }
          else
          {
            myservo2.write(150);
            Serial.println("closed");
            initwgt2 = (initwgt2-wgt);
            if (user==1)
            {
              ru21 = ru21 + qty;
            }
            else if (user==2)
            {
              ru22 = ru22 + qty;
            }
            else if (user==3)
            {
              ru23 = ru23 + qty;
            }
            a=1;
          }
        }
      }
      else{
        a=1;
      }
    }   
    else if (key == '3')
    {
      if (rice3 > 0)
      {
        rice3 = rice3 - qty;
        Serial.println(rice3);
        while (a==0)
        {
          weight = scale3.get_units();
          if ( weight >= (initwgt3-wgt))
          {
            statusSensor = digitalRead (42);
            if (statusSensor == 0)
            {
              digitalWrite(44, LOW);
              lcd.clear();lcd.setCursor(0,0);lcd.print("Bag detected");
              myservo3.write(100);
              Serial.println(weight);
              lcd.clear();lcd.setCursor(0,0);lcd.print("Weight : ");lcd.setCursor(10,0);lcd.print(wgt-(initwgt3-weight));
            }
            else{
              lcd.clear();lcd.setCursor(0,0);lcd.print("Put your bag");
              digitalWrite(44, HIGH);
            }
          }
          else
          {
            myservo3.write(150);
            Serial.println("closed");
            initwgt3 = (initwgt3-wgt);
            if (user==1)
            {
              ru31 = ru31 + qty;
            }
            else if (user==2)
            {
              ru32 = ru32 + qty;
            }
            else if (user==3)
            {
              ru33 = ru33 + qty;
            }
            a=1;
          }
        }
      }
      else{
        a=1;
      }
    }
    else if (key == '4')
    {
      if (kerosene > 0)
      {
        kerosene = kerosene - qty;
        Serial.println(kerosene);
        while (a==0)
        {
          delay(50);
          flow = .00225 * pulse_freq;
          if (flow <= (qty/150))
          {
            digitalWrite(30,LOW);
            Serial.println(flow, DEC);
            lcd.clear();lcd.setCursor(0,0);lcd.print("Flow : ");lcd.setCursor(8,0);lcd.print(flow);
            delay(50);
          }
          else
          {
            digitalWrite(30,HIGH);
            delay(500);
            Serial.println("closed");
            if (user==1)
            {
              ku1 = ku1 + qty;
            }
            else if (user==2)
            {
              ku2 = ku2 + qty;
            }
            else if (user==3)
            {
              ku3 = ku3 + qty;
            }
            pulse_freq = 0;
            flow = 0;
            a=1;
          }
        }
      }
      else{
        a=1;
      }
    }
}

void setkey(void)
{
  if (key == '1')
  {
    keytemp = '1';
  }
  if (key == '2')
  {
    keytemp = '2';
  }
  if (key == '3')
  {
    keytemp = '3';
  }
  if (key == '4')
  {
    keytemp = '4';
  }
  if (key == '5')
  {
    keytemp = '5';
  }
  if (key == '6')
  {
    keytemp = '6';
  }
  if (key == '7')
  {
    keytemp = '7';
  }
  if (key == '8')
  {
    keytemp = '8';
  }
  if (key == '9')
  {
    keytemp = '9';
  }
  if (key == '0')
  {
    keytemp = '0';
  }
  if (key == '*')
  {
    keytemp = '*';
  }
  if (key == '#')
  {
    keytemp = '#';
  }

}

void namedec(void)
{
  if (user==1)
  {
    username = "User1";
    Master = "1234";
    cardtype = "APL";
    balance = 1000;
    rice1 = (10-ru11);
    rice2 = (15-ru21);
    rice3 = (20-ru31);
    kerosene = (1000-ku1);
  }
  else if (user==2)
  {
    username = "User2";
    Master = "5678";
    cardtype = "BPL";
    balance = 2000;
    rice1 = (20-ru12);
    rice2 = (25-ru22);
    rice3 = (30-ru32);
    kerosene = (1500-ku2);
  }
  else if (user==3)
  {
    username = "User3";
    Master = "1010";
    cardtype = "APL";
    balance = 500;
    rice1 = (10-ru13);
    rice2 = (25-ru23);
    rice3 = (15-ru33);
    kerosene = (500-ku3);
  }
}

void authentication(void)
{
  namedec();
  lcd.clear();lcd.setCursor(0,0);lcd.print("Enter your Passcode:");
  while (data_count <= Password_Lenght - 1)
  {
    passcode = keypad.getKey();
    if (passcode)
    {
      Data[data_count] = passcode;
      //lcd.setCursor(data_count, 1);
      lcd.print(Data[data_count]);
      data_count++;
    }
  }
  if (data_count == Password_Lenght)
  {
    if (String(Data) == Master)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Authorized access");
      delay(500);
      b =1;
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Access denied");
      digitalWrite(44, HIGH);
      delay(500);
      digitalWrite(44, LOW);
    }
  }
}
