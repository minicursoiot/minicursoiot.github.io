/*  Arduino Day 2019 - IFPB
 *  Introdução a IoT com NodeMCU 
 *  Ministrantes: Angelo Johnson, Laura Macaíba e Raylle Cordeiro
 */

#include <ESP8266WiFi.h>  //Biblioteca para gerenciamento do WiFi.
#include <WiFiServer.h>   //Biblioteca para gerenciamento do TCP.
 
WiFiServer servidor(80);  //Cria um objeto "servidor" na porta 80 (http).
WiFiClient cliente; //Cria um objeto "cliente".
 
String html;  //String que armazena o corpo do site.
 
void setup()
{
   Serial.begin(9600);  //Inicia comunicaçao Serial.
 
   WiFi.mode(WIFI_STA); //Habilita o modo STATION.
   WiFi.begin("NOME_DA_REDE", "SENHA_DA_REDE");  //Conecta no WiFi (COLOQUE O NOME E SENHA DA SUA REDE)
 
   //Serial.print(WiFi.localIP());  //Printa o IP que foi concebido ao ESP8266 (este ip que voce ira acessar)
   servidor.begin();  //Inicia o Servidor.
   
  Serial.print("Conectando");
  //Verifica se esta conectado
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();

  Serial.print("Conectado, Endereço de IP: ");
  Serial.println(WiFi.localIP());
  pinMode(D4, OUTPUT);  //Define o pino 4 como saída.
}
 
void loop()
{
   cliente = servidor.available();  //Diz ao cliente que há um servidor disponivel.
 
   if (cliente == true) //Se houver clientes conectados, ira enviar o HTML.
   {
      String req = cliente.readStringUntil('\r'); //Faz a leitura do Cliente.
      Serial.println(req);//Printa o pedido no Serial monitor.
 
      if (req.indexOf("/LED") > -1) //Caso o pedido houver led, inverter o seu estado.
         digitalWrite(D4, !digitalRead(D4));  //Inverte o estado do led.
 
      html = "";//Reseta a string.
      html += "HTTP/1.1 Content-Type: text/html\n\n"; //Identificaçao do HTML.
      html += "<!DOCTYPE html><html><head><title>Arduino Day</title>";//Identificaçao e Titulo.
      html += "<meta name='viewport' content='user-scalable=no'charset='utf-8'>"; //Desabilita o Zoom.
      html += "<style>.btn{font-size:20px; color:white; background-color:#0094ff; width:200px; height:50px;}</style>"; //Estilização do botão
      html += "</head><body><center><br>";
      html += "<h1><font face='arial'>Introdução à IoT com NodeMCU </font></h1>"; 
      html += "<form action='/LED' method='get'>";  //Cria um botao para o link /LED
      html += "<button type='submit' class='btn' value='LED'> LED </button></form>";
      html += "</center></body></html>";  //Termino e fechamento de TAG`s do HTML. Nao altere nada sem saber!
      
      cliente.print(html);//Finalmente, enviamos o HTML para o cliente.
      cliente.flush();//Encerra a conexao.
   }
}
