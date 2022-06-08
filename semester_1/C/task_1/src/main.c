// Copyright 2022 zenehu

#include <stdio.h>

#include "Subnet.h"

bool make_subnet(Subnet **new_subnet);
bool make_server(Server *server, size_t index);
void delete (Subnet *subnet);

int main() {
  Subnet *new_subnet = NULL;
  bool is_right = make_subnet(&new_subnet);
  if (is_right) {
    print_subnet(new_subnet);
  } else {
    printf("%s", "Something went wrong!");
  }
  delete (new_subnet);
  return 0;
}

bool make_server(Server *server, size_t index) {
  if (!server) {
    return false;
  }

  Server new_server;

  printf("%zu. %s: ", index + 1, "Input dns");
  char *tmp_string = input_string(stdin);
  if (!tmp_string) {
    return false;
  }
  new_server.dns = tmp_string;

  unsigned int *tmp = NULL;

  printf("   %s:\n", "Input ip");
  tmp = input_ip(stdin, 4);
  if (!tmp) {
    return false;
  }
  new_server.ip = tmp;

  printf("   %s:\n", "Input mask");
  tmp = input_ip(stdin, 4);
  if (!tmp) {
    return false;
  }
  new_server.mask = tmp;

  printf("   %s: ", "Input count of threads");
  unsigned int thread_count = input_int(stdin);
  if (!thread_count) {
    return false;
  }
  new_server.thread_count = thread_count;

  printf("   %s: ", "Input count of cores");
  unsigned int core_count = input_int(stdin);
  if (!core_count) {
    return false;
  }
  new_server.core_count = core_count;
  *server = new_server;

  return true;
}

bool make_subnet(Subnet **new_subnet) {
  *new_subnet = (Subnet *)calloc(1, sizeof(Subnet));

  if (!*new_subnet) {
    return false;
  }

  Subnet *_subnet = *new_subnet;

  printf("%s\n", "Input subnet: (x.x.x.0)");

  unsigned int *tmp_ip = NULL;

  tmp_ip = input_ip(stdin, 4);
  if (!tmp_ip) {
    return false;
  }
  if (tmp_ip[3] != 0) {
    return false;
  }
  _subnet->subnet = tmp_ip;

  printf("%s: ", "Your subnet");
  for (int i = 0; i < 3; ++i) {
    printf("%u.", _subnet->subnet[i]);
  }
  printf("%u\n", _subnet->subnet[3]);
  printf("%s", "Input count of servers in this subnet: ");

  _subnet->size = input_int(stdin);
  if (!_subnet->size) {
    return false;
  }
  _subnet->servers = (Server *)malloc(sizeof(Server) * _subnet->size);
  if (!_subnet->servers) {
    return false;
  }

  for (size_t i = 0; i < _subnet->size; ++i) {
    if (!make_server(&_subnet->servers[i], i)) {
      return false;
    }
  }
  return true;
}

void delete (Subnet *subnet) {
  if (!subnet) {
    return;
  }
  free(subnet->subnet);
  for (int i = 0; i < subnet->size; ++i) {
    free(subnet->servers[i].ip);
    free(subnet->servers[i].dns);
    free(subnet->servers[i].mask);
  }
  free(subnet->servers);
  free(subnet);
}
