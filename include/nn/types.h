#pragma once

#include <types.h>

namespace nn {

#define NN_RESULT_SIZE_DESCRIPTION    0x00000014
#define NN_RESULT_SIZE_MODULE         0x00000009
#define NN_RESULT_SIZE_LVL            0x00000003

#define NN_RESULT_SHIFTS_DESCRIPTION  0x00000000
#define NN_RESULT_SHIFTS_MODULE       0x00000014
#define NN_RESULT_SHIFTS_LEVEL        0x0000001D

#define NN_RESULT_MASK_DESCRIPTION    0x000FFFFFU
#define NN_RESULT_MASK_MODULE         0x000FFFFFU
#define NN_RESULT_MASK_LEVEL          0xE0000000U
#define NN_RESULT_MASK_FAILURE        0x80000000U

#define NN_RESULT_MAX_DESCRIPTION     0x000FFFFF
#define NN_RESULT_MAX_MODULE          0x000001FF
#define NN_RESULT_MAX_LEVEL           0x00000007

class Result {
public:
    enum Level {
        Level_Success = 0,
        Level_Fatal   = -1,
        Level_Usage   = -2,
        Level_Status  = -3,
        Level_End     = -7
    };

public:
    Result()
        : code((NN_RESULT_MAX_LEVEL << NN_RESULT_SHIFTS_LEVEL) & NN_RESULT_MASK_LEVEL | (NN_RESULT_MAX_MODULE << NN_RESULT_SHIFTS_MODULE) & NN_RESULT_MASK_MODULE | NN_RESULT_MAX_DESCRIPTION & NN_RESULT_MASK_DESCRIPTION)
    { }

    Result(u32 code)
        : code(code)
    { }

    Result(Level level, u32 module, u32 description)
        : code((level << NN_RESULT_SHIFTS_LEVEL) & NN_RESULT_MASK_LEVEL | (module << NN_RESULT_SHIFTS_MODULE) & NN_RESULT_MASK_MODULE | description & NN_RESULT_MASK_DESCRIPTION)
    { }

    inline u32 getDescription() const { return this->getCodeBits(NN_RESULT_MASK_DESCRIPTION, NN_RESULT_SHIFTS_DESCRIPTION); }
    inline u32 getModule() const { return this->getCodeBits(NN_RESULT_MASK_MODULE, NN_RESULT_SHIFTS_MODULE); }
    inline u32 getLevel() const { return this->getCodeBits(NN_RESULT_MASK_LEVEL, NN_RESULT_SHIFTS_LEVEL); }

    inline bool isFailure() const { return (this->code & NN_RESULT_MASK_FAILURE) != 0; }
    inline bool isSuccess() const { return !this->isFailure(); }

    bool operator==(const Result& rhs) const { return this->code == rhs.code; }
    bool operator!=(const Result& rhs) const { return this->code != rhs.code; }

private:
    inline u32 getCodeBits(u32 mask, s32 shift) const { return (this->code & mask) >> shift; }

    u32 code;
};

}