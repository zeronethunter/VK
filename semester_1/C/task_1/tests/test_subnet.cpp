#include <gtest/gtest.h>

extern "C" {
#include "Subnet.h"
}

TEST(ServerCreationTest, RightTest) {
  // cppcheck-suppress cstyleCast
  auto *new_subnet = (Subnet *)malloc(sizeof(Subnet));
  new_subnet->size = 1;

  const char *std_in = "192\n168\n1\n0\n";

  FILE *std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  unsigned int *subnet = input_ip(std_in_f, 4);
  fclose(std_in_f);

  EXPECT_FALSE(!subnet);

  new_subnet->subnet = subnet;

  const char *dns = "mr.robot.ru";

  std_in = "192\n168\n1\n1\n";

  std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  unsigned int *ip = input_ip(std_in_f, 4);
  fclose(std_in_f);

  EXPECT_FALSE(!ip);

  std_in = "255\n255\n255\n0\n";

  std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  unsigned int *mask = input_ip(std_in_f, 4);
  fclose(std_in_f);

  EXPECT_FALSE(!mask);

  unsigned int thread_count = 4;
  unsigned int core_count = 8;

  new_subnet->servers =
      Server_new((char *)dns, ip, mask, thread_count, core_count);

  EXPECT_FALSE(!new_subnet->servers);

  free(ip);
  free(mask);
  free(new_subnet->servers);
  free(new_subnet->subnet);
  free(new_subnet);
}

TEST(ServerCreationTest, WrongTest) {
  unsigned int wrong_thread_count = 0;
  unsigned int wrong_core_count = 0;
  auto *ip = (unsigned int *)malloc(sizeof(unsigned int) * 4);
  auto *mask = (unsigned int *)malloc(sizeof(unsigned int) * 4);

  ip[0] = 192;
  ip[1] = 168;
  ip[2] = 1;
  ip[3] = 25;

  mask[0] = 255;
  mask[1] = 255;
  mask[2] = 255;
  mask[3] = 0;

  const char *right_dns = "mr.robot.ru";
  unsigned int right_thread_count = 4;
  unsigned int right_core_count = 8;

  Server *new_server =
      Server_new(NULL, ip, mask, right_thread_count, right_core_count);
  EXPECT_FALSE(new_server);

  new_server = Server_new((char *)right_dns, ip, mask, wrong_thread_count,
                          right_core_count);
  EXPECT_FALSE(new_server);

  new_server = Server_new((char *)right_dns, ip, mask, right_thread_count,
                          wrong_core_count);
  EXPECT_FALSE(new_server);

  free(ip);
  free(mask);
  free(new_server);
}

TEST(InputTest, InputInt) {
  const char *std_in = "123s123\n";

  FILE *std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  EXPECT_FALSE(input_int(std_in_f));

  fclose(std_in_f);
}

TEST(InputTest, InputString) {
  const char *std_in = "123s123\n";

  FILE *std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  char *tmp_string = input_string(std_in_f);
  EXPECT_EQ(strcmp("123s123", tmp_string), 0);

  fclose(std_in_f);
  free(tmp_string);
}

TEST(InputTest, InputIP) {
  const char *std_in = "256\n168\n1\n0\n";

  FILE *std_in_f = fmemopen((char *)std_in, strlen(std_in), "r");
  unsigned int *ip = input_ip(std_in_f, 4);

  EXPECT_FALSE(ip);

  fclose(std_in_f);
  free(ip);
}