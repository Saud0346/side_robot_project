int pin1 = 3, pin2 = 5, pin3 = 6, pin4 = 9;

int trig1 = 4, trig2 = 7, trig3 = 8;
int echo1 = 10, echo2 = 11, echo3 = 12;

int distance1, duration1;
int distance2, duration2;
int distance3, duration3;
int ONOFF =A0;
int car_speed = 0;
char read_data;

int ir_S1 = 2, ir_S2 = 13;

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

    pinMode(A0,INPUT);

    Serial.begin(9600);
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
            car_speed = 255;
        switch (read_data)
        {
        case 'F':
        {

            // Forward
            analogWrite(pin1, car_speed);
            analogWrite(pin2, LOW);
            analogWrite(pin3, car_speed);
            analogWrite(pin4, LOW);
            break;
        }

        case 'B':
        {
            analogWrite(pin1, LOW);
            analogWrite(pin2, car_speed);
            analogWrite(pin3, LOW);
            analogWrite(pin4, car_speed);
            break;
        }
        case 'L':
        {
            analogWrite(pin1, car_speed);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, car_speed);

            break;
        }

        case 'R':
        {
            analogWrite(pin1, LOW);
            analogWrite(pin2, car_speed);
            analogWrite(pin3, car_speed);
            analogWrite(pin4, LOW);

            break;
        }

        case 'G':
        {
            analogWrite(pin1, car_speed);
            analogWrite(pin2, LOW);
            analogWrite(pin3, 100);
            analogWrite(pin4, LOW);

            break;
        }

        case 'I':
        {
            analogWrite(pin1, 100);
            analogWrite(pin2, LOW);
            analogWrite(pin3, car_speed);
            analogWrite(pin4, LOW);

            break;
        }

        case 'H':
        {

            analogWrite(pin1, LOW);
            analogWrite(pin2, car_speed);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 100);
            break;
        }

        case 'J':
        {
            analogWrite(pin1, LOW);
            analogWrite(pin2, 100);
            analogWrite(pin3, LOW);
            analogWrite(pin4, car_speed);

            break;
        }

        default:
        {
            analogWrite(pin1, LOW);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, LOW);

        }
        }
    }

    if(!digitalRead(ONOFF))
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

        if (distance2 > 10)
        {
            // Forward
            analogWrite(pin1, 100);
            analogWrite(pin2, LOW);
            analogWrite(pin3, 100);
            analogWrite(pin4, LOW);
        }

        else if (distance1 > 8 && distance1>distance3)
        {
            // right turn
            analogWrite(pin1, LOW);
            analogWrite(pin2, 200);
            analogWrite(pin3, 200);
            analogWrite(pin4, LOW);
            delay(550);
        }

        else if (distance3 > 8)
        {
            // left turn
            analogWrite(pin1, 200);
            analogWrite(pin2, LOW);
            analogWrite(pin3, LOW);
            analogWrite(pin4, 200);
            delay(550);
        }

        else
        {
            while (distance1 < 8 || distance3 < 8)
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
                analogWrite(pin2, 100);
                analogWrite(pin3, LOW);
                analogWrite(pin4, 100);
                delay(500);
            }

            if (distance1 >= 8)
            {
                // right turn
                analogWrite(pin1, LOW);
                analogWrite(pin2, 200);
                analogWrite(pin3, 200);
                analogWrite(pin4, LOW);
                delay(550);
            }

            else if (distance3 >= 8)
            {
                // left turn
                analogWrite(pin1, 200);
                analogWrite(pin2, LOW);
                analogWrite(pin3, LOW);
                analogWrite(pin4, 200);
                delay(550);
            }
        }

        if (!digitalRead(ir_S1))
        {

            digitalWrite(pin1, HIGH);
            digitalWrite(pin2, LOW);
            digitalWrite(pin3, LOW);
            digitalWrite(pin4, HIGH);
            delay(100);
            digitalWrite(pin1, LOW);
            digitalWrite(pin2, LOW);
        }

        if (!digitalRead(ir_S2))
        {

            digitalWrite(pin1, LOW);
            digitalWrite(pin2, HIGH);
            digitalWrite(pin3, HIGH);
            digitalWrite(pin4, LOW);
            delay(100);
            digitalWrite(pin1, LOW);
            digitalWrite(pin2, LOW);
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
}
