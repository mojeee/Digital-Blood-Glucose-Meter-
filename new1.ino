#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_INA219 ina219;
  int j = 1;
  float mills =0;
 float t =0;
  float glucose=0;
void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }
  lcd.init();                      // initialize the lcd 
  lcd.init();
  uint32_t currentFrequency;


  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();
}

void loop(void) 
{ delay(500);
  lcd.clear();
  lcd.noBacklight();
  float shuntvoltage = 0;
  float busvoltage = 0;
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  if (shuntvoltage>1&&j==1){                  //qarar dadane navar daroone sooket
    shuntvoltage = ina219.getShuntVoltage_mV();
    if(shuntvoltage<=3){ //tashkhise navar qande khoone jadid
    delay(250);  
    lcd.backlight();
    lcd.setCursor(2,0);
    lcd.print("please apply");  //namayeshe peyqame qarar dadane qatre khoon
    lcd.setCursor(6,1);
    lcd.print("blood");
    
    busvoltage = ina219.getBusVoltage_V();
       while(busvoltage>3){                    // ta zamani ke navar daroone sooket ast va ta vaqti ke khoon bar rooye an qarar nagarefte varede loop mishavad
             busvoltage = ina219.getBusVoltage_V();
             shuntvoltage = ina219.getShuntVoltage_mV(); 
             while(shuntvoltage>3){
             delay(150);  
            shuntvoltage = ina219.getShuntVoltage_mV(); 
            busvoltage = ina219.getBusVoltage_V();
             if (shuntvoltage==40){                   //peyda kardan noqte max  
              lcd.clear();
               lcd.setCursor(2,0);
               lcd.print("please wait"); 
              while (shuntvoltage==40)  {    
                shuntvoltage = ina219.getShuntVoltage_mV(); 
                t=millis();  
                mills =0;
               while( mills<=4522&&shuntvoltage<40){        //4.5 sanie pas az noqte max ra peyda mikonad
                mills= millis()- t;
                     shuntvoltage = ina219.getShuntVoltage_mV(); 
               }}
                  

               glucose =  14.34*shuntvoltage - 243.64;      //formoole mohasebe qande khoon
               lcd.clear();
               lcd.setCursor(4,1);
               lcd.print(glucose);                          //namayeshe meqdare qande khoon 
               lcd.print(" mg/dL");
               j=0;
               delay(20000);
               break;
               }
               else if (shuntvoltage<30&&shuntvoltage>28){                    //tashkhise qarar dadane qatre khoon be nahve qalat
                 lcd.backlight();
                 lcd.setCursor(5,0);
                 lcd.print("error");
                 j=0;
                 break;}
             }
          }
      }
   else if(shuntvoltage>3){                                                   //tashkhise navare qande khoone estefade shode 
    delay(250);
    lcd.backlight();
    lcd.setCursor(5,0);
    lcd.print("error");
   busvoltage = ina219.getBusVoltage_V();
    while(busvoltage>3){
     busvoltage = ina219.getBusVoltage_V();}
    }
     }
    
      shuntvoltage = ina219.getShuntVoltage_mV(); 
      if (shuntvoltage<.5){j=1;}                                                //tashkhise biroon avardane navare qande khoon
      
      }
