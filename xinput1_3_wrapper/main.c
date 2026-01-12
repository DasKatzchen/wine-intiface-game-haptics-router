/*
 * The Wine project - Xinput Joystick Library
 * Copyright 2008 Andrew Fenn
 * Copyright 2018 Aric Stewart
 * Copyright 2021 Rémi Bernon for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <fcntl.h>
#include <unistd.h>

#include "xinput.h"

WINE_DEFAULT_DEBUG_CHANNEL(xinput);

static int v1l;
static int v1r;
static int v2l;
static int v2r;
static int v3l;
static int v3r;
static int v4l;
static int v4r;
//static void* handle;

void __attribute__ ((constructor)) hook_init(void)
{
    //handle = dlopen("xinput1_3.dll",RTLD_LAZY);
    v1l=open("/tmp/vibe/1/left", O_WRONLY);
    v1r=open("/tmp/vibe/1/right", O_WRONLY);
    v2l=open("/tmp/vibe/2/left", O_WRONLY);
    v2r=open("/tmp/vibe/2/right", O_WRONLY);
    v3l=open("/tmp/vibe/3/left", O_WRONLY);
    v3r=open("/tmp/vibe/3/right", O_WRONLY);
    v4l=open("/tmp/vibe/4/left", O_WRONLY);
    v4r=open("/tmp/vibe/4/right", O_WRONLY);
}

void __attribute__ ((destructor)) hook_fini(void)
{
    close(v1l);
    close(v1r);
    close(v2l);
    close(v2r);
    close(v3l);
    close(v3r);
    close(v4l);
    close(v4r);
}

//BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)
//{
//    TRACE("xinput1_3.dll hook, inst %p, reason %lu, reserved %p.\n", inst, reason, reserved);
//
//    handle = dlopen("xinput1_3.dll",RTLD_LAZY);
//    void* (*origDllMain)(HINSTANCE inst, DWORD reason, LPVOID reserved) = dlsym(handle,"DllMain");
//
//    switch (reason)
//    {
//        case DLL_PROCESS_ATTACH:
//            v1l=open("/tmp/vibe/1/left", O_WRONLY);
//            v1r=open("/tmp/vibe/1/right", O_WRONLY);
//            v2l=open("/tmp/vibe/2/left", O_WRONLY);
//            v2r=open("/tmp/vibe/2/right", O_WRONLY);
//            v3l=open("/tmp/vibe/3/left", O_WRONLY);
//            v3r=open("/tmp/vibe/3/right", O_WRONLY);
//            v4l=open("/tmp/vibe/4/left", O_WRONLY);
//            v4r=open("/tmp/vibe/4/right", O_WRONLY);
//            break;
//        case DLL_PROCESS_DETACH:
//            close(v1l);
//            close(v1r);
//            close(v2l);
//            close(v2r);
//            close(v3l);
//            close(v3r);
//            close(v4l);
//            close(v4r);
//            break;
//    }
//    return origDllMain(inst, reason, reserved);
//}

DWORD WINAPI DECLSPEC_HOTPATCH XInputSetState(DWORD index, XINPUT_VIBRATION *vibration)
{

    //void* (*origXInputSetState)(DWORD index, XINPUT_VIBRATION *vibration) = dlsym(handle,"XInputSetState");
    void* (*origXInputSetState)(DWORD index, XINPUT_VIBRATION *vibration) = dlsym(RTLD_NEXT,"XInputSetState");

    TRACE("xinput1_3.dll hook, index %lu, vibration %p.\n", index, vibration);

    switch (index)
    {
        case 0x00:
            if(v1l!=-1) write(v1l, &vibration->wLeftMotorSpeed, sizeof(WORD));
            if(v1r!=-1) write(v1r, &vibration->wRightMotorSpeed, sizeof(WORD));
            break;
        case 0x01:
            if(v2l!=-1) write(v1l, &vibration->wLeftMotorSpeed, sizeof(WORD));
            if(v2r!=-1) write(v1r, &vibration->wRightMotorSpeed, sizeof(WORD));
            break;
        case 0x02:
            if(v3l!=-1) write(v1l, &vibration->wLeftMotorSpeed, sizeof(WORD));
            if(v3r!=-1) write(v1r, &vibration->wRightMotorSpeed, sizeof(WORD));
            break;
        case 0x03:
            if(v4l!=-1) write(v1l, &vibration->wLeftMotorSpeed, sizeof(WORD));
            if(v4r!=-1) write(v1r, &vibration->wRightMotorSpeed, sizeof(WORD));
            break;
    }

    return origXInputSetState(index, vibration);

}
