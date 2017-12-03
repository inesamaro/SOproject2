#include "header.h"

void atendimento() {
  Paciente paciente; // = (Paciente)malloc(sizeof(struct pa
  clock_t start = clock();
  clock_t end = clock();
  double shift_time = (double)(end - start);// / CLOCKS_PER_SEC;

  while (shift_time < config->tempoTurno) {
    if (msgrcv(mqid, &paciente, sizeof(paciente)-sizeof(long), -3, 0) == -1){
  	perror("Oh boy u got a error recieving a msg from the messagequeue");
    }
    sleep(paciente.info.tempoAtend);
    printf("-----------------------------------> %s, %ld\n",paciente.info.nome, paciente.mtype);

    end = clock();
    shift_time = (double)(end - start); // / CLOCKS_PER_SEC;
    printf("shift time %f // tempo doctor %d\n", shift_time, config->tempoTurno);
  }
}

void criarDoutor() {
  int i;
  for (i=0; i<5/*config->nDoutores*/; i++) {
    if (fork() == 0) {
      printf("[%d] INICIO DOUTOR\n", getpid());
      atendimento();//por fazer
      printf("[%d] FIM DOUTOR\n", getpid());
      exit(0);
    }
  }

  int rc;
  struct msqid_ds buf;
  int num_pacientes;

  while(1){ //sempre que um dos processos morre um novo é criado
      wait(NULL);
      msgctl(mqid, IPC_STAT, &buf);
      num_pacientes = buf.msg_qnum;
      if (num_pacientes > 0) {
        printf("numero de pacientes na queue: %d\n", num_pacientes);
        if(fork() == 0){
          printf("[%d] NEW INICIO DOUTOR\n", getpid());
          atendimento(); //por fazer
          printf("[%d] NEW FIM DOUTOR\n", getpid());
          exit(0);
        }
      }
    }
 //de momento manter comentado para nao criar demasiados doutores
}
