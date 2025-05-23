#include "dolphin/GBAPriv.h"

s32 GBAReadAsync(s32 chan, u8* dst, u8* status, GBACallback callback) {
    GBAControl* gba;

    gba = &__GBA[chan];

    if (gba->callback != NULL) {
        return 2;
    }

    gba->output[0] = 0x14;
    gba->ptr = dst;
    gba->status = status;
    gba->callback = callback;

    return 0;//__GBATransfer(chan, 1, 5, ReadProc);
}

s32 GBARead(s32 chan, u8* dst, u8* status) {
    s32 tmp;
    GBAControl* gba = &__GBA[chan];
    s32 ret;
    ret = GBAReadAsync(chan, dst, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }

    return __GBASync(chan);
}