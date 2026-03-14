#pragma once

#ifndef INCLUDE_FS_STATE_H
#define INCLUDE_FS_STATE_H

enum yai_fs_state {
    YAI_FS_STATE_UNKNOWN = 0,
    YAI_FS_STATE_MOUNTED,
    YAI_FS_STATE_READONLY,
    YAI_FS_STATE_DEGRADED,
    YAI_FS_STATE_FAILED
};

#endif
