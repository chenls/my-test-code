#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((__packed__)) {
  uint8_t version; // Current version is 0
  uint64_t challenge;
  uint64_t user_id;            // secure user ID, not Android user ID
  uint64_t authenticator_id;   // secure authenticator ID
  uint32_t authenticator_type; // hw_authenticator_type_t, in network order
  uint64_t timestamp;          // in network order
  uint8_t hmac[32];
} AncHwAuthToken;

void OnExcuteCommand(void *p_device, int32_t command_id, int32_t argument,
                     const uint8_t *p_output_buffer, uint32_t out_length) {
  printf("OnExcuteCommand p_output_buffer : %d %d %d %d\n", p_output_buffer[0],
         p_output_buffer[1], p_output_buffer[7], p_output_buffer[9]);
}

int AncExcuteCommand(void *p_device, int32_t command_id,
                     const uint8_t *p_in_param, uint32_t in_param_length,
                     uint8_t **p_output_buffer,
                     uint32_t *p_output_buffer_length) {

  AncHwAuthToken temp_auth_token;
  temp_auth_token.version = 66;
  temp_auth_token.challenge = 66;

  uint8_t *p_buffer = (uint8_t *)&temp_auth_token;
  uint32_t buffer_length = 66;

  OnExcuteCommand(p_device, command_id, 66, p_buffer, buffer_length);
  *p_output_buffer = p_buffer;
  *p_output_buffer_length = buffer_length;

  return 0;
}

int main() {
  const uint8_t p_in_param[] = {"abc"};
  uint8_t *p_output_buffer = NULL;
  uint32_t out_length = 0;
  AncExcuteCommand(NULL, 33, p_in_param, strlen((const char *)p_in_param) + 1,
                   &p_output_buffer, &out_length);

  printf("AncExcuteCommand p_output_buffer : %d %d %d %d\n", p_output_buffer[0],
         p_output_buffer[1], p_output_buffer[7], p_output_buffer[9]);
  return 0;
}