const int pinLDR = A0;      // Entrée analogique du capteur de luminosité
const int pinLED = D4;      // Sortie digitale pour la LED
const int pinPIR = D2;      // Entrée digitale du capteur de mouvement

int seuilBas = 100;         // En dessous de cette valeur = sombre (peut allumer)
int seuilHaut = 110;        // Au dessus de cette valeur = assez lumineux (éteint)
//2 seuils pour éviter l'hystérésis

bool ledAllumee = false;    // Etat actuel de la LED

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinPIR, INPUT);
  Serial.begin(115200);
}

void loop() {
  int valeurLumiere = analogRead(pinLDR);   // 0 à 1023
  bool mouvementDetecte = digitalRead(pinPIR) == HIGH;

  Serial.print("Luminosité : ");
  Serial.print(valeurLumiere);
  Serial.print(" | Mouvement : ");
  Serial.println(mouvementDetecte ? "OUI" : "non");

  if (!ledAllumee && mouvementDetecte && valeurLumiere < seuilBas) {
    // Sombre + mouvement -> on allume
    ledAllumee = true;
    digitalWrite(pinLED, HIGH);
  }
  else if (ledAllumee && valeurLumiere > seuilHaut) {
    // Assez lumineux -> on éteint, peu importe le mouvement
    ledAllumee = false;
    digitalWrite(pinLED, LOW);
  }

  delay(200);
}