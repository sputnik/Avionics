
void get_Time(void) {

  DateTime now = rtc.now();
  rtc_time[0] = now.second();
  rtc_time[1] = now.minute();
  rtc_time[2] = now.hour();
  rtc_time[3] = now.day();
  rtc_time[4] = now.month();
  rtc_time[5] = now.year();

}
