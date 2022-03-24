void loop()
{
  // int registerIsPressed = digitalRead(registerButton);
  // int delistIsPressed = digitalRead(delistButton);

  Serial.println("State 1:" + digitalRead(registerButton));
  Serial.println("State 2:" + digitalRead(delistButton));

  if (digitalRead(registerButton) == LOW)
  {
    register_mode = HIGH;
    listen_mode = LOW;
  }
  else if (digitalRead(delistButton) == LOW)
  {
    delist_mode = HIGH;
    listen_mode = LOW;
  }

  buttonPressed_functions();

  if (listen_mode == HIGH)
  {
    showText_OLED("Listening Mode!");
    Serial.println("Listening Mode . . . ");
  }
}