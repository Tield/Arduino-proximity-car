int izqA = 5; // define el pin 5 como salida para  el puente H
int izqB = 6; // define el pin 6 como  salida para el puente H
int derA = 9; // define el pin 9 como salida para el puente H
int derB = 10; // define el pin 10 como salida para el puente H
int vel = 255; // Velocidad de los motores (0-255)
int estado = 'g';         // inicia detenido

int pecho = 2;            // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = 3;            // define el pin 3 como (ptrig) para el Ultrasonido
int duracion, distancia;  // para Calcular distacia

void setup()  {
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
   pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(pecho, INPUT);   // define el pin 2 como entrada (pecho)
  pinMode(ptrig,OUTPUT);   // define el pin 3 como salida  (ptrig)
  pinMode(12, OUTPUT);
}

void loop()  {

  digitalWrite(12, HIGH);

  if(Serial.available()>0){        // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
 if (estado =='A'){          // Boton ON,  se mueve sensando distancia (BOTON HACIA ADELANTE)

     digitalWrite(ptrig, HIGH);   // genera el pulso de trigger por 10us
     delay(0.01);
     digitalWrite(ptrig, LOW);

     duracion = pulseIn(pecho, HIGH);              // Lee el tiempo del Echo
     distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
     delay(10);

     if (distancia <= 20 && distancia >=2){    // si la distancia es menor de 15cm
        digitalWrite(13,HIGH);                 // Enciende LED

        analogWrite(derB, 0);                  // Parar los motores por 200 mili segundos
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
     }
     else{                   // Si no hay obstaculos se desplaza al frente
         analogWrite(derB, 0);
         analogWrite(izqB, 0);
         analogWrite(derA, vel);
         analogWrite(izqA, vel);
     }
  }
  if(estado=='B'){          // Boton IZQ (BOTON IZQUIERDO)
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, vel);
  }
  if(estado=='a'){         // Boton Parar  (SE ENCIENDE CUANDO DESACTIVA LOS BOTONES)
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
  }
  if(estado=='D'){          // Boton DER ( EL BOTON DERECHO)
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(izqA, 0);
    analogWrite(derA, vel);
  }

  if(estado=='E'){          // Boton Reversa ( BOTON DE REVERSA)
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    analogWrite(derB, vel);
    analogWrite(izqB, vel);
  }
   if(estado=='F'){          // Boton FRENTE (NO HACE NADA)
    analogWrite(derB, vel);
    analogWrite(izqB, vel);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
   }

  if (estado =='f'){          // Boton ON,  se mueve sensando distancia (BOTON DE ENCENDIDO ENCIENDE LED, ENTRA EN MODO AUTOMATICO)

     digitalWrite(ptrig, HIGH);   // genera el pulso de trigger por 10us
     delay(0.01);
     digitalWrite(ptrig, LOW);

     duracion = pulseIn(pecho, HIGH);              // Lee el tiempo del Echo
     distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
     delay(10);

     if (distancia <= 20 && distancia >=2){    // si la distancia es menor de 15cm
        digitalWrite(13,HIGH);                 // Enciende LED

        analogWrite(derB, 0);                  // Parar los motores por 200 mili segundos
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
        delay (200);

        analogWrite(derB, vel);               // Reversa durante 500 mili segundos
        analogWrite(izqB, vel);
        delay(250);

        analogWrite(derB, 0);                // Girar durante 1100 milisegundos
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, vel);
        delay(500);

        analogWrite(derB, 0);                  // Parar los motores por 500 mili segundos
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
        delay (500);

     }
     else{                   // Si no hay obstaculos se desplaza al frente
         analogWrite(derB, 0);
         analogWrite(izqB, 0);
         analogWrite(derA, vel);
         analogWrite(izqA, vel);
     }
  }
  if(estado=='g'){          // Boton OFF, detiene los motores no hace nada (BOTON DE APAGADO APAGA EL LED, ENTRA EN MODO MANUAL)
     analogWrite(derB, 0);
     analogWrite(izqB, 0);
     analogWrite(derA, 0);
     analogWrite(izqA, 0);
  }
}
