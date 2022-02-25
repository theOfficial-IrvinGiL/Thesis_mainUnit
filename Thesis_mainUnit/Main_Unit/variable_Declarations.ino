// variable declarations are here: ⋙⋙

char admin_input[8];
unsigned short admin_fixedNumberInput = 0;

unsigned short set_CursorCollumn = 0;

char contact_input[11];
char generated_passcode[4];

unsigned int address_OnEEPROM = 0;
short fixed_numberOfInputs = 0;
char code_fromEEPROM[4];

String predefined_adminPasscode[] = {
    "77351071", "27326699", "82736918", "61835240"
};

//declaration for modes
boolean idle_mode = true;
boolean requestAccess_mode = false;
