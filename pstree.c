#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // Crear el primer proceso hijo
  int pid = fork();

  if (pid == 0) {
    // Proceso hijo
    printf("Proceso hijo 1, PID: %d, PPID: %d\n", getpid(), getppid());

    // Crear el proceso nieto
    pid = fork();

    if (pid < 0) {
      printf("Error al crear el proceso hijo\n");
      exit(1);
      return 1;

    } else if (pid == 0) {
      // Proceso nieto
      printf("Proceso nieto, PID: %d, PPID: %d\n", getpid(), getppid());
      execlp("pstree", "pstree", "-p", NULL);

    } else {
      // Proceso hijo 1
      sleep(1);
      printf("Proceso hijo 1 terminando\n");
      exit(0);
    }
  } else if (pid > 0) { // Proceso padre

    // Crear el segundo proceso hijo
    int pid2 = fork();

    if (pid2 < 0) {
      printf("Error al crear el proceso hijo\n");
      exit(1);
      return 1;

    } else if (pid2 == 0) { // Proceso hijo 2
      // proceso nieto de hijo 2
      int pid3 = fork();

      if (pid3 == 0) {
        printf("Proceso nieto 2: nieto 2 %d padre: %d\n", getpid(), getppid());
        sleep(1);
        printf("Proceso nieto 2, terminado\n");
        exit(0);

      } else if (pid3 > 0) {
        printf("Proceso hijo 2, PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(1);
        printf("Proceso hijo 2, terminado\n");
        exit(0);

      } else {
        printf("Error al crear el proceso nieto2\n");
        exit(1);
        return 1;
      }

    } else {
      // Proceso padre
      sleep(1);
      printf("Proceso padre terminando\n");
      exit(0);
    }

  } else {
    // Error al crear el proceso hijo
    printf("Error al crear el proceso hijo\n");

    // Salida del proceso de forma controlada por error no fatal
    exit(1);
    return 1;
  }
  return 0;
}
