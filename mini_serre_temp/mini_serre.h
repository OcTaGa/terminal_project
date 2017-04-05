#include <Arduino.h>



class MIS
{
  public:
      void Menu(char key_menu);
      void Display(int temp_cons, int temp_dht, float h, bool StateRelay);
      bool Thermostat(int temp_cons, int temp_dht);
      int ValueRead(int temp_cons, char key);
  protected:
      int key;
      int key_menu:

};
