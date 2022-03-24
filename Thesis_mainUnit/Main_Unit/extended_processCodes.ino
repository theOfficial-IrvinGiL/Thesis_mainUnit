// write new codes here
void buttonPressed_functions()
{
    if (register_mode == HIGH)
    {
        Serial.println("register mode...");
        while (Serial.available() == 0)
        {
            showText_OLED("Register: Waiting for Serial Data...");
        }
        process_message();
        int empty_address = findEmpty_address();
        String concat_message = processed_message[0];
        concat_message += processed_message[1];

        Serial.flush();

        if (processed_message[0] == "")
        {
            Serial.println("Error: Serial message unreadable!");
            showText_OLED("Error: Serial message unreadable!");
        }
        else
        {
            update_eeprom(concat_message);
            showText_OLED("Data Registered Successfully!");
        }
        empty_serialMessages();
        register_mode = LOW;
        listen_mode = HIGH;
    }
    else if (delist_mode == HIGH)
    {
        Serial.println("delist mode...");
        while (Serial.available() == 0)
        {
            showText_OLED("Delist: Waiting for Serial Data...");
        }

        process_message();

        Serial.flush();

        if (processed_message[0] == "")
        {
            Serial.println("Error: Serial message unreadable!");
            showText_OLED("Error: Serial message unreadable!");
        }
        else
        {
            extract_delist();
            showText_OLED("Data Delisted Successfully!");
        }
        empty_serialMessages();
        delist_mode = LOW;
        listen_mode = HIGH;
    }
}