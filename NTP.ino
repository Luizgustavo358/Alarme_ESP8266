// NTP Server
extern const char* NTP_SERVER;
extern const int timeZone;

extern WiFiUDP Udp;
extern unsigned int localPort;

extern IPAddress ntpServerIP;

void configNTP() {
  Udp.begin(localPort);
  Serial.println("Iniciando cliente UDP");

  Serial.print("Conectando a ");
  Serial.println(NTP_SERVER);

  IPAddress dns(8, 8, 8, 8);  // Exemplo de servidor DNS do Google
  WiFi.config(IPAddress(192, 168, 31, 100), IPAddress(192, 168, 31, 1), IPAddress(255, 255, 255, 0), dns);

  WiFi.hostByName(NTP_SERVER, ntpServerIP);

  Serial.print("Servidor NTP encontrado em: ");
  Serial.println(ntpServerIP);

  setSyncProvider(getNtpTime);
  setSyncInterval(300);  // Atualizar a hora a cada 300 segundos (5 minutos)
}

time_t getNtpTime() {
  const int NTP_PACKET_SIZE = 48;     // tamanho do pacote NTP
  byte packetBuffer[NTP_PACKET_SIZE]; // buffer para armazenar o pacote NTP

  // monta o pacote NTP
  memset(packetBuffer, 0, NTP_PACKET_SIZE); // limpa o buffer

  packetBuffer[0]  = 0b11100011; // Versao do NTP, modo cliente
  packetBuffer[1]  = 0;          // Numero de stratum
  packetBuffer[2]  = 6;          // Intervalo maximo entre atualizacoes
  packetBuffer[3]  = 0xEC;       // Clock estrato
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  // enviar pacote NTP para o servidor
  Udp.beginPacket(ntpServerIP, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();

  // aguardar resposta do servidor NTP
  delay(1000);

  // verifica se ha dados recebidos
  if(Udp.parsePacket()) {
    // le a resposta do servidor NTP
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    // converte os 4 bytes da resposta do timestamp para um long
    unsigned long secsSince1900 = (unsigned long) packetBuffer[40] << 24 |
                                  (unsigned long) packetBuffer[41] << 16 |
                                  (unsigned long) packetBuffer[42] << 8  |
                                  (unsigned long) packetBuffer[43];

    // tempo unix comeca em 1 de janeiro de 1970
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;

    return epoch + timeZone * SECS_PER_HOUR;  // Ajuste para o fuso horário correto
  }

  return 0; // se nao conseguir a hora
}