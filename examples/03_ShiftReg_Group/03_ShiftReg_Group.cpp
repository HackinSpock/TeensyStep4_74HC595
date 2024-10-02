#include "Arduino.h"
#include "teensystep4.h"
#include <Shifty.h>
extern "C" uint32_t set_arm_clock(uint32_t frequency);

using namespace TS4;

//declare shift register
Shifty shift;

Stepper s1(&shift, 1, 2);
Stepper s3(&shift, 13, 14);
Stepper s2(&shift, 11, 12);
Stepper s4(&shift, 3, 4);


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    // Set the number of bits you have (multiples of 8)
    shift.setBitCount(16);

  // Set the clock, data, and latch pins you are using
  // This also sets the pinMode for these pins
    shift.setPins(11, 12, 8); 
    set_arm_clock(24000000);//set it to 24 Mhz

    TS4::begin();
    
    s1
        // .setMaxSpeed(10'000)
        // .setAcceleration(50'000);
        .setMaxSpeed(1'000)
        .setAcceleration(5'000);

    s2
        // .setMaxSpeed(8'000)
        // .setAcceleration(25'000);
        .setMaxSpeed(5'000)
        .setAcceleration(5'000);
    s3
        // .setMaxSpeed(10'000)
        // .setAcceleration(50'000);
        .setMaxSpeed(1'000)
        .setAcceleration(5'000);

    s4
        // .setMaxSpeed(8'000)
        // .setAcceleration(25'000);
        .setMaxSpeed(3'000)
        .setAcceleration(1'000);
    // move two steppers simultaneously (not synchronized)
    s1.moveAbsAsync(1000);
    s2.moveAbsAsync(4000);
    s3.moveAbsAsync(8000);
    s4.moveAbsAsync(2000);

    // wait until both steppers are done
    while (s1.isMoving || s2.isMoving || s3.isMoving || s4.isMoving)
    {
        delay(10);
    }
    delay(100);

    // define and move a groups of steppers synchronized
    //StepperGroup g1{s1, s2, s3, s4};
    StepperGroup g1{s1, s2, s3, s4};

    s1.setTargetAbs(-1000);
    s2.setTargetAbs(-3000);
    s3.setTargetAbs(-6000);
    s4.setTargetAbs(-3000);
    g1.move();
    delay(100);

    s1.setTargetAbs(0);
    //s3.setTargetAbs(0);
    //StepperGroup({s1, s2, s3, s4}).move();
    StepperGroup({s1, s2, s3, s4}).move();
}

void loop()
{
    digitalToggleFast(LED_BUILTIN);
    delay(200);
}