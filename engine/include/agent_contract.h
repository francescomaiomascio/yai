#ifndef YAI_AGENT_CONTRACT_H
#define YAI_AGENT_CONTRACT_H

#include <stdint.h>
#include <stdbool.h>

// Capability Bitmask
typedef enum {
    CAP_FS_READ     = 1 << 0,
    CAP_FS_WRITE    = 1 << 1,
    CAP_NET_OUT     = 1 << 2,
    CAP_PROCESS_SPAWN = 1 << 3,
    CAP_LLM_DIRECT  = 1 << 4
} AgentCapability;

typedef struct {
    char agent_id[64];
    uint32_t capabilities; // Bitmask delle CAP_
    uint64_t memory_limit; // Byte massimi allocabili
} AgentContract;

// Verifica se un agente ha il permesso per un'azione
bool yai_contract_check(const char* agent_id, AgentCapability cap);

#endif
