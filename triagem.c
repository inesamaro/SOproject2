#include "header.h"

void *triagem(int *num){
  printf("TRIAGEM HAPPENING\n");
  Paciente *paciente;

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);
  fprintf(fichLog, "Triagem %d started\n", *num);

  paciente = queuePacientes->info.next;
  printf("Paciente que vai ser eliminado: %s\n", paciente->info.nome);
  queuePacientes->info.next = (queuePacientes->info.next)->info.next;

  sleep((int)paciente->info.tempoTriagem);
  shared_var->nTriados += 1;
  printf("numero de pessoas triadas: %d \n", (shared_var)->nTriados);
  sendMQ(*paciente);
  pthread_mutex_unlock(&mutex);

  return NULL;
}
