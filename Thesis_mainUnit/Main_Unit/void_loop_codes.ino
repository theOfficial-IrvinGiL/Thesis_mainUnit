void loop()
{

    char keyValue = customKeypad.getKey();

    if (keyValue)
    {
        switch (keyValue)
        {
        case 'A':
            requestAccess_mode = true;
            idle_mode = false;
            showAdmin_menu = false;

            keyValue = 0x00;
            showInputPasscodeMessage();
            break;
        default:
            break;
        }
    }
    /**
    * if key A is pressed during idle then request
    access is returned as true
    */
    else if (requestAccess_mode == true)
    {
        getAdmin_input();
    }
    /**
     * code function for displaying admin options
     */
    else if (showAdmin_menu == true)
    {
        if (keyValue)
        {
            switch (keyValue)
            {
            case 'A':
                bool idle_mode = false;
                bool requestAccess_mode = false;
                bool showAdmin_menu = false;
                //----
                bool registerUser_mode = true; // enter register new user mode
                bool delistUser_mode = false;
                bool viewUser_mode = false;
                break;
            case 'B':
                break;
            case 'C':
                break;
            case 'D':
                showMainUnit();
                break;
            default:
                break;
            }
        }
    }
    /**
    * if register new user options is picked
    */
    else if (registerUser_mode == true)
    {

    }
    /**part of code where the main unit is receiving data from the
     * meter unit
     */
    else if (idle_mode == true)
    {
    }
}
