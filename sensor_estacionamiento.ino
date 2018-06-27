//Robot IMA sensor de estacionamiento
//Sensor ultrasonido + buzzer

//Pines del sensor de ultrasonido y la alarma
#define echo A2
#define trigger 2
#define buzzer 13

//Variables necesarias para medir la distancia
float distancia;
float tiempo;

// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 40.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;

// Establecemos los pines de entrada y salida del sensor de ultrasonido 
void setup() {
  Serial.begin(9600);     
  pinMode(trigger, OUTPUT); /*activación del pin 2 como salida: para el trigger*/
  pinMode(echo, INPUT); /*activación del pin A0 como entrada: tiempo del rebote del ultrasonido*/
  pinMode (buzzer, OUTPUT); /*activación del pin 13 como salida para la alarma*/
}
 
void loop() {
  /*inicia la secuencia del Trigger para comenzar a medir*/
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH); /* Envío del pulso ultrasónico*/
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  tiempo = pulseIn(echo, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
                               del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin A2 empieza a recibir el rebote, HIGH,
                               hasta que deja de hacerlo, LOW, la longitud del pulso entrante*/
   
  distancia = int(tiempo * 0.000001 * sonido / 2.0); /*Fórmula para calcular la distancia.
                                  Lo dividimos entre 2 por que solo nos interesa la distancia de ida.*/
   
  /*Monitorización en centímetros por el monitor serial*/
  Serial.print("\nDistancia ");
  Serial.print(distancia);
  Serial.print(" cm");
  Serial.println();
  delay(500);
   
  if (distancia < umbral1 && distancia >= umbral2)
  {
    // Encendemos alarma
    tone(buzzer, 2000, 200);
    delay(500);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    tone(buzzer, 2000, 200);
    delay(250);
  }
  else if (distancia <= umbral3)
  {
    tone(buzzer, 2000, 200);
    delay(100);
  }
}
