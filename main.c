#include "header.h"

int main(int argc, char *argv[]){
  config = (Config*)malloc(sizeof(Config));
  fichLog = fopen("ficheiroLog.log", "w");

  criarMemPartilhada();

  lerFichConfig();

  queuePacientes = criarQueuePacientes();

  queuePacientes = namedPipe();

  criarMQ();

  criarTriagens();

  criarDoutor();
}
