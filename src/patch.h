#pragma once

int patch_wwidth(SRB2Executable* exe, int32 width);
int patch_wheight(SRB2Executable* exe, int32 height);
int patch_pausedtxt(SRB2Executable* exe, char* string);
int patch_wtitle(SRB2Executable* exe, char* string);

void enable_drm(SRB2Executable* exe);
void disable_drm(SRB2Executable* exe);

void enable_iwad_chk(SRB2Executable* exe);
void disable_iwad_chk(SRB2Executable* exe);