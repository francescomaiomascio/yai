#pragma once

#ifndef INCLUDE_FS_EVENT_RECORD_H
#define INCLUDE_FS_EVENT_RECORD_H

#include <fs/types.h>

struct yai_fs_event_record {
    yai_inode_id_t inode_id;
    const char *action;
    int allowed;
};

#endif
