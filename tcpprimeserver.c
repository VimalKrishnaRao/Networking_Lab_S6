#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// Function to check if a number is prime
int isPrime(int num) {
  if (num <= 1) return 0;
  if (num <= 3) return 1;
  if (num % 2 == 0 || num % 3 == 0) return 0;
  for (int i = 5; i * i <= num; i += 6) {
    if (num % i == 0 || num % (i + 2) == 0) return 0;
  }
  return 1;
}

int main() {
  char buf[100];
  int k;
  socklen_t len;
  int sock_desc, temp_sock_desc, num;

  struct sockaddr_in server, client;

  sock_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_desc == -1)
    printf("Error in Socket creation\n");

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 3003;

  k = bind(sock_desc, (struct sockaddr*)&server, sizeof(server));

  if (k == -1)
    printf("Error in binding\n");

  k = listen(sock_desc, 5);

  if (k == -1)
    printf("Error in listening\n");

  len = sizeof(client);
  temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);

  if (temp_sock_desc == -1)
    printf("Error in temporary socket creation\n");

  for (;;) {
    bzero(buf, sizeof(buf));
    read(temp_sock_desc, buf, sizeof(buf));
    printf("\n[From Client]:%s", buf);

    if (strncmp("exit", buf, 4) == 0 || strncmp("Exit", buf, 4) == 0) {
      printf("Got Exit Request\nExiting!!!\n");
      exit(0);
    }

    // Extract the number from the received message
    sscanf(buf, "%d", &num);

    // Check if the number is prime and prepare response
    if (isPrime(num)) {
      sprintf(buf, "%d is a prime number\n", num);
    } else {
      sprintf(buf, "%d is not a prime number\n", num);
    }

    printf("[To Client]:");
    write(temp_sock_desc, buf, sizeof(buf));
  }
  return 0;
}
