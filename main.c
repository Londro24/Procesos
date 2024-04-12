#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  int pid = fork(); // Se genera el proceso hijo

  // Podemos observar el PID del proceso
  // 0 significa que es el hijo
  printf("PID proceso: %d\n", pid);

  if (pid == 0) { // Proceso hijo
    printf("Proceso hijo, PID: %d, PPID: %d\n", getpid(), getppid());

    // Se genera un número aleatorio de 0 a 1
    int numero = rand() % 10;

    if (numero == 1) { // si el numero aleatorio es 1, se aborta el proceso
      printf("EL numero es un 1. Abortando el programa.\n");
      abort();
      return 1;
    } else {
      // llamado al programa ps
      execlp("ps", "ps", "-f", NULL);
    }

    // Si execlp() falla, se muestra un mensaje de error
    perror("execlp");
    // Termina el proceso hijo de forma normal por error no grave.
    exit(1);

  } else if (pid > 0) { // Proceso padre

    // creamos un segundo proceso hijo
    int pid2 = fork();

    if (pid2 == 0) {
      // Proceso hijo 2
      printf("Proceso hijo 2, PID: %d, PPID: %d\n", getpid(), getppid());
      while (1) {
        printf("Proceso hijo 2 en ejecución\n");
        sleep(1);
      }
    } else if (pid2 > 0) {
      printf("Proceso padre, PID: %d, PPID: %d\n", getpid(), getppid());
      sleep(5); // espera a que el hijo se termine de ejecutar

      // Matamos a los procesos hijos
      printf("Proceso padre: Enviando señal KILL a los procesos hijos\n");
      kill(pid, SIGKILL);
      kill(pid2, SIGKILL);
      printf("Proceso padre: El proceso hijo ha terminado\n");
    } else {
      // Si el fork() falla, se muestra un mensaje de error
      perror("fork 2");
      // Sale del programa de forma normal por error no grave
      exit(1);
    }
  } else {
    // Si el fork() falla, se muestra un mensaje de error
    perror("fork");
    // Sale del programa de forma normal por error no grave
    exit(1);
  }

  return 0;
}
