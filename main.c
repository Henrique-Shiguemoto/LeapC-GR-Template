/* Copyright (C) 2012-2017 Ultraleap Limited. All rights reserved.
 *
 * Use of this code is subject to the terms of the Ultraleap SDK agreement
 * available at https://central.leapmotion.com/agreements/SdkAgreement unless
 * Ultraleap has signed a separate license agreement with you or your
 * organisation.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "LeapC.h"
#include "connection.h"
#include "mthlib.h"

#define MAX_FRAMES 249

int64_t lastFrameID = 0; //The last frame received
int32_t gestureClass = 0;

int main(int argc, char** argv) {
    OpenConnection();
    while (!IsConnected)
        millisleep(100); //wait a bit to let the connection complete

    printf("Connected.");
    LEAP_DEVICE_INFO* deviceProps = GetDeviceProperties();
    if (deviceProps)
        printf("Using device %s.\n", deviceProps->serial);

    FILE* csvFile;
    fopen_s(&csvFile, "dataset.csv", "w");

    if (csvFile == NULL) {
        printf("There was an error while creating the file...\n");
        return 1;
    }

    int frameCounter = 0;
    for (;;) {
        LEAP_TRACKING_EVENT* frame = GetFrame();
        if (frame && (frame->tracking_frame_id > lastFrameID)) {
            lastFrameID = frame->tracking_frame_id;
            printf("Frame %d\n", frameCounter);
            for (uint32_t h = 0; h < frame->nHands; h++) {
                LEAP_HAND* hand = &frame->pHands[h];
                
                //Finger 3D Positions
                v3 thumbTipPosition = { hand->thumb.distal.next_joint.x, hand->thumb.distal.next_joint.y, hand->thumb.distal.next_joint.z};
                v3 indexTipPosition = { hand->index.distal.next_joint.x, hand->index.distal.next_joint.y, hand->index.distal.next_joint.z};
                v3 middleTipPosition = { hand->middle.distal.next_joint.x, hand->middle.distal.next_joint.y, hand->middle.distal.next_joint.z};
                v3 ringTipPosition = { hand->ring.distal.next_joint.x, hand->ring.distal.next_joint.y, hand->ring.distal.next_joint.z};
                v3 pinkyTipPosition = { hand->pinky.distal.next_joint.x, hand->pinky.distal.next_joint.y, hand->pinky.distal.next_joint.z};
                v3 palmCenterPosition = { hand->palm.position.x, hand->palm.position.y, hand->palm.position.z};

                //Distance between fingers and palm center
                f32 distanceBetweenThumbAndPalmCenter = DistanceBetweenPoints3D(palmCenterPosition, thumbTipPosition) / 200.0f;
                f32 distanceBetweenIndexAndPalmCenter = DistanceBetweenPoints3D(palmCenterPosition, indexTipPosition) / 200.0f;
                f32 distanceBetweenMiddleAndPalmCenter = DistanceBetweenPoints3D(palmCenterPosition, middleTipPosition) / 200.0f;
                f32 distanceBetweenRingAndPalmCenter = DistanceBetweenPoints3D(palmCenterPosition, ringTipPosition) / 200.0f;
                f32 distanceBetweenPinkyAndPalmCenter = DistanceBetweenPoints3D(palmCenterPosition, pinkyTipPosition) / 200.0f;

                fprintf(csvFile, "%d,%f,%f,%f,%f,%f\n", 
                    gestureClass,
                    distanceBetweenThumbAndPalmCenter,
                    distanceBetweenIndexAndPalmCenter, 
                    distanceBetweenMiddleAndPalmCenter, 
                    distanceBetweenRingAndPalmCenter, 
                    distanceBetweenPinkyAndPalmCenter);
                
                if (ferror(csvFile)) {
                    printf("Error while writing to file...\n");
                    return 1;
                }
                if (frameCounter >= MAX_FRAMES) goto exit;
                frameCounter++;
            }
        }
    }

exit:
    fclose(csvFile);
    return 0;
}
