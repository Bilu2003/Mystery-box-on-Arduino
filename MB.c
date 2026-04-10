void LED_check(int i , int tab[], int len);
void levele(int tab[], int len);
int read_diode();
void gierka();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello!");
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); 
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW); 
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 
  
  // przyciski
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  //8,9 silnik, 6 pwm slinik
  pinMode(8, OUTPUT); //sterowanie
  //DODAC 9 JAKO DRUGI SILNIK, POZOSTALE INY DWÓCH SILNIKOW DO MASY I KIERUJE TYLKO HIGHEM NA JEDYM PINIE
  pinMode(6,OUTPUT); //pwm


  pinMode(9, OUTPUT); //sterowanie 2 silnik high-kręć
  pinMode(11,OUTPUT);  //pwm drugi

  //DUZE LEDY
  pinMode(5,OUTPUT); //ziel
  pinMode(12,OUTPUT); //czerw
  //teraz zrobic koncowy kod, podpopinac, pokleic i spiąć w obudoiwe, potem połączyc z kartonami.
}

void loop() {

  //świecenie wzystkich na początku
  digitalWrite(5, HIGH); 
  digitalWrite(12, HIGH); 
  digitalWrite(13, HIGH); 
  digitalWrite(7, HIGH); 
  digitalWrite(10, HIGH); 
  delay(3000);
  digitalWrite(5, LOW); 
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW); 
  digitalWrite(7, LOW); 
  digitalWrite(10, LOW); 

  //G = 1, R = 2, Y = 3
  int lista1[] = {3,2,3,1,2,3};
  int lista2[] = {1,1,3,2,3,1,2};
  int lista3[] = {3,2,2,1,1,3,1,2};
  //level1
  Serial.println("level1: ");
  levele(lista1, 6);
  LED_check(0, lista1, 6);
  digitalWrite(7, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(13, LOW);
  delay(500);
  
 

  //level 2
  Serial.println("level2: ");
  levele(lista2, 7);
  LED_check(0, lista2, 7);
  digitalWrite(7, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(13, LOW);
  delay(500);
  //level3
  Serial.println("level3: ");
  levele(lista3, 8);
  LED_check(0, lista3, 8);
  Serial.println("koniec");

  digitalWrite(5, HIGH); 
  digitalWrite(12, HIGH); 
  digitalWrite(13, HIGH); 
  digitalWrite(7, HIGH); 
  digitalWrite(10, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(6, 170);
  delay(4300);
  digitalWrite(8, LOW);
 
  //WYBOR SKRYTKI
  
  digitalWrite(10, LOW); 
  int wybor;
  while (true){
    if (digitalRead(2)==0){
      digitalWrite(8, HIGH);
      analogWrite(6, 160);
      delay(4200);
      digitalWrite(8, LOW);
      wybor = 1;
      break;
    }
    if (digitalRead(4)==0){
      digitalWrite(9, HIGH);
      analogWrite(11, 160);
      delay(4200);
      digitalWrite(9, LOW);
      wybor = 2;
      break;
    }

    }
  
  
  digitalWrite(10, HIGH);
  delay(1000);

  digitalWrite(5, LOW); 
  digitalWrite(12, LOW); 
  digitalWrite(13, HIGH); 
  digitalWrite(7, HIGH); 
  digitalWrite(10, HIGH); 

  //gierka abc
  gierka();
  if (wybor ==1){
    digitalWrite(9, HIGH);
    analogWrite(11, 160);
    delay(4200);
    digitalWrite(9, LOW);

  }else{
      digitalWrite(8, HIGH);
      analogWrite(6, 160);
      delay(4200);
      digitalWrite(8, LOW);
  }
  delay(5000);

}
void levele(int tab[], int len){
  for (int i=0; i<len;i++){
    if (tab[i] == 1){
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
    }
    if (tab[i] == 2){
      digitalWrite(10, HIGH);
      delay(500);
      digitalWrite(10, LOW);
    }
    if (tab[i] == 3){
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7, LOW);
    }
    delay(200);
    }
  }



int read_diode(){
    while (true){
      int r = digitalRead(2);
      int m = digitalRead(3);
      int l = digitalRead(4);
      if (l == 0){
        
        
        digitalWrite(13, HIGH); 
        delay(220);
        digitalWrite(13, LOW); 
        Serial.println("1");
        return 1;
        
      }
      if (m == 0){
        
        
        digitalWrite(10, HIGH); 
        delay(220);
        digitalWrite(10, LOW); 
        Serial.println("2");
        return 2;
        
      }
      if (r == 0){
        
        
        digitalWrite(7, HIGH); 
        delay(220);
        digitalWrite(7, LOW); 
        Serial.println("3");
        return 3;
        
      }
    }
}
void LED_check(int i, int tab[], int len){
  delay(50);
  
  
  int lista_len = len;

  if (i==lista_len){
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(5, LOW);
    return;
  }

  int X = read_diode();

  if(X==tab[i]){
    i++;
    LED_check(i, tab, len);
  } else{
    //źle
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
    levele(tab, len);
    LED_check(0,tab, len);
  }


}
void gierka(){
  Serial.println("wszedlem do gierki");
  
  int x, y, z;
  for (int i=0;i<3;i++){
    switch (i) {
      case 0: {
        x = 2;
        y = 4;
        z = 3;
        // zrób coś z tymi zmiennymi, bo poza klamrami znikną!
        break;
      }
      case 1: {
        x = 4;
        y = 2;
        z = 3;
        break;
      }
      case 2: {
        x = 3;
        y = 4;
        z = 2;
        break;
    }
      default:
        Serial.println("Błąd danych!"); 
        break;
    }
    Serial.println(x);
    
    while (true){
      
      if (digitalRead(x)==0){
        Serial.println("wykonano zgadniecie gierki");
        digitalWrite(5, HIGH);
        delay(500);
        digitalWrite(5, LOW);
        
        break;
        }
      if (digitalRead(y)==0){
        Serial.println("wykonano niezgadniecie gierki");
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        }
      if (digitalRead(z)==0){
        Serial.println("wykonano niezgadniecie gierki");
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        }
  
    }
  }
}
