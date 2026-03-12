#include <string.h>

#include "yai/container/state.h"

void yai_container_state_defaults(yai_container_state_t *state) {
  if (!state) {
    return;
  }

  memset(state, 0, sizeof(*state));
  state->lifecycle_state = YAI_CONTAINER_LIFECYCLE_CREATED;
  state->updated_at = 0;
}
