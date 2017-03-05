void setup()
{
  Serial.begin(9600);
  
  float floatVal= -123.3436767;    
  String stringVal = "";     
  
  stringVal+=String(int(floatVal))+ "."+String(getDecimal(floatVal)); //combining both whole and decimal part in string with a fullstop between them
  Serial.print("stringVal: ");Serial.println(stringVal);              //display string value
  
  char charVal[stringVal.length()+1];                      //initialise character array to store the values
  stringVal.toCharArray(charVal,stringVal.length()+1);     //passing the value of the string to the character array
  
  Serial.print("charVal: ");  
  for(uint8_t i=0; i<sizeof(charVal);i++) Serial.print(charVal[i]); //display character array
  
}
void loop()
{
}
//function to extract decimal part of float
long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 1000*(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places. 
                                    //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}
