#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int pin1 = 3, pin2 = 5, pin3 = 6, pin4 = 9;

int trig1 = 4, trig2 = 7, trig3 = 8;
int echo1 = 10, echo2 = 11, echo3 = 12;

double distance1, duration1;
double distance2, duration2;
double distance3, duration3;

int car_speed = 0, car_speed2;
char read_data;

int set_distance1, set_distance2, set_distance3;

int ir_S1 = 2, ir_S2 = 13;
int ir_S3 = 14, ir_S4 = 15, ir_S5 = 16, ir_S6 = 17, ir_S7 = 18;
int skip_code = 0;
int clear_lcd = 0;
int clear_screen = 0;
int self_driving();
int bluetooth_controle();
int maze_drive();
void setup()
{
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(trig3, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    pinMode(echo3, INPUT);

    pinMode(ir_S1, INPUT);
    pinMode(ir_S2, INPUT);

    pinMode(ir_S3, INPUT);
    pinMode(ir_S4, INPUT);
    pinMode(ir_S5, INPUT);
    pinMode(ir_S6, INPUT);
    pinMode(ir_S7, INPUT);

    // pinMode(A0, INPUT);
    // pinMode(A1, INPUT);
    // pinMode(A2, INPUT);
    // pinMode(A3, INPUT);
    // pinMode(A4, INPUT);
    // pinMode(A5, INPUT);

    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.clear();

    lcd.print("Hi I'am a robot");
    lcd.setCursor(0, 1);
    lcd.print(" Made by Saud");
    delay(3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Connect to ");
    lcd.setCursor(0, 1);
    lcd.print("Mobile phone");

    skip_code = 0;
    clear_lcd = 0;
}

void loop()
{
    distance1 = 0;
    distance2 = 0;
    distance3 = 0;

    if (Serial.available() > 0)
    {
        read_data = Serial.read();

        

        if (read_data == 'W')
            skip_code++;
        else if (read_data == 'U')
            lcd.clear();

        switch (skip_code)
        {
        case 0:
        {

            speed_controle();
            if (clear_lcd == 0)
            {
                lcd.clear();
                clear_lcd++;
            }
            break;
        }

        case 1:
        {

            sensor_distance();
            if (clear_lcd == 1)
            {
                lcd.clear();
                clear_lcd++;
            }
            break;
        }

        case 2:
        {

           // line_following1();
            if (clear_lcd == 2)
            {
                lcd.clear();
                clear_lcd++;
            }
            break;
        }

        case 3:
        {

            //line_following2();
            if (clear_lcd == 3)
            {
                lcd.clear();
                clear_lcd++;
            }

            break;
        }

        case 4:
        {

            self_driving();
            if (clear_lcd == 4)
            {
                lcd.clear();
                clear_lcd++;
            }

            break;
        }

        case 5:
        {

            bluetooth_controle();

            if (clear_lcd == 5)
            {
                lcd.clear();
                clear_lcd++;
            }

            break;
        }

        case 6:
        {
            skip_code = 0;
            clear_lcd = 0;
            break;
        }
        }
    }
}
int sensor_distance()
{

    if (read_data == 'F')
        set_distance2++;
    else if (read_data == 'B')
    {
        set_distance1++;
        set_distance3++;
    }
    else if (read_data == 'R')
        set_distance2--;
    else if (read_data == 'L')
    {
        set_distance1--;
        set_distance3--;
    }

    lcd.setCursor(0, 0);
    lcd.print("D1   D2   D3 cm");
    lcd.setCursor(0, 1);
    lcd.print(set_distance1);
    lcd.print("    ");
    lcd.print(set_distance2);
    lcd.print("   ");
    lcd.print(set_distance3);
}
int speed_controle()
{

    if (read_data == 'F')
        car_speed2++;
    else if (read_data == 'B')
        car_speed2--;

    if (read_data == 'W')
    {
        skip_code++;
        read_data = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("Car Speed");
    lcd.setCursor(0, 1);
    lcd.print(car_speed2);
}
int bluetooth_controle()
{

    lcd.setCursor(0, 0);
    lcd.print("Bluetooth ");
    lcd.setCursor(0, 1);
    lcd.print("    Controle");

    switch (read_data)
    {
    case '9':
    {
        car_speed = 255;
        break;
    }

    case '8':
    {
        car_speed = 227;
        break;
    }

    case '7':
    {
        car_speed = 199;
        break;
    }

    case '6':
    {
        car_speed = 171;
        break;
    }

    case '5':
    {
        car_speed = 148;
        break;
    }

    case '4':
    {
        car_speed = 115;
        break;
    }

    case '3':
    {
        car_speed = 100;
        break;
    }

    case '2':
    {
        car_speed = 80;
        break;
    }

    case '1':
    {
        car_speed = 80;
        break;
    }
    case '0':
    {
        car_speed = 0;
        break;
    }
    }

    if (read_data == 'F')
    {

        // Forward
        analogWrite(pin1, car_speed);
        analogWrite(pin2, LOW);
        analogWrite(pin3, car_speed);
        analogWrite(pin4, LOW);
    }

    else if (read_data == 'B')
    {
        analogWrite(pin1, LOW);
        analogWrite(pin2, car_speed);
        analogWrite(pin3, LOW);
        analogWrite(pin4, car_speed);
    }
    else if (read_data == 'L')
    {

        // Turn left
        analogWrite(pin1, LOW);
        analogWrite(pin2, car_speed);
        analogWrite(pin3, car_speed);
        analogWrite(pin4, LOW);
    }

    else if (read_data == 'R')
    {
        // Right
        analogWrite(pin1, car_speed);
        analogWrite(pin2, LOW);
        analogWrite(pin3, LOW);
        analogWrite(pin4, car_speed);
    }

    else if (read_data == 'G')
    {
        // forward left
        analogWrite(pin1,(car_speed/4));
        analogWrite(pin2, LOW);
        analogWrite(pin3, car_speed);
        analogWrite(pin4, LOW);
    }

    else if (read_data == 'I')
    {
        // Forward right
        analogWrite(pin1, car_speed);
        analogWrite(pin2, LOW);
        analogWrite(pin3, (car_speed/4));
        analogWrite(pin4, LOW);
    }

    else if (read_data == 'H')
    {
        // Backward left
        analogWrite(pin1, LOW);
        analogWrite(pin2, (car_speed/4));
        analogWrite(pin3, LOW);
        analogWrite(pin4, car_speed);
    }

    else if (read_data == 'J')
    {
        // backward right
        analogWrite(pin1, LOW);
        analogWrite(pin2, car_speed);
        analogWrite(pin3, LOW);
        analogWrite(pin4, (car_speed/4));
    }

    else
    {
        analogWrite(pin1, LOW);
        analogWrite(pin2, LOW);
        analogWrite(pin3, LOW);
        analogWrite(pin4, LOW);
    }

    
}
int self_driving()
{

    lcd.setCursor(0, 0);
    lcd.print("Obstacles");
    lcd.setCursor(0, 1);
    lcd.print("     Avoiding");

    // distance1
    //*******************************
    digitalWrite(trig1, LOW);
    delayMicroseconds(2);

    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);

    duration1 = pulseIn(echo1, HIGH);
    distance1 = (duration1 * 0.034) / 2;
    //*******************************

    // distance2
    //*******************************
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);

    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);

    duration2 = pulseIn(echo2, HIGH);
    distance2 = (duration2 * 0.034) / 2;
    //******************************

    // distance3
    //*******************************
    digitalWrite(trig3, LOW);
    delayMicroseconds(2);

    digitalWrite(trig3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3, LOW);

    duration3 = pulseIn(echo3, HIGH);
    distance3 = (duration3 * 0.034) / 2;
    //*******************************

    if (distance2 > set_distance2)
    {
        // Forward
        analogWrite(pin1, car_speed2);
        analogWrite(pin2, LOW);
        analogWrite(pin3, car_speed2);
        analogWrite(pin4, LOW);
    }

    else if (distance1 > set_distance1 && distance1 > distance3)
    {
        // right turn
        analogWrite(pin1, 200);
        analogWrite(pin2, LOW);
        analogWrite(pin3, LOW);
        analogWrite(pin4, 200);
        delay(250);
    }

    else if (distance3 > set_distance3)
    {
        // left turn
        analogWrite(pin1, LOW);
        analogWrite(pin2, 200);
        analogWrite(pin3, 200);
        analogWrite(pin4, LOW);
        delay(250);
    }

    else if (distance1 < set_distance1 && distance2 < set_distance2 && distance3 < set_distance3)
    {
        while (distance1 < set_distance1 || distance3 < set_distance3)
        {

            // distance1
            //*******************************
            digitalWrite(trig1, LOW);
            delayMicroseconds(2);

            digitalWrite(trig1, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig1, LOW);

            duration1 = pulseIn(echo1, HIGH);
            distance1 = (duration1 * 0.034) / 2;
            //*******************************

            // distance3
            //*******************************
            digitalWrite(trig3, LOW);
            delayMicroseconds(2);

            digitalWrite(trig3, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig3, LOW);

            duration3 = pulseIn(echo3, HIGH);
            distance3 = (duration3 * 0.034) / 2;
            //*******************************

            // Backward
            analogWrite(pin1, LOW);
            analogWrite(pin2, car_speed2);
            analogWrite(pin3, LOW);
            analogWrite(pin4, car_speed2);
        }

        if (distance1 > set_distance1 && distance1 > distance3)
        {
            // right turn
            analogWrite(pin1, 200);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 200);
            delay(250);
        }

        else if (distance3 > set_distance3)
        {
            // left turn
            analogWrite(pin1, LOW);
            analogWrite(pin2, 200);
            analogWrite(pin3, 200);
            analogWrite(pin4, LOW);
            delay(250);
        }
    }

    if (!digitalRead(ir_S1))
    {

        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
    }

    else if (!digitalRead(ir_S2))
    {

        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
    }

    /*

      Serial.print("D1 ");
      Serial.println(distance1);
      delay(1000);
      Serial.print("D2 ");
      Serial.println(distance2);
      delay(1000);
      Serial.print("D3 ");
      Serial.println(distance3);
      delay(1000);
      */
}

int line_following1()
{
    lcd.setCursor(0, 0);
    lcd.print("Line");
    lcd.setCursor(0, 1);
    lcd.print("  Following(1)");

    
        if (!digitalRead(ir_S4) && digitalRead(ir_S5) && !digitalRead(ir_S6))
        {
            // forward
            analogWrite(pin1, car_speed2);
            analogWrite(pin2, LOW);
            analogWrite(pin3, car_speed2);
            analogWrite(pin4, LOW);
        }

         if (digitalRead(ir_S4) && digitalRead(ir_S5) && !digitalRead(ir_S6))
        {
            // left turn
            analogWrite(pin1, LOW);
            analogWrite(pin2, 200);
            analogWrite(pin3, 200);
            analogWrite(pin4, LOW);
        }

         if (!digitalRead(ir_S4) && digitalRead(ir_S5) && digitalRead(ir_S6))
        {
            // Right turn
            analogWrite(pin1, 200);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 200);
        }

       
}


int line_following2()
{
    lcd.setCursor(0, 0);
    lcd.print("Line");
    lcd.setCursor(0, 1);
    lcd.print("  Following(2)");

    
        if (!digitalRead(ir_S3) && !digitalRead(ir_S7))
        {
            // forward
            analogWrite(pin1, car_speed2);
            analogWrite(pin2, LOW);
            analogWrite(pin3, car_speed2);
            analogWrite(pin4, LOW);
        }

        if (!digitalRead(ir_S3) && digitalRead(ir_S7))
        {
            // Right turn
            analogWrite(pin1, 200);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 200);
        }

           if (digitalRead(ir_S3) && !digitalRead(ir_S7))
        {
            // Turn left
            analogWrite(pin1, LOW);
            analogWrite(pin2, 200);
            analogWrite(pin3, 200);
            analogWrite(pin4, LOW);
        }

        


      if (digitalRead(ir_S4) && digitalRead(ir_S5) && digitalRead(ir_S6))
        {
            // Turn right
            analogWrite(pin1, 200);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 200);
        }
}
