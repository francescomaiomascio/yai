#pragma once

#ifndef INCLUDE_FS_ADMISSION_H
#define INCLUDE_FS_ADMISSION_H

enum yai_fs_admission_result {
    YAI_FS_ADMISSION_UNKNOWN = 0,
    YAI_FS_ADMISSION_ALLOW,
    YAI_FS_ADMISSION_DENY,
    YAI_FS_ADMISSION_DEFER
};

#endif
