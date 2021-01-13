#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  4

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

/* Thread 1 */
void *thread1 (void *t) {
  int boba1, boba2;

  printf("Thread 1: Comecei\n");
  
  /* faz alguma coisa para gastar tempo... */
  boba1=10000; boba2=-10000; while (boba2 < boba1) boba2++;
  
  printf("Bom dia!\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if(x == 2){

    printf("B: x = %d, vai sinalizar a condicao \n", x);
    pthread_cond_broadcast(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
/* Thread 2 */
void *thread2 (void *t) {
  int boba1, boba2;

  printf("Thread 2: Comecei\n");
  
  /* faz alguma coisa para gastar tempo... */
  boba1=10000; boba2=-10000; while (boba2 < boba1) boba2++;
  
  printf("tudo bem?\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if(x == 2){
    printf("B: x = %d, vai sinalizar a condicao \n", x);
    pthread_cond_broadcast(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Thread 3 */
void *thread3 (void *t) {
  printf("Thread 3: Comecei\n");

  pthread_mutex_lock(&x_mutex);
  if (x < 2 ) { 
     printf("Thread 3: vai se bloquear...\n");
     pthread_cond_wait(&x_cond, &x_mutex);
     printf("Thread 3: sinal recebido e mutex realocado, x = %d\n", x);
  }
  pthread_mutex_unlock(&x_mutex); 
  printf("até mais!\n");
  pthread_exit(NULL);
}

/* Thread 4 */
void *thread4 (void *t) {
  printf("Thread 4: Comecei\n");

  pthread_mutex_lock(&x_mutex);
  if (x < 2 ) { 
     printf("Thread 4: vai se bloquear...\n");
     pthread_cond_wait(&x_cond, &x_mutex);
     printf("Thread 4: sinal recebido e mutex realocado, x = %d\n", x);
  }
  pthread_mutex_unlock(&x_mutex); 
  printf("Boa Tarde!\n");
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, thread1, NULL);
  pthread_create(&threads[1], NULL, thread2, NULL);
  pthread_create(&threads[2], NULL, thread3, NULL);
  pthread_create(&threads[3], NULL, thread4, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  return 0;
}
