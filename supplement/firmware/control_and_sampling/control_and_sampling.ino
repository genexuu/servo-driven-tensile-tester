#include "HX711.h"

// CHANGE CALIBRATION CONDITIONS BASED ON BEST FIT LINE!!!
// For example, best fit equation is: y = mx + b.  (where x is raw sensor value, y is the value in grams
const double calibration_YIntercept = 0; // TODO: Need to define best fit y intercept
const double calibration_Slope = 1;  // TODO: Need to define best fit slope
//-----------------------------------------------------------------------------

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;

// Ultrasonic Range Sensor
const int ECHO_PIN = 2;
const int TRIG_PIN = 3;

HX711 scale;

void setup() {

  //Define BAUD rate
  Serial.begin(9600);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an INPUT

  //Display results in CSV data standard (comma deliminator)
  Serial.println("Raw Average, Load (in g), Distance (in cm)");
}

void loop() {
  
  // ------------------------ Get Distance -------------------
  double sum = 0.0;
  double samples[11];

  //Poll sensor 20 times, with 20ms delay between samples
  for(int i=0;i<11;i++){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
      
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
      
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHO_PIN, HIGH);
      
    // Calculating the distance
    double distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    samples[i] = distance;
      
    delay(20);
  }

  //Take the median of the range samples 
  sort(samples, 11);
  double medianDist = samples[5];

  //Read load cell 20 times and take average (can change this to median) 
  double avg = scale.read_average(10);

  //y = mx + b (where y is the value in grams and x is the raw value) 
  double grams = (calibration_Slope)*avg + calibration_YIntercept;

  Serial.print(avg);
  Serial.print(",");
  Serial.print(grams);
  Serial.print(",");
  Serial.println(medianDist);
  
  scale.power_down();             // put the ADC in sleep mode
  delay(50);
  scale.power_up();
}


//Sorts an array of doubles
void sort(double a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}
