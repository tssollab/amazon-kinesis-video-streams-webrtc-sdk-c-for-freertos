# amazon-kinesis-video-streams-webrtc-sdk-c-for-freertos

This project demonstrate how to port [Amazon Kinesis Video WebRTC C SDK](https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-c) to FreeRTOS.  It uses the [Sky39AV100_SDK_freertos_V0.01] as a reference platform.  You may follow the same procedure to port to other hardware platforms.

## Clone projects

Please git clone this project using the command below.  This will git sub-module all depended submodules under main/lib.

```
git submodule update --init --recursive
```

## Reference platform

We use [Sky39AV100_SDK_freertos_V0.01]

## Apply patches

Next, patch depended libraries for using with WebRTC.

### [wslay](https://github.com/tatsuhiro-t/wslay)

This project uses wslay as the websocket client. Please apply patches located in patch/wslay directory.

```
main/lib/wslay$ git am ../../../patch/wslay/*
```

### [libsrtp](https://github.com/cisco/libsrtp/releases/tag/v2.3.0)

This project uses v2.3.0 of libsrtp.  Please apply patches located in patch/libsrtp directory.

```
main/lib/libsrtp$ git am ../../../patch/libsrtp/*
```

### [mbedtls](https://github.com/Mbed-TLS/mbedtls/tree/v3.2.1)

```
main/lib/mbedtls$ git am ../../../patch/mbedtls/*
```

### [usrsctp](https://github.com/sctplab/usrsctp/commit/939d48f9632d69bf170c7a84514b312b6b42257d)

Please apply patches as below.

```
main/lib/usrsctp$ git am ../../../patch/usrsctp/*
```

## Configure the project

Use menuconfig of ESP IDF to configure the project.

```
./build.sh
```

### Video source

This project uses pre-recorded h.264 frame files for video streaming.  Please put the files on a SD card.  The files should look like:

/sdcard/h264SampleFrames/frame-%04d.h264. 

 The “%04d” part of the file name should be replaced by a sequence number of the frame.

Please note that you can not use J-TAG and SD card simultaneously on ESP-Wrover-Kit because they share some pins.

[Generate video source](https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-c/blob/master/samples/h264SampleFrames/README.md)

Given a video file videotestsrc,  the following GStreamer command generates video frame files. If you want to reduce the number of video files, please modify related setting in sample code.



```
sh
gst-launch-1.0 videotestsrc pattern=ball num-buffers=1500 ! timeoverlay ! videoconvert ! video/x-raw,format=I420,width=1280,height=720,framerate=5/1 ! queue ! x264enc bframes=0 speed-preset=veryfast bitrate=128 byte-stream=TRUE tune=zerolatency ! video/x-h264,stream-format=byte-stream,alignment=au,profile=baseline ! multifilesink location="frame-%04d.h264" index=1
```

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type `Ctrl-]`.)

See the Getting Started Guide of ESP IDF for full steps to configure and use ESP-IDF to build projects.

### Known limitations and issues

This project does not use audio at this point of time. When running on the ESP-Wrover-Kit, this project can only run at low frame rate and low bit rate.  

The current implementation does not support data channel. Please check back later for availability of the data channel feature.

**[The m-line mismatch](https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-c/issues/803)**

When using the [WebRTC SDK Test Page](https://awslabs.github.io/amazon-kinesis-video-streams-webrtc-sdk-js/examples/index.html) to validate the demo, you may get m-line mismatch errors.  Different browsers have different behaviors.  To work around such errors, you need to run the [sample](https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-js/#Development) in [amazon-kinesis-video-streams-webrtc-sdk-js](https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-js), and disable audio functionality of audio. This patch disables the audio functionality.  A later release of this project may eliminate the need for this.

patch/amazon-kinesis-video-streams-webrtc-sdk-js/0001-diable-offerToReceiveAudio.patch`

## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This project is licensed under the Apache-2.0 License.

