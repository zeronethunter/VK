// Copyright 2022 zenehu

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SUBNET_LIB_SUBNET_H_
#define SUBNET_LIB_SUBNET_H_

typedef struct {
  char *dns;
  unsigned int *ip;
  unsigned int *mask;
  unsigned int thread_count;
  unsigned int core_count;
} Server;

typedef struct {
  unsigned int *subnet;
  unsigned int size;
  Server *servers;
} Subnet;

Server *Server_new(char *_dns, unsigned int *_ip, unsigned int *_mask,
                   unsigned int _thread_count, unsigned int _core_count);

void print_server(const Server *server);

void print_subnet(const Subnet *subnet);

unsigned int *input_ip(FILE *file, size_t n);

void print_ip(const unsigned int *ip, size_t n);

char *input_string(FILE *file);

int input_int(FILE *file);

#endif  // SUBNET_LIB_SUBNET_H_
