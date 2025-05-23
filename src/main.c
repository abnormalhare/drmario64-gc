typedef signed char s8;
typedef signed short int s16;
typedef signed long s32;
typedef signed long long int s64;
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long u32;
typedef unsigned long long int u64;

typedef struct unkStruct {
    struct unkStruct* unk0;
    struct unkStruct* unk4;
    char unk8;
} unkStruct;

#define NULL 0

u32 OSGetResetCode(void);                             /* extern */
void fn_80006DD8();                                    /* extern */
void fn_800128C4();                                    /* extern */
void fn_80018CD0();                                    /* extern */
void fn_80018D00(int, int);                                /* extern */
void fn_800196A8(int);                                   /* extern */
void fn_8001970C();                                    /* extern */
u32 fn_800489E8();                                  /* extern */

typedef struct unkStruct2 {
    char unk[0x28];
    int unk28;
    int unk2C;
    int unk30;
} unkStruct2;

unkStruct2 lbl_800C6C40;
extern s32 lbl_801F9C08[];

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
