#define DATA_PIN_1
#define DATA_PIN_2
#define DATA_PIN_3
#define DATA_PIN_4
#define DATA_PIN_5
#define DATA_PIN_6
#define DATA_PIN_7
#define DATA_PIN_8
#define DATA_IN_READY_PIN 10
#define DATA_OUT_READY_PIN 16

#include "Keyboard.h"


enum states {
  idle,
  rx,
  tx
};
states state = idle;
char keys[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
const int DATA_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};
String command;

void setup() {
  //  1.5 seconds to allow for programming
  delay(1500);

  //  data ready pins
  pinMode(DATA_IN_READY_PIN, INPUT);
  pinMode(DATA_OUT_READY_PIN, OUTPUT);

  //  setup keyboard
  Keyboard.begin();
  for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
    Keyboard.press(keys[i]);
    Keyboard.release(keys[i]);
  }

}

void loop() {
  handle_pins();
}

void handle_pins() {
  if (digitalRead(DATA_IN_READY_PIN) == HIGH) {
    if (digitalRead(DATA_OUT_READY_PIN) == HIGH) {
      // receive ack
      if (state == tx) {
        digitalWrite(DATA_OUT_READY_PIN, LOW);
      }
      // otherwise we are receiving data and acking waiting for DATA_IN_READY_PIN to go low
    } else {
      // set state to rx
      state = rx;
      // read data in
      command += read_data_pins();
      // ack
      digitalWrite(DATA_OUT_READY_PIN, LOW);
      // execute any complete commands
      parse_command();
    }
  } else {
    if (digitalRead(DATA_OUT_READY_PIN) == HIGH) {
      if (state == rx || state == idle) {
        digitalWrite(DATA_OUT_READY_PIN, LOW);
        state = idle;
      } else {
        // we are transmitting but no ack yet
        // check timer for timeout?
      }
    } else {
      // idle
      state = idle;
    }
  }

}

void parse_command() {

  //  look for complete commands
  int semicolon_index = command.indexOf(';');
  if (semicolon_index == -1) {
    return;
  } else {
    run_command(command.substring(0, semicolon_index));
    command = command.substring(semicolon_index);
  }
}

void run_command(String c) {
  String head = c.substring(0, c.indexOf(":"));
  String tail = c.substring(c.indexOf(":") + 1); 
  //  KD key down
  if (head == "KD"){
    Keyboard.press(tail.toInt());
  }
  //  KU key up
  if (head == "KU"){
    Keyboard.release(tail.toInt());
  }
}

char read_data_pins() {
  for (int i = 0; i < sizeof(DATA_PINS) / sizeof(DATA_PINS[0]); i++) {
    pinMode(DATA_PINS[i], INPUT);
  }
  char output = 0;
  for (int i = 0; i < sizeof(DATA_PINS) / sizeof(DATA_PINS[0]); i++) {
    if (digitalRead(DATA_PINS[i]) == HIGH) {
      output ++;
    }
    output = output << 1;
  }
}

void write_data_pins(char input) {
  for (int i = 0; i < sizeof(DATA_PINS) / sizeof(DATA_PINS[0]); i++) {
    pinMode(DATA_PINS[i], OUTPUT);
    if ((input >> i) & 1) {
      digitalWrite(DATA_PINS[i], HIGH);
    } else {
      digitalWrite(DATA_PINS[i], LOW);
    }
  }
}
