// inputs , AvgHeight, AvgVelocity,

void check_airbrakes() {  
    //#error "Need AvgHeight and AvgVelocity passed in. It shouldnt need them as inputs because they are global variables"
  double x = AvgHeight;
  //VelocityPlot = (-.000000000000019026*x*x*x*x*x) + (.00000000015991*x*x*x*x) - (.00000051648*x*x*x) + (.00079253*x*x) - (.65636 * x) + (478.29);
  VelocityPlot = 40 - 8*x; // Modified plot for testing in elevator
  
  if (AvgVelocity >= VelocityPlot) {
    AirbrakeStatus = true;
    digitalWrite(LA_DIR, HIGH);
    digitalWrite(LA_PWM, HIGH);
    //printf("airbrakes opening\n");
  }
  else if (AvgVelocity < VelocityPlot) {
    AirbrakeStatus = false;
    digitalWrite(LA_DIR, LOW);
    digitalWrite(LA_PWM, HIGH);
  }
  Serial.print("Airbrakes opening:, ");
  Serial.println(AirbrakeStatus);
  AirbrakeValue = analogRead(LA_FDBK);
  if (AirbrakeStatus == true) {
    if (LAfdbk >= 500) {
      digitalWrite(LA_DIR, HIGH);
      LAdir = 1;
      digitalWrite(LA_PWM, LOW);
      LApwm = 0;
      //PercentOpen = 100;
    }
    else if (LAfdbk < 500) {
      digitalWrite(LA_DIR, HIGH);
      LAdir = 1;
      digitalWrite(LA_PWM, HIGH);
      LApwm = 1;
      //PercentOpen = CurrentActuationPeriod * 45.4545454545;
      //CurrentActuationPeriod = CurrentActuationPeriod + TIME_DELTA;
    }
  }
  else if (AirbrakeStatus == false) {
    if (LAfdbk <= 208) {
      digitalWrite(LA_DIR, LOW);
      LAdir = 0;
      digitalWrite(LA_PWM, LOW);
      LApwm = 0;
      PercentOpen = 0;
    }
    else if (LAfdbk > 208) {
      digitalWrite(LA_DIR, LOW);
      LAdir = 0;
      digitalWrite(LA_PWM, HIGH);
      LApwm = 1;
      //TODO: Switch percent open statements and make sure function is correct
      //PercentOpen = (analogRead(LA_FDBK) * FUNCTION) + B;
      //TODO: What is currentactuationperiod. isn't this just a simulated number?
      PercentOpen = CurrentActuationPeriod * 45.4545454545;
      if(PercentOpen > 95) {
        if(AirbrakeStatus == true) {
          //digitalWrite(LA_PWM, LOW);
        }
        else {  //airbrake status == false
          //TODO: figure out what we should do with this case
        }
      }
      else if (PercentOpen == 0) {
        if(AirbrakeStatus == true) {
          //TODO: figure out what we should do with this case
        }
        else {  //airbrake status == false
          //digitalWrite(LA_PWM, LOW);
        }
      }
      CurrentActuationPeriod = CurrentActuationPeriod - TIME_DELTA;
    }
    LAfdbk = analogRead(LA_FDBK);
  }
}
