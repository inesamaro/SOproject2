#include "header.h"

void criarTriagens() {
  pthread_t vTriagens[10/*config->nTriagens*/];
  int i;
  int idsTriagens[10/*config->nTriagens*/];
  Paciente * paciente;

  //cria o numero de triagens necessarias
  for (i=0; i<10 /*config->nTriagens*/; i++) {
    idsTriagens[i] = i;

    pthread_create(&vTriagens[i], NULL, triagem, &idsTriagens[i]/*paciente*/);

    Paciente* aux = queuePacientes;
    printf("QueuePacientes depois de eliminar: \n");
    while(aux->info.next != NULL) {
      aux = aux->info.next;
      printf("nome: %s\n", aux->info.nome);
    }
  }

  for (i=0; i<config->nTriagens; i++) {
    pthread_join(vTriagens[i], NULL);
  }
}
