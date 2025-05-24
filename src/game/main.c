#include <types.h>

extern s32 lbl_801F9C08[];

u32 OSGetResetCode(void);
void fn_80006D04(s32);
void fn_80006CF4();
void fn_80006DD8();
s32 fn_80012854();
void fn_800128C4();
s32 fn_800158C4();
void fn_800160CC(s32, s32, s32, s32);
s32 fn_800160FC();
void fn_80018CD0();
void fn_80018D00(int, int);
void fn_800196A8(int);
void fn_8001970C();
void fn_80019D00();
void fn_8001A22C();
u32 fn_800489E8();

typedef struct unkStruct2 {
    char unk[0x28];
    int unk28;
    int unk2C;
    int unk30;
} unkStruct2;

unkStruct2 lbl_800C6C40;
const char *lbl_8006A880[] = {
    "/menu_relsamp.bin",
    "/Dr_MARIO.rel",
    "/panepon.rel",
    "/ycookie.rel",
};
const char *lbl_8006A890[] = {
    "/menu_relsamp.szp",
    "/Dr_MARIO.szp",
    "/panepon.szp",
    "/ycookie.szp",
};

s32 lbl_800BDD38[2] = { 1, 0 };

int main(void) {
    s32 var_r30;
    unkStruct2* var_r31;

    var_r31 = &lbl_800C6C40;
    
    var_r31->unk28 = var_r30 = 0;
    if ((OSGetResetCode() + 0x80000000) == 0) {
        var_r30 = 1;
    }
    var_r31->unk2C = var_r30;
    var_r30 = 0;
    if ((var_r31->unk2C != 0) && (fn_800489E8() == 1)) {
        var_r30 = 1;
    }
    var_r31->unk30 = var_r30;
    fn_800128C4();
    fn_80018CD0();
    fn_80018D00(1, 0);
    fn_80018D00(7, 0);
    lbl_801F9C08[0] = 1;
    fn_800196A8(1);
    fn_8001970C();
    fn_80006DD8();
    
    return 0;
}

s32 fn_80006838(s32 arg0) {
    s32 var_r31;

    fn_800160CC(arg0, 0, 0, 0);
    while (1) {
        var_r31 = fn_800158C4();
        if (var_r31 == 0x28) {
            fn_800160CC(arg0, 0, 0, 0);
            var_r31 = 0x24;
        }
        fn_80006D04(var_r31);
        if (var_r31 == 36) {
            if (fn_80012854() == 0) {
                fn_8001A22C();
                continue;
            }
            fn_80019D00();
            if (fn_80012854() != 0x18) {
                continue;
            }
            while (1) {}
        } else if (var_r31 != 0) {
            return 0;
        } else {
            return fn_800160FC();
        }
    }
}

void fn_80006968(void) {
    fn_80006CF4();
    lbl_800BDD38[0] = 0;
}
