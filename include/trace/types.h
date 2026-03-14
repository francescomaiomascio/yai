#pragma once

#ifndef INCLUDE_TRACE_TYPES_H
#define INCLUDE_TRACE_TYPES_H

#include <stdint.h>

typedef uint64_t yai_trace_id_t;
typedef uint64_t yai_trace_record_id_t;
typedef uint64_t yai_trace_session_id_t;

enum yai_trace_kind {
    YAI_TRACE_UNKNOWN = 0,
    YAI_TRACE_RUNTIME,
    YAI_TRACE_POLICY,
    YAI_TRACE_SESSION,
    YAI_TRACE_WORKSPACE,
    YAI_TRACE_AUDIT
};

#endif
