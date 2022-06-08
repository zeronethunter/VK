// Copyright 2022 zenehu

#include "Subnet.h"

Server *Server_new(char *_dns, unsigned int *_ip, unsigned int *_mask,
                   unsigned int _thread_count, unsigned int _core_count) {
  if (!_dns || !_ip || !_mask) {
    return NULL;
  }
  if (_thread_count == 0 || _core_count == 0) {
    return NULL;
  }
  Server *new_server = (Server *)malloc(sizeof(Server));

  if (!new_server) {
    return NULL;
  }

  new_server->dns = _dns;
  new_server->ip = _ip;
  new_server->mask = _mask;
  new_server->core_count = _core_count;
  new_server->thread_count = _thread_count;
  return new_server;
}

int input_int(FILE *file) {
  if (!file) {
    return 0;
  }
  int c = 0;
  int result = 0;
  while (c = fgetc(file), c != EOF && c != '\n') {
    if (!(c >= '0' && c <= '9')) {
      char *buf = input_string(file); /* Read to the end of the string */
      free(buf);
      return 0;
    }
    // NOLINTNEXTLINE (*-magic-numbers)
    result = result * 10 + c - '0';
  }
  return result;
}

char *input_string(FILE *file) {
  if (!file) {
    return NULL;
  }
  char c = 0;
  size_t size = 1;
  size_t len = 0;
  char *str = (char *)malloc(sizeof(char) * size);
  if (!str) {
    return NULL;
  }
  while (c = (char)fgetc(file), c != EOF && c != '\n') {
    str[len] = c;
    ++len;
    if (len == size) {
      size += 16;
      char *tmp = realloc(str, sizeof(char) * size);
      if (!tmp) {
        free(str);
        return NULL;
      }
      str = tmp;
    }
  }
  str[len] = '\0';
  ++len;

  char *tmp = realloc(str, sizeof(*str) * len);
  if (!tmp) {
    free(str);
    return NULL;
  }
  return tmp;
}

unsigned int *input_ip(FILE *file, size_t n) {
  unsigned int *ip = (unsigned int *)malloc(sizeof(unsigned int) * n);
  if (!ip) {
    return NULL;
  }
  for (int i = 0; i < n; ++i) {
    printf("%d. ", i + 1);
    int num = input_int(file);
    if (num < 0 || num > 255) {
      free(ip);
      return NULL;
    }
    ip[i] = num;
  }
  if (!ip) {
    return NULL;
  }
  return ip;
}

void print_ip(const unsigned int *ip, size_t n) {
  if (!ip) {
    return;
  }
  for (size_t i = 0; i < n - 1; ++i) {
    printf("%u.", ip[i]);
  }
  printf("%u\n", ip[n - 1]);
}

void print_server(const Server *server) {
  if (!server) {
    return;
  }
  printf("%s: %s\n", "DNS", server->dns);

  printf("%s: ", "ip");
  print_ip(server->ip, 4);

  printf("%s: ", "MASK");
  print_ip(server->mask, 4);

  printf("%s: %u\n", "Count of threads", server->thread_count);

  printf("%s: %u\n", "Count of cores", server->core_count);
}

void print_subnet(const Subnet *subnet) {
  if (!subnet) {
    return;
  }
  for (int i = 0; i < subnet->size; ++i) {
    printf("%d)\n", i + 1);
    print_server(&subnet->servers[i]);
  }
}
