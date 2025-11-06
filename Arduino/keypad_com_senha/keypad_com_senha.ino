#include <Keypad.h>  
// biblioteca do teclado matricial
#include <LiquidCrystal.h> 
// biblioteca do display LCD

LiquidCrystal lcd(9,8,10,11,12,13); // RS, E, DB4, DB5, DB6, DB7

const byte linhas = 4;
const byte colunas = 4;  
byte linhaPino[linhas] = {7,6,5,4};
byte colunaPino[colunas] = {3,2,A0,A1};
String senha_digitada = ""; // armazena a sequência de teclas digitadas

char teclado[linhas][colunas] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}  
};

Keypad mapeamento = Keypad(makeKeymap(teclado), linhaPino, colunaPino, linhas, colunas);

int numero_digitado = 0; // acompanha o número de teclas digitadas

void setup()
{
 Serial.begin(9600); // início da comunicação serial 
 lcd.begin(16,2); // início do display LCD que tem 16 colunas e 2 linhas
}

void loop()
{  
  char senha = mapeamento.getKey(); // verifica se uma tecla foi pressionada
  
  if(numero_digitado == 0) {
    lcd.setCursor(0,0); // faz "SENHA" aparecer na primeira linha do display
    lcd.print("SENHA: ");
  }
    
  
  if(senha){ // "se uma tecla for acionada"
    senha_digitada = senha_digitada + senha; // armazena a sequência de dígitos da senha
    numero_digitado = ++numero_digitado; // quantidade de vezes que a tecla foi clicada
    lcd.clear(); // limpa o conteúdo do display LCD
    lcd.setCursor(6,0);  
    
    switch(numero_digitado) { // exibe asteriscos no LCD com base no valor atual de numeros digitados
      case 1: 
        lcd.print("*");
        break;
      
      case 2: 
        lcd.print("**");      
        break;   
      
      case 3: 
        lcd.print("***");
        break;
      
      case 4: 
      	lcd.print("****");
      
        if(senha_digitada == "ABC0"){
          lcd.setCursor(0,1); // faz a permissão ou não de acesso aparecer na segunda linha do display
          lcd.print("ACESSO LIBERADO");
          delay(1000);
          lcd.clear();                
          lcd.print("SENHA: "); 
        }

        else {
          lcd.setCursor(0,1);  
          lcd.print("ACESSO NEGADO");
          delay(1000);
          lcd.clear();                
          lcd.print("SENHA: ");
        }

        delay(1000);
        numero_digitado = 0;
// aqui o programa está reiniciando a contagem para uma nova tentativa de digitação da senha,
// ou seja, a cada vez que 1 quarteto de senha é digitada, ele reinicia na contagem 0 no motor serial
        senha_digitada = "";
// ao atribuir a string vazia, o programa limpa qualquer valor anteriormente armazenado nessa variável
        Serial.println(numero_digitado);      
        break;
      }
    }
}
