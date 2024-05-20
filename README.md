# leitura-radiacaoUV-arduino-mqtt

## Materiais 

- O modulo serial ESP8266 Node MCU, está ligado ao push button através do protoboard, utilizando o pino analógico D6 e GND.  Quando o push button  é pressionado, o modulo envia a informação 0 (display desligado) para o broker e ao soltar o push button, o modulo envia a informação 1(display ligado) para o broker, utilizando protocolo mqtt.  

O modulo wi-fi serial ESP8266 ESP-01, está conectado ao Arduino da seguinte maneira: 

- Pino GND: conectado ao pino GND do Arduino Uno.		 

- Pino TX: conectado à porta digital 2 do Arduino Uno. 

- Os pinos 3V3 e RX estão conectados no protoboard. 

O sensor UVM-30A está conectado da seguinte forma:  

- Pino OUT: conectado a pino analógico A0 do Arduino UNO. 

- Pino positivo: conectado ao protoboard positivo VCC.  

- Pino negativo: conectado ao protoboard negativo GND.  

Desta forma, estabelece as conexões necessárias para a leitura da intensidade da radiação UV. 

O programa faz a leitura da porta A0, e faz a conversão desse valor em milivolts, fazendo a associação do valor da tabela abaixo, para exibir o índice no display OLED I2C.   

O display OLED I2C está conectado ao Arduino Uno, utilizando a interface I2C para a transmissão de dados, da seguinte maneira:  

- Pino SDA: conectado na porta analógica A4 do Arduino Uno. 

- Pino SCL: conectado na porta analógica A5 do Arduino Uno.  

- Pino GND: conectado no protoboard GND. 

- Pino VCC: conectado no protoboard VCC.  

Estabelecer as conexões de alimentação entre os componentes e a fonte de alimentação externa. 

# Funcionamento  

- Conectando o sensor no Arduino 

O sensor UVM-30A possui três pinos:  

- VCC utilizado para alimentar o sensor com uma tensão entre 3,3v a 5v. Ligamos este pino no pino de 5V do Arduino. 

- GND que é o pino utilizado para o aterramento. Ligamos este pino ao pino GND do Arduino. 

- OUT que é o pino utilizado para a saída de sinal. Deve ser ligado a um pino analógico do Arduino, neste caso utilizaremos o pino A0. 

Quando o sensor é exposto à radiação UV, ele converte essa energia em uma corrente elétrica. Essa corrente é proporcional à intensidade da radiação detectada. A saída do sensor, pino OUT, é uma tensão analógica que varia de acordo com a intensidade da radiação UV detectada. 

Enviando mensagem do push button via protocolo MTQQ 

- O modulo serial wi-fi ESP8266 Node MCU, detecta quando o push buton foi apertado, e envia a mensagem para o browker. 

- O modulo serial wi-fi ESP8266 ESP-01, busca a mensagem e envia para a porta digital 2 do Arduino UNO, que consome a informação e liga e desliga o display OLED. 

Conectando o display OLED no Arduino 

- Para conectar o display ao Arduino iremos utilizar a protoboard para facilitar a ligação dos pinos. 

- O display deve ser colocado de forma que os pinos estejam alinhados com os trilhos da protoboard. Todos os pinos devem estar inseridos corretamente nos furos da protoboard. 

- O display possui quatro pinos, sendo eles: VCC (alimentação), GND (terra), SDA (transmissão dos dados) e SCL (sinal de clock) para sincronização da comunicação. 

- VCC deve ser conectado ao trilho positivo da protoboard. 

- GND deve ser conectado ao trilho negativo da protoboard. 

- SDA: utilizar um fio (jumper) para ligar este pino ao pino A4 analógico do Arduino. 

- SCL: utilizar outro fio jumper para ligar este pino ao pino A5 analógico do Arduino comumente utilizado para esta função. 

Conectando o display OLED no Arduino 

Protocolo MQTT

- MQTT (Message Queuing Telemetry Transport) é um protocolo de comunicação leve e eficiente, amplamente utilizado em aplicações de Internet das Coisas (IoT). Ele opera no modelo de publicação/assinatura (publish/subscribe), onde os dispositivos conectados (clientes) podem publicar mensagens em tópicos específicos ou assinar esses tópicos para receber mensagens. 

Componentes Principais: 

- Broker: Servidor central que recebe todas as mensagens publicadas e as encaminha para os clientes assinantes dos respectivos tópicos. 

- Clientes: Dispositivos que se comunicam através do broker, podendo tanto publicar quanto assinar tópicos. 

Funcionamento Básico: 

- Publicação: Um cliente publica uma mensagem em um tópico específico. Por exemplo, um sensor de temperatura pode publicar os dados de temperatura no tópico "casa/sala/temperatura". 

- Assinatura: Outros clientes assinam esse tópico para receber as mensagens publicadas. Por exemplo, um aplicativo no celular pode assinar o tópico "casa/sala/temperatura" para receber atualizações da temperatura. 

- Broker: O broker gerencia todas as conexões e distribui as mensagens dos tópicos publicados para todos os clientes assinantes desses tópicos. 
