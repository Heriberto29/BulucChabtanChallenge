#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, A0, 10, A1, 13);

boolean Actual = false;
boolean final = false;
String num1, num2;
float total;
int movimiento;
char op;
char op2;
boolean funcionActiva;

const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando

char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {5, 4, 3, 2}; //Seleccionamos los pines en el arduino donde iran conectadas las filas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  char key = customKeypad.getKey();
  if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')) {
    if (Actual != true) {
      total = 0;
      lcd.clear();
      num1 = num1 + key;//concatenando
      int numLength = num1.length();//calcula el tamaño de la cadena
      movimiento = numLength;//se usara para saber en que posicion imprimir
      lcd.setCursor(0, 0);
      lcd.print(num1);
      Actual = false;
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(movimiento, 0);
      lcd.print(num2);
      final = true;
    }
  } else if (key != NO_KEY && (key == '+' || key == '-' || key == '*' || key == '/')) {
    if (total != 0 && funcionActiva != true) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(total);
      op = key;
      op2 = key;
      lcd.print(op);
      Actual = true;
      num1 = String(total);
      movimiento = num1.length() + 1;
      num2 = "";
      funcionActiva = true;
    } else if (funcionActiva != true) {
      op = key;
      op2 = key;
      lcd.print(op);
      movimiento += 1;
      Actual = true;
      funcionActiva = true;
    } else {
      op = key;
      lcd.clear();
      lcd.setCursor(0, 0);
      if (op2 == '+') {
        total = num1.toFloat() + num2.toFloat();
      } else if (op2 == '-') {
        total = num1.toFloat() - num2.toFloat();
      } else if (op2 == '*') {
        total = num1.toFloat() * num2.toFloat();
      } else if (op2 == '/') {
        total = num1.toFloat() / num2.toFloat();
      }
      op2 = key;
      lcd.setCursor(0, 0);
      lcd.print(total);
      lcd.print(op);
      Actual = true;
      num1 = String(total);
      movimiento = num1.length() + 1;
      num2 = "";
      funcionActiva = true;
    }

  } else if (key != NO_KEY && key == '=') {
    if (op == '+' && num1 != "" && num2 != "") {
      total = num1.toFloat() + num2.toFloat();
    } else if (op == '-' && num1 != "" && num2 != "") {
      total = num1.toFloat() - num2.toFloat();
    } else if (op == '*' && num1 != "" && num2 != "") {
      total = num1.toFloat() * num2.toFloat();
    } else if (op == '/' && num1 != "" && num2 != "") {
      total = num1.toFloat() / num2.toFloat();
    }
    if (num1 != "" && num2 != "") {
      lcd.setCursor(0, 1);
      lcd.print(total);
      Actual = false;
      num1 = "";
      num2 = "";
      funcionActiva = false;
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(total);
    }

  } else if (key != NO_KEY && key == 'C') {
    num1 = "";
    num2 = "";
    total = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
  }

}
