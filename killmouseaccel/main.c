//
//  main.c
//  killmouseaccel
//
//  Created by Christian Höltje on 9/20/11.
//  This is public domain. The code was originally taken from
//  http://forums3.armagetronad.net/viewtopic.php?t=3364
//

#include <stdio.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <IOKit/hidsystem/IOHIDParameter.h>

int main(int argc, char **argv)
{
    const int32_t accel = -0x10000; // if this ever becomes a scale factor, we set it to one
    if(argc < 2) {
        fprintf(stderr, "Give me mouse and/or trackpad as arguments\n");
        return 1;
    }
    
    io_connect_t handle = NXOpenEventStatus();
    if(handle) {
        int i;
        for(i=1; i<argc; i++) {
            CFStringRef type = 0;
            
            if(strcmp(argv[i], "mouse") == 0)
                type = CFSTR(kIOHIDMouseAccelerationType);
            else if(strcmp(argv[i], "trackpad") == 0)
                type = CFSTR(kIOHIDTrackpadAccelerationType);
            
            if(type && IOHIDSetParameter(handle, type, &accel, sizeof accel) != KERN_SUCCESS)
                fprintf(stderr, "Failed to kill %s accel\n", argv[i]);
        }
        NXCloseEventStatus(handle);
    } else
        fprintf(stderr, "No handle\n");
    
    return 0;
}