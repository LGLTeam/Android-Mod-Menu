#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

// thanks to shmoo and joeyjurjens for the usefull stuff under this comment.

#if defined(__aarch64__) //Compile for arm64 lib only
#include <And64InlineHook/And64InlineHook.hpp>

#define HOOK(offset, ptr, orig) A64HookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define HOOK_LIB(lib, offset, ptr, orig) A64HookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)

#define HOOK_NO_ORIG(offset, ptr) A64HookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)
#define HOOK_LIB_NO_ORIG(lib, offset, ptr) A64HookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)

#define HOOKSYM(sym, ptr, org) A64HookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)
#define HOOKSYM_LIB(lib, sym, ptr, org) A64HookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)

#define HOOKSYM_NO_ORIG(sym, ptr) A64HookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, NULL)
#define HOOKSYM_LIB_NO_ORIG(lib, sym, ptr) A64HookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, NULL)

#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

#define HOOK(offset, ptr, orig) MSHookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define HOOK_LIB(lib, offset, ptr, orig) MSHookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)

#define HOOK_NO_ORIG(offset, ptr) MSHookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)
#define HOOK_LIB_NO_ORIG(lib, offset, ptr) MSHookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)

#define HOOKSYM(sym, ptr, org) MSHookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)
#define HOOKSYM_LIB(lib, sym, ptr, org) MSHookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)

#define HOOKSYM_NO_ORIG(sym, ptr)  MSHookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, NULL)
#define HOOKSYM_LIB_NO_ORIG(lib, sym, ptr)  MSHookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, NULL)

#endif

// Obfuscate offset
#define OBFUSCATEOFFSET(str) string2Offset(OBFUSCATE(str)) // Encrypt offset

// Patching a offset without switch.
void patchOffset(const char *fileName, uint64_t offset, std::string hexBytes) {
    MemoryPatch patch = MemoryPatch::createWithHex(fileName, offset, hexBytes);
    if(!patch.isValid()){
        LOGE(OBFUSCATE("Failing offset: 0x%llu, please re-check the hex you entered."), offset);
        return;
    }
    if(!patch.Modify()) {
        LOGE(OBFUSCATE("Something went wrong while patching this offset: 0x%llu"), offset);
        return;
    }
}

void patchOffset(uint64_t offset, std::string hexBytes) {
    MemoryPatch patch = MemoryPatch::createWithHex(targetLibName, offset, hexBytes);
    if(!patch.isValid()){
        LOGE(OBFUSCATE("Failing offset: 0x%llu, please re-check the hex you entered."), offset);
        return;
    }
    if(!patch.Modify()) {
        LOGE(OBFUSCATE("Something went wrong while patching this offset: 0x%llu"), offset);
        return;
    }
}

#define PATCHOFFSET(offset, hex) patchOffset(string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex))
#define PATCHOFFSET_LIB(lib, offset, hex) patchOffset(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex))

#endif //ANDROID_MOD_MENU_MACROS_H
