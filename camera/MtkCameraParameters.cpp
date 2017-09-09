/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "MTKCameraParams"
#include <utils/Log.h>

#include <string.h>
#include <stdlib.h>
#include "MtkCameraParameters.h"
#include <system/graphics.h>

namespace android {
// Parameter keys to communicate between camera application and driver.
const char CameraParameters::KEY_PREVIEW_SIZE[] = "preview-size";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES[] = "preview-size-values";
const char CameraParameters::KEY_PREVIEW_FORMAT[] = "preview-format";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS[] = "preview-format-values";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE[] = "preview-frame-rate";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES[] = "preview-frame-rate-values";
const char CameraParameters::KEY_PREVIEW_FPS_RANGE[] = "preview-fps-range";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE[] = "preview-fps-range-values";
const char CameraParameters::KEY_PICTURE_SIZE[] = "picture-size";
const char CameraParameters::KEY_SUPPORTED_PICTURE_SIZES[] = "picture-size-values";
const char CameraParameters::KEY_PICTURE_FORMAT[] = "picture-format";
const char CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS[] = "picture-format-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH[] = "jpeg-thumbnail-width";
const char CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT[] = "jpeg-thumbnail-height";
const char CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES[] = "jpeg-thumbnail-size-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY[] = "jpeg-thumbnail-quality";
const char CameraParameters::KEY_JPEG_QUALITY[] = "jpeg-quality";
const char CameraParameters::KEY_ROTATION[] = "rotation";
const char CameraParameters::KEY_GPS_LATITUDE[] = "gps-latitude";
const char CameraParameters::KEY_GPS_LONGITUDE[] = "gps-longitude";
const char CameraParameters::KEY_GPS_ALTITUDE[] = "gps-altitude";
const char CameraParameters::KEY_GPS_TIMESTAMP[] = "gps-timestamp";
const char CameraParameters::KEY_GPS_PROCESSING_METHOD[] = "gps-processing-method";
const char CameraParameters::KEY_WHITE_BALANCE[] = "whitebalance";
const char CameraParameters::KEY_SUPPORTED_WHITE_BALANCE[] = "whitebalance-values";
const char CameraParameters::KEY_EFFECT[] = "effect";
const char CameraParameters::KEY_SUPPORTED_EFFECTS[] = "effect-values";
const char CameraParameters::KEY_ANTIBANDING[] = "antibanding";
const char CameraParameters::KEY_SUPPORTED_ANTIBANDING[] = "antibanding-values";
const char CameraParameters::KEY_SCENE_MODE[] = "scene-mode";
const char CameraParameters::KEY_SUPPORTED_SCENE_MODES[] = "scene-mode-values";
const char CameraParameters::KEY_FLASH_MODE[] = "flash-mode";
const char CameraParameters::KEY_SUPPORTED_FLASH_MODES[] = "flash-mode-values";
const char CameraParameters::KEY_FOCUS_MODE[] = "focus-mode";
const char CameraParameters::KEY_SUPPORTED_FOCUS_MODES[] = "focus-mode-values";
const char CameraParameters::KEY_MAX_NUM_FOCUS_AREAS[] = "max-num-focus-areas";
const char CameraParameters::KEY_FOCUS_AREAS[] = "focus-areas";
const char CameraParameters::KEY_FOCAL_LENGTH[] = "focal-length";
const char CameraParameters::KEY_HORIZONTAL_VIEW_ANGLE[] = "horizontal-view-angle";
const char CameraParameters::KEY_VERTICAL_VIEW_ANGLE[] = "vertical-view-angle";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION[] = "exposure-compensation";
const char CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION[] = "max-exposure-compensation";
const char CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION[] = "min-exposure-compensation";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP[] = "exposure-compensation-step";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK[] = "auto-exposure-lock";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK_SUPPORTED[] = "auto-exposure-lock-supported";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK[] = "auto-whitebalance-lock";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK_SUPPORTED[] = "auto-whitebalance-lock-supported";
const char CameraParameters::KEY_MAX_NUM_METERING_AREAS[] = "max-num-metering-areas";
const char CameraParameters::KEY_METERING_AREAS[] = "metering-areas";
const char CameraParameters::KEY_ZOOM[] = "zoom";
const char CameraParameters::KEY_MAX_ZOOM[] = "max-zoom";
const char CameraParameters::KEY_ZOOM_RATIOS[] = "zoom-ratios";
const char CameraParameters::KEY_ZOOM_SUPPORTED[] = "zoom-supported";
const char CameraParameters::KEY_SMOOTH_ZOOM_SUPPORTED[] = "smooth-zoom-supported";
const char CameraParameters::KEY_FOCUS_DISTANCES[] = "focus-distances";
const char CameraParameters::KEY_VIDEO_FRAME_FORMAT[] = "video-frame-format";
const char CameraParameters::KEY_VIDEO_SIZE[] = "video-size";
const char CameraParameters::KEY_SUPPORTED_VIDEO_SIZES[] = "video-size-values";
const char CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO[] = "preferred-preview-size-for-video";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_HW[] = "max-num-detected-faces-hw";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_SW[] = "max-num-detected-faces-sw";
const char CameraParameters::KEY_RECORDING_HINT[] = "recording-hint";
const char CameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED[] = "video-snapshot-supported";
const char CameraParameters::KEY_VIDEO_STABILIZATION[] = "video-stabilization";
const char CameraParameters::KEY_VIDEO_STABILIZATION_SUPPORTED[] = "video-stabilization-supported";
const char CameraParameters::KEY_LIGHTFX[] = "light-fx";

const char CameraParameters::TRUE[] = "true";
const char CameraParameters::FALSE[] = "false";
const char CameraParameters::FOCUS_DISTANCE_INFINITY[] = "Infinity";

// Values for white balance settings.
const char CameraParameters::WHITE_BALANCE_AUTO[] = "auto";
const char CameraParameters::WHITE_BALANCE_INCANDESCENT[] = "incandescent";
const char CameraParameters::WHITE_BALANCE_FLUORESCENT[] = "fluorescent";
const char CameraParameters::WHITE_BALANCE_WARM_FLUORESCENT[] = "warm-fluorescent";
const char CameraParameters::WHITE_BALANCE_DAYLIGHT[] = "daylight";
const char CameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT[] = "cloudy-daylight";
const char CameraParameters::WHITE_BALANCE_TWILIGHT[] = "twilight";
const char CameraParameters::WHITE_BALANCE_SHADE[] = "shade";

// Values for effect settings.
const char CameraParameters::EFFECT_NONE[] = "none";
const char CameraParameters::EFFECT_MONO[] = "mono";
const char CameraParameters::EFFECT_NEGATIVE[] = "negative";
const char CameraParameters::EFFECT_SOLARIZE[] = "solarize";
const char CameraParameters::EFFECT_SEPIA[] = "sepia";
const char CameraParameters::EFFECT_POSTERIZE[] = "posterize";
const char CameraParameters::EFFECT_WHITEBOARD[] = "whiteboard";
const char CameraParameters::EFFECT_BLACKBOARD[] = "blackboard";
const char CameraParameters::EFFECT_AQUA[] = "aqua";

// Values for antibanding settings.
const char CameraParameters::ANTIBANDING_AUTO[] = "auto";
const char CameraParameters::ANTIBANDING_50HZ[] = "50hz";
const char CameraParameters::ANTIBANDING_60HZ[] = "60hz";
const char CameraParameters::ANTIBANDING_OFF[] = "off";

// Values for flash mode settings.
const char CameraParameters::FLASH_MODE_OFF[] = "off";
const char CameraParameters::FLASH_MODE_AUTO[] = "auto";
const char CameraParameters::FLASH_MODE_ON[] = "on";
const char CameraParameters::FLASH_MODE_RED_EYE[] = "red-eye";
const char CameraParameters::FLASH_MODE_TORCH[] = "torch";

// Values for scene mode settings.
const char CameraParameters::SCENE_MODE_AUTO[] = "auto";
const char CameraParameters::SCENE_MODE_ACTION[] = "action";
const char CameraParameters::SCENE_MODE_PORTRAIT[] = "portrait";
const char CameraParameters::SCENE_MODE_LANDSCAPE[] = "landscape";
const char CameraParameters::SCENE_MODE_NIGHT[] = "night";
const char CameraParameters::SCENE_MODE_NIGHT_PORTRAIT[] = "night-portrait";
const char CameraParameters::SCENE_MODE_THEATRE[] = "theatre";
const char CameraParameters::SCENE_MODE_BEACH[] = "beach";
const char CameraParameters::SCENE_MODE_SNOW[] = "snow";
const char CameraParameters::SCENE_MODE_SUNSET[] = "sunset";
const char CameraParameters::SCENE_MODE_STEADYPHOTO[] = "steadyphoto";
const char CameraParameters::SCENE_MODE_FIREWORKS[] = "fireworks";
const char CameraParameters::SCENE_MODE_SPORTS[] = "sports";
const char CameraParameters::SCENE_MODE_PARTY[] = "party";
const char CameraParameters::SCENE_MODE_CANDLELIGHT[] = "candlelight";
const char CameraParameters::SCENE_MODE_BARCODE[] = "barcode";
const char CameraParameters::SCENE_MODE_HDR[] = "hdr";

// Values for light fx settings
const char CameraParameters::LIGHTFX_LOWLIGHT[] = "low-light";
const char CameraParameters::LIGHTFX_HDR[] = "high-dynamic-range";

///////////////////////////Mediatek Custom Parameters///////////////////////////

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  App Mode.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const char MtkCameraParameters::PROPERTY_KEY_CLIENT_APPMODE[]   = "client.appmode";
//
const char MtkCameraParameters::APP_MODE_NAME_DEFAULT[]         = "Default";
const char MtkCameraParameters::APP_MODE_NAME_MTK_ENG[]         = "MtkEng";
const char MtkCameraParameters::APP_MODE_NAME_MTK_ATV[]         = "MtkAtv";
const char MtkCameraParameters::APP_MODE_NAME_MTK_S3D[]         = "MtkS3d";
const char MtkCameraParameters::APP_MODE_NAME_MTK_VT[]          = "MtkVt";
const char MtkCameraParameters::APP_MODE_NAME_MTK_PHOTO[]       = "MtkPhoto";
const char MtkCameraParameters::APP_MODE_NAME_MTK_VIDEO[]       = "MtkVideo";
const char MtkCameraParameters::APP_MODE_NAME_MTK_ZSD[]         = "MtkZsd";

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Scene Mode
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const char MtkCameraParameters::SCENE_MODE_NORMAL[] = "normal";

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Face Beauty
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const char MtkCameraParameters::KEY_FB_SMOOTH_LEVEL[]       = "fb-smooth-level";
const char MtkCameraParameters::KEY_FB_SMOOTH_LEVEL_MIN[]   = "fb-smooth-level-min";
const char MtkCameraParameters::KEY_FB_SMOOTH_LEVEL_MAX[]   = "fb-smooth-level-max";
//
const char MtkCameraParameters::KEY_FB_SKIN_COLOR[]         = "fb-skin-color";
const char MtkCameraParameters::KEY_FB_SKIN_COLOR_MIN[]     = "fb-skin-color-min";
const char MtkCameraParameters::KEY_FB_SKIN_COLOR_MAX[]     = "fb-skin-color-max";
//
const char MtkCameraParameters::KEY_FB_SHARP[]              = "fb-sharp";
const char MtkCameraParameters::KEY_FB_SHARP_MIN[]          = "fb-sharp-min";
const char MtkCameraParameters::KEY_FB_SHARP_MAX[]          = "fb-sharp-max";
//
const char MtkCameraParameters::KEY_FB_ENLARGE_EYE[]        = "fb-enlarge-eye";
const char MtkCameraParameters::KEY_FB_ENLARGE_EYE_MIN[]    = "fb-enlarge-eye-min";
const char MtkCameraParameters::KEY_FB_ENLARGE_EYE_MAX[]    = "fb-enlarge-eye-max";
//
const char MtkCameraParameters::KEY_FB_SLIM_FACE[]          = "fb-slim-face";
const char MtkCameraParameters::KEY_FB_SLIM_FACE_MIN[]      = "fb-slim-face-min";
const char MtkCameraParameters::KEY_FB_SLIM_FACE_MAX[]      = "fb-slim-face-max";
//
const char MtkCameraParameters::KEY_FB_EXTREME_BEAUTY[]     = "fb-extreme-beauty";
//
const char MtkCameraParameters::KEY_FACE_BEAUTY[]           = "face-beauty";


//
const char MtkCameraParameters::KEY_EXPOSURE[] = "exposure";
const char MtkCameraParameters::KEY_EXPOSURE_METER[] = "exposure-meter";
const char MtkCameraParameters::KEY_ISO_SPEED[] = "iso-speed";
const char MtkCameraParameters::KEY_AE_MODE[] = "ae-mode";

// Values for focus mode settings.
const char CameraParameters::FOCUS_MODE_AUTO[] = "auto";
const char CameraParameters::FOCUS_MODE_INFINITY[] = "infinity";
const char CameraParameters::FOCUS_MODE_MACRO[] = "macro";
const char CameraParameters::FOCUS_MODE_FIXED[] = "fixed";
const char CameraParameters::FOCUS_MODE_EDOF[] = "edof";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_VIDEO[] = "continuous-video";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_PICTURE[] = "continuous-picture";
const char MtkCameraParameters::KEY_FOCUS_METER[] = "focus-meter";


const char MtkCameraParameters::KEY_EDGE[] = "edge";
const char MtkCameraParameters::KEY_HUE[] = "hue";
const char MtkCameraParameters::KEY_SATURATION[] = "saturation";
const char MtkCameraParameters::KEY_BRIGHTNESS[] = "brightness";
const char MtkCameraParameters::KEY_CONTRAST[] = "contrast";
const char MtkCameraParameters::KEY_AF_LAMP_MODE [] = "aflamp-mode";
const char MtkCameraParameters::KEY_STEREO_3D_PREVIEW_SIZE[] = "stereo3d-preview-size";
const char MtkCameraParameters::KEY_STEREO_3D_PICTURE_SIZE[] = "stereo3d-picture-size";
const char MtkCameraParameters::KEY_STEREO_3D_TYPE [] = "stereo3d-type";
const char MtkCameraParameters::KEY_STEREO_3D_MODE [] = "stereo3d-mode";
const char MtkCameraParameters::KEY_STEREO_3D_IMAGE_FORMAT [] = "stereo3d-image-format";

// ZSD
const char MtkCameraParameters::KEY_ZSD_MODE[] = "zsd-mode"; 
const char MtkCameraParameters::KEY_SUPPORTED_ZSD_MODE[] = "zsd-supported";
//
const char MtkCameraParameters::KEY_FPS_MODE[] = "fps-mode";
//
const char MtkCameraParameters::KEY_FOCUS_DRAW[] = "af-draw";
//
const char MtkCameraParameters::KEY_CAPTURE_MODE[] = "cap-mode";
const char MtkCameraParameters::KEY_SUPPORTED_CAPTURE_MODES[] = "cap-mode-values";
const char MtkCameraParameters::KEY_CAPTURE_PATH[] = "capfname";
const char MtkCameraParameters::KEY_BURST_SHOT_NUM[] = "burst-num";
//
const char MtkCameraParameters::KEY_MATV_PREVIEW_DELAY[] = "tv-delay";
const char MtkCameraParameters::KEY_PANORAMA_IDX[] = "pano-idx";
const char MtkCameraParameters::KEY_PANORAMA_DIR[] = "pano-dir";

// Values for KEY_EXPOSURE
const char MtkCameraParameters::EXPOSURE_METER_SPOT[] = "spot";
const char MtkCameraParameters::EXPOSURE_METER_CENTER[] = "center";
const char MtkCameraParameters::EXPOSURE_METER_AVERAGE[] = "average";

// Valeus for KEY_ISO_SPEED
const char MtkCameraParameters::ISO_SPEED_AUTO[] = "auto";
const char MtkCameraParameters::ISO_SPEED_100[] = "100";
const char MtkCameraParameters::ISO_SPEED_200[] = "200";
const char MtkCameraParameters::ISO_SPEED_400[] = "400";
const char MtkCameraParameters::ISO_SPEED_800[] = "800";
const char MtkCameraParameters::ISO_SPEED_1600[] = "1600";

// Values for KEY_AE_MODE = "ae-mode"

// Values for KEY_FOCUS_METER
const char MtkCameraParameters::FOCUS_METER_SPOT[] = "spot";
const char MtkCameraParameters::FOCUS_METER_MULTI[] = "multi";

// AWB2PASS
const char MtkCameraParameters::KEY_AWB2PASS[] = "awb-2pass"; 


//
//  Camera Mode
const char MtkCameraParameters::KEY_CAMERA_MODE[] = "mtk-cam-mode";
// Values for KEY_CAMERA_MODE
const int MtkCameraParameters::CAMERA_MODE_NORMAL  = 0;
const int MtkCameraParameters::CAMERA_MODE_MTK_PRV = 1;
const int MtkCameraParameters::CAMERA_MODE_MTK_VDO = 2;
const int MtkCameraParameters::CAMERA_MODE_MTK_VT  = 3;

// Values for KEY_FPS_MODE
const int MtkCameraParameters::FPS_MODE_NORMAL = 0;
const int MtkCameraParameters::FPS_MODE_FIX = 1;

// Values for raw save mode

// Values for KEY_FOCUS_DRAW

// Values for capture mode
const char MtkCameraParameters::CAPTURE_MODE_PANORAMA_SHOT[] = "panoramashot";
const char MtkCameraParameters::CAPTURE_MODE_BURST_SHOT[] = "burstshot";
const char MtkCameraParameters::CAPTURE_MODE_NORMAL[] = "normal";
const char MtkCameraParameters::CAPTURE_MODE_BEST_SHOT[] = "bestshot";
const char MtkCameraParameters::CAPTURE_MODE_EV_BRACKET_SHOT[] = "evbracketshot";
const char MtkCameraParameters::CAPTURE_MODE_SMILE_SHOT[] = "smileshot";
const char MtkCameraParameters::CAPTURE_MODE_MAV_SHOT[] = "mav"; 
const char MtkCameraParameters::CAPTURE_MODE_AUTO_PANORAMA_SHOT[] = "autorama"; 
const char MtkCameraParameters::CAPTURE_MODE_MOTION_TRACK_SHOT[] = "motiontrack"; 
const char MtkCameraParameters::CAPTURE_MODE_HDR_SHOT[] = "hdr"; 
const char MtkCameraParameters::CAPTURE_MODE_ASD_SHOT[] = "asd"; 
const char MtkCameraParameters::CAPTURE_MODE_ZSD_SHOT[] = "zsd";
const char MtkCameraParameters::CAPTURE_MODE_PANO_3D[] = "pano_3d"; 
const char MtkCameraParameters::CAPTURE_MODE_SINGLE_3D[] = "single_3d"; 
const char MtkCameraParameters::CAPTURE_MODE_FACE_BEAUTY[] = "face_beauty"; 
const char MtkCameraParameters::CAPTURE_MODE_CONTINUOUS_SHOT[] = "continuousshot";
const char MtkCameraParameters::CAPTURE_MODE_MULTI_MOTION[] = "multi_motion";
const char MtkCameraParameters::CAPTURE_MODE_GESTURE_SHOT[] = "gestureshot";

// Values for panorama direction settings
const char MtkCameraParameters::PANORAMA_DIR_RIGHT[] = "right";
const char MtkCameraParameters::PANORAMA_DIR_LEFT[] = "left";
const char MtkCameraParameters::PANORAMA_DIR_TOP[] = "top";
const char MtkCameraParameters::PANORAMA_DIR_DOWN[] = "down";

//
const int MtkCameraParameters::ENABLE = 1;
const int MtkCameraParameters::DISABLE = 0;

// Values for KEY_EDGE, KEY_HUE, KEY_SATURATION, KEY_BRIGHTNESS, KEY_CONTRAST
const char MtkCameraParameters::HIGH[] = "high";
const char MtkCameraParameters::MIDDLE[] = "middle";
const char MtkCameraParameters::LOW[] = "low";

// Preview Internal Format.
const char MtkCameraParameters::KEY_PREVIEW_INT_FORMAT[] = "prv-int-fmt";

// Pixel color formats for KEY_PREVIEW_FORMAT, KEY_PICTURE_FORMAT,
// and KEY_VIDEO_FRAME_FORMAT
const char MtkCameraParameters::PIXEL_FORMAT_BAYER8[] = "bayer8"; 
const char MtkCameraParameters::PIXEL_FORMAT_BAYER10[] = "bayer10";
const char MtkCameraParameters::PIXEL_FORMAT_YV12_GPU[] = "yv12-gpu";
const char MtkCameraParameters::PIXEL_FORMAT_YUV420I[] = "yuv420i-yyuvyy-3plane";
const char CameraParameters::PIXEL_FORMAT_YUV420P[]  = "yuv420p";
const char CameraParameters::PIXEL_FORMAT_YUV420SP[] = "yuv420sp";
const char CameraParameters::PIXEL_FORMAT_YUV422I[] = "yuv422i-yuyv";
const char MtkCameraParameters::PIXEL_FORMAT_YUV422I_UYVY[] = "yuv422i-uyvy";
const char MtkCameraParameters::PIXEL_FORMAT_YUV422I_VYUY[] = "yuv422i-vyuy";
const char MtkCameraParameters::PIXEL_FORMAT_YUV422I_YVYU[] = "yuv422i-yvyu";
const char CameraParameters::PIXEL_FORMAT_YUV422SP[] = "yuv422sp";
const char CameraParameters::PIXEL_FORMAT_RGB565[] = "rgb565";
const char CameraParameters::PIXEL_FORMAT_RGBA8888[] = "rgba8888";
const char CameraParameters::PIXEL_FORMAT_JPEG[] = "jpeg";
const char CameraParameters::PIXEL_FORMAT_BAYER_RGGB[] = "bayer-rggb";
const char CameraParameters::PIXEL_FORMAT_ANDROID_OPAQUE[] = "android-opaque";  

const char MtkCameraParameters::KEY_BRIGHTNESS_VALUE[] = "brightness_value";

// ISP Operation mode for meta mode use 
const char MtkCameraParameters::KEY_ISP_MODE[] = "isp-mode"; 
// AF 
const char MtkCameraParameters::KEY_AF_X[] = "af-x"; 
const char MtkCameraParameters::KEY_AF_Y[] = "af-y"; 
// Effect 
const char MtkCameraParameters::EFFECT_SEPIA_BLUE[] = "sepiablue";
const char MtkCameraParameters::EFFECT_SEPIA_GREEN[] = "sepiagreen";

//
//  on/off => FIXME: should be replaced with TRUE[]
const char MtkCameraParameters::ON[] = "on";
const char MtkCameraParameters::OFF[] = "off";
// 
const char MtkCameraParameters::WHITE_BALANCE_TUNGSTEN[] = "tungsten";
//
const char MtkCameraParameters::ISO_SPEED_ENG[] = "iso-speed-eng";
const char MtkCameraParameters::KEY_RAW_SAVE_MODE[] = "rawsave-mode";
const char MtkCameraParameters::KEY_RAW_PATH[] = "rawfname";

const char MtkCameraParameters::KEY_FAST_CONTINUOUS_SHOT[] = "fast-continuous-shot";

const char MtkCameraParameters::KEY_CSHOT_INDICATOR[] = "cshot-indicator";

// AF EM MODE
const char MtkCameraParameters::KEY_FOCUS_ENG_MODE[]		= "afeng-mode";
const char MtkCameraParameters::KEY_FOCUS_ENG_STEP[] 		= "afeng-pos";
const char MtkCameraParameters::KEY_FOCUS_ENG_MAX_STEP[] 	= "afeng-max-focus-step";
const char MtkCameraParameters::KEY_FOCUS_ENG_MIN_STEP[] 	= "afeng-min-focus-step";
const char MtkCameraParameters::KEY_FOCUS_ENG_BEST_STEP[]   = "afeng-best-focus-step";
const char MtkCameraParameters::KEY_RAW_DUMP_FLAG[]         = "afeng_raw_dump_flag";
const char MtkCameraParameters::KEY_PREVIEW_DUMP_RESOLUTION[] = "preview-dump-resolution";
// Values for KEY_PREVIEW_DUMP_RESOLUTION
const int MtkCameraParameters::PREVIEW_DUMP_RESOLUTION_NORMAL  = 0;
const int MtkCameraParameters::PREVIEW_DUMP_RESOLUTION_CROP  = 1;
//
const char MtkCameraParameters::KEY_MAX_NUM_DETECTED_OBJECT[] = "max-num-ot";
//
const char MtkCameraParameters::KEY_VIDEO_HDR[] = "video-hdr"; 

// KEY for [Engineer Mode] Add new camera paramters for new requirements
const char MtkCameraParameters::KEY_ENG_AE_ENABLE[] = "eng-ae-enable";
const char MtkCameraParameters::KEY_ENG_PREVIEW_SHUTTER_SPEED[] = "eng-preview-shutter-speed";
const char MtkCameraParameters::KEY_ENG_PREVIEW_SENSOR_GAIN[] = "eng-preview-sensor-gain";
const char MtkCameraParameters::KEY_ENG_PREVIEW_ISP_GAIN[] = "eng-preview-isp-gain";
const char MtkCameraParameters::KEY_ENG_PREVIEW_AE_INDEX[] = "eng-preview-ae-index";
const char MtkCameraParameters::KEY_ENG_CAPTURE_SENSOR_GAIN[] = "eng-capture-sensor-gain";
const char MtkCameraParameters::KEY_ENG_CAPTURE_ISP_GAIN[] = "eng-capture-isp-gain";
const char MtkCameraParameters::KEY_ENG_CAPTURE_SHUTTER_SPEED[] = "eng-capture-shutter-speed";
const char MtkCameraParameters::KEY_ENG_CAPTURE_ISO[] = "eng-capture-iso";
const char MtkCameraParameters::KEY_ENG_FLASH_DUTY_VALUE[] = "eng-flash-duty-value";
const char MtkCameraParameters::KEY_ENG_FLASH_DUTY_MIN[] = "eng-flash-duty-min";
const char MtkCameraParameters::KEY_ENG_FLASH_DUTY_MAX[] = "eng-flash-duty-max";
const char MtkCameraParameters::KEY_ENG_ZSD_ENABLE[] = "eng-zsd-enable";
const char MtkCameraParameters::KEY_SENSOR_TYPE[] = "sensor-type";
const char MtkCameraParameters::KEY_ENG_PREVIEW_FPS[] = "eng-preview-fps";
const char MtkCameraParameters::KEY_ENG_MSG[] = "eng-msg";
const int  MtkCameraParameters::KEY_ENG_FLASH_DUTY_DEFAULT_VALUE = -1;
const int  MtkCameraParameters::KEY_ENG_FLASH_STEP_DEFAULT_VALUE = -1;
const char MtkCameraParameters::KEY_ENG_FLASH_STEP_MIN[] = "eng-flash-step-min";
const char MtkCameraParameters::KEY_ENG_FLASH_STEP_MAX[] = "eng-flash-step-max";
const char MtkCameraParameters::KEY_ENG_FOCUS_FULLSCAN_FRAME_INTERVAL[] = "eng-focus-fullscan-frame-interval";
const char MtkCameraParameters::KEY_ENG_FOCUS_FULLSCAN_FRAME_INTERVAL_MAX[] = "eng-focus-fullscan-frame-interval-max";
const char MtkCameraParameters::KEY_ENG_FOCUS_FULLSCAN_FRAME_INTERVAL_MIN[] = "eng-focus-fullscan-frame-interval-min";
const int  MtkCameraParameters::KEY_ENG_FOCUS_FULLSCAN_FRAME_INTERVAL_MAX_DEFAULT = 65535;
const int  MtkCameraParameters::KEY_ENG_FOCUS_FULLSCAN_FRAME_INTERVAL_MIN_DEFAULT = 0;
const char MtkCameraParameters::KEY_ENG_PREVIEW_FRAME_INTERVAL_IN_US[] = "eng-preview-frame-interval-in-us";
const char MtkCameraParameters::KEY_ENG_PARAMETER1[] = "key-eng-parameter1";
const char MtkCameraParameters::KEY_ENG_PARAMETER2[] = "key-eng-parameter2";
const char MtkCameraParameters::KEY_ENG_PARAMETER3[] = "key-eng-parameter3";

const char MtkCameraParameters::KEY_ENG_SAVE_SHADING_TABLE[] = "eng-save-shading-table";
const char MtkCameraParameters::KEY_ENG_SHADING_TABLE[] = "eng-shading-table";
const int MtkCameraParameters::KEY_ENG_SHADING_TABLE_AUTO = 0;
const int MtkCameraParameters::KEY_ENG_SHADING_TABLE_LOW = 1;
const int MtkCameraParameters::KEY_ENG_SHADING_TABLE_MIDDLE = 2;
const int MtkCameraParameters::KEY_ENG_SHADING_TABLE_HIGH = 3;
const int MtkCameraParameters::KEY_ENG_SHADING_TABLE_TSF = 4;

// KEY for [Engineer Mode] Add new camera paramters for ev calibration
const char MtkCameraParameters::KEY_ENG_EV_CALBRATION_OFFSET_VALUE[] = "eng-ev-cal-offset";

#ifdef MTK_SLOW_MOTION_VIDEO_SUPPORT
// High Speed Video Record
const char MtkCameraParameters::KEY_HSVR_PRV_SIZE[] = "hsvr-prv-size";
const char MtkCameraParameters::KEY_SUPPORTED_HSVR_PRV_SIZE[] = "hsvr-prv-size-values";
const char MtkCameraParameters::KEY_HSVR_PRV_FPS[] = "hsvr-prv-fps";
const char MtkCameraParameters::KEY_SUPPORTED_HSVR_PRV_FPS[] = "hsvr-prv-fps-values";
#endif
const char MtkCameraParameters::KEY_DXOEIS_ONOFF[] = "dxo-eis";
const char MtkCameraParameters::KEY_FIX_EXPOSURE_TIME[] = "fix-exposure-time";

/////////////////////End Of Mediatek Custom Parameters/////////////////////

CameraParameters::CameraParameters()
                : mMap()
{
}

CameraParameters::~CameraParameters()
{
}

String8 CameraParameters::flatten() const
{
    String8 flattened("");
    size_t size = mMap.size();

    for (size_t i = 0; i < size; i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);

        flattened += k;
        flattened += "=";
        flattened += v;
        if (i != size-1)
            flattened += ";";
    }

    return flattened;
}

void CameraParameters::unflatten(const String8 &params)
{
    const char *a = params.string();
    const char *b;

    mMap.clear();

    for (;;) {
        // Find the bounds of the key name.
        b = strchr(a, '=');
        if (b == 0)
            break;

        // Create the key string.
        String8 k(a, (size_t)(b-a));

        // Find the value.
        a = b+1;
        b = strchr(a, ';');
        if (b == 0) {
            // If there's no semicolon, this is the last item.
            String8 v(a);
            mMap.add(k, v);
            break;
        }

        String8 v(a, (size_t)(b-a));
        mMap.add(k, v);
        a = b+1;
    }
}


void CameraParameters::set(const char *key, const char *value)
{
    if (key == NULL || value == NULL)
        return;

    // XXX i think i can do this with strspn()
    if (strchr(key, '=') || strchr(key, ';')) {
        //XXX ALOGE("Key \"%s\"contains invalid character (= or ;)", key);
        return;
    }

    if (strchr(value, '=') || strchr(value, ';')) {
        //XXX ALOGE("Value \"%s\"contains invalid character (= or ;)", value);
        return;
    }
#ifdef QCOM_HARDWARE
    // qcom cameras default to delivering an extra zero-exposure frame on HDR.
    // The android SDK only wants one frame, so disable this unless the app
    // explicitly asks for it
    if (!get("hdr-need-1x")) {
        mMap.replaceValueFor(String8("hdr-need-1x"), String8("false"));
    }
#endif

    mMap.replaceValueFor(String8(key), String8(value));
}

void CameraParameters::set(const char *key, int value)
{
    char str[16];
    sprintf(str, "%d", value);
    set(key, str);
}

void CameraParameters::setFloat(const char *key, float value)
{
    char str[16];  // 14 should be enough. We overestimate to be safe.
    snprintf(str, sizeof(str), "%g", value);
    set(key, str);
}

const char *CameraParameters::get(const char *key) const
{
    String8 v = mMap.valueFor(String8(key));
    if (v.length() == 0)
        return 0;
    return v.string();
}

int CameraParameters::getInt(const char *key) const
{
    const char *v = get(key);
    if (v == 0)
        return -1;
    return strtol(v, 0, 0);
}

float CameraParameters::getFloat(const char *key) const
{
    const char *v = get(key);
    if (v == 0) return -1;
    return strtof(v, 0);
}

void CameraParameters::remove(const char *key)
{
    mMap.removeItem(String8(key));
}

// Parse string like "640x480" or "10000,20000"
static int parse_pair(const char *str, int *first, int *second, char delim,
                      char **endptr = NULL)
{
    // Find the first integer.
    char *end;
    int w = (int)strtol(str, &end, 10);
    // If a delimeter does not immediately follow, give up.
    if (*end != delim) {
        ALOGE("Cannot find delimeter (%c) in str=%s", delim, str);
        return -1;
    }

    // Find the second integer, immediately after the delimeter.
    int h = (int)strtol(end+1, &end, 10);

    *first = w;
    *second = h;

    if (endptr) {
        *endptr = end;
    }

    return 0;
}

static void parseSizesList(const char *sizesStr, Vector<Size> &sizes)
{
    if (sizesStr == 0) {
        return;
    }

    char *sizeStartPtr = (char *)sizesStr;

    while (true) {
        int width, height;
        int success = parse_pair(sizeStartPtr, &width, &height, 'x',
                                 &sizeStartPtr);
        if (success == -1 || (*sizeStartPtr != ',' && *sizeStartPtr != '\0')) {
            ALOGE("Picture sizes string \"%s\" contains invalid character.", sizesStr);
            return;
        }
        sizes.push(Size(width, height));

        if (*sizeStartPtr == '\0') {
            return;
        }
        sizeStartPtr++;
    }
}

void CameraParameters::setPreviewSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_PREVIEW_SIZE, str);
}

void CameraParameters::getPreviewSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PREVIEW_SIZE);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getPreferredPreviewSizeForVideo(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPreviewSizes(Vector<Size> &sizes) const
{
    const char *previewSizesStr = get(KEY_SUPPORTED_PREVIEW_SIZES);
    parseSizesList(previewSizesStr, sizes);
}

void CameraParameters::setVideoSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_VIDEO_SIZE, str);
}

void CameraParameters::getVideoSize(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_VIDEO_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedVideoSizes(Vector<Size> &sizes) const
{
    const char *videoSizesStr = get(KEY_SUPPORTED_VIDEO_SIZES);
    parseSizesList(videoSizesStr, sizes);
}

void CameraParameters::setPreviewFrameRate(int fps)
{
    set(KEY_PREVIEW_FRAME_RATE, fps);
}

int CameraParameters::getPreviewFrameRate() const
{
    return getInt(KEY_PREVIEW_FRAME_RATE);
}

void CameraParameters::getPreviewFpsRange(int *min_fps, int *max_fps) const
{
    *min_fps = *max_fps = -1;
    const char *p = get(KEY_PREVIEW_FPS_RANGE);
    if (p == 0) return;
    parse_pair(p, min_fps, max_fps, ',');
}

void CameraParameters::setPreviewFormat(const char *format)
{
    set(KEY_PREVIEW_FORMAT, format);
}

const char *CameraParameters::getPreviewFormat() const
{
    return get(KEY_PREVIEW_FORMAT);
}

void CameraParameters::setPictureSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_PICTURE_SIZE, str);
}

void CameraParameters::getPictureSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PICTURE_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPictureSizes(Vector<Size> &sizes) const
{
    const char *pictureSizesStr = get(KEY_SUPPORTED_PICTURE_SIZES);
    parseSizesList(pictureSizesStr, sizes);
}

void CameraParameters::setPictureFormat(const char *format)
{
    set(KEY_PICTURE_FORMAT, format);
}

const char *CameraParameters::getPictureFormat() const
{
    return get(KEY_PICTURE_FORMAT);
}

void CameraParameters::dump() const
{
    ALOGD("dump: mMap.size = %zu", mMap.size());
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        ALOGD("%s: %s\n", k.string(), v.string());
    }
}

status_t CameraParameters::dump(int fd, const Vector<String16>& /*args*/) const
{
    const size_t SIZE = 256;
    char buffer[SIZE];
    String8 result;
    snprintf(buffer, 255, "CameraParameters::dump: mMap.size = %zu\n", mMap.size());
    result.append(buffer);
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        snprintf(buffer, 255, "\t%s: %s\n", k.string(), v.string());
        result.append(buffer);
    }
    write(fd, result.string(), result.size());
    return NO_ERROR;
}

void CameraParameters::getSupportedPreviewFormats(Vector<int>& formats) const {
    const char* supportedPreviewFormats =
          get(CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS);

    if (supportedPreviewFormats == NULL) {
        ALOGW("%s: No supported preview formats.", __FUNCTION__);
        return;
    }

    String8 fmtStr(supportedPreviewFormats);
    char* prevFmts = fmtStr.lockBuffer(fmtStr.size());

    char* savePtr;
    char* fmt = strtok_r(prevFmts, ",", &savePtr);
    while (fmt) {
        int actual = previewFormatToEnum(fmt);
        if (actual != -1) {
            formats.add(actual);
        }
        fmt = strtok_r(NULL, ",", &savePtr);
    }
    fmtStr.unlockBuffer(fmtStr.size());
}


int CameraParameters::previewFormatToEnum(const char* format) {
    return
        !format ?
            HAL_PIXEL_FORMAT_YCrCb_420_SP :
        !strcmp(format, PIXEL_FORMAT_YUV422SP) ?
            HAL_PIXEL_FORMAT_YCbCr_422_SP : // NV16
        !strcmp(format, PIXEL_FORMAT_YUV420SP) ?
            HAL_PIXEL_FORMAT_YCrCb_420_SP : // NV21
        !strcmp(format, PIXEL_FORMAT_YUV422I) ?
            HAL_PIXEL_FORMAT_YCbCr_422_I :  // YUY2
        !strcmp(format, PIXEL_FORMAT_YUV420P) ?
            HAL_PIXEL_FORMAT_YV12 :         // YV12
        !strcmp(format, PIXEL_FORMAT_RGB565) ?
            HAL_PIXEL_FORMAT_RGB_565 :      // RGB565
        !strcmp(format, PIXEL_FORMAT_RGBA8888) ?
            HAL_PIXEL_FORMAT_RGBA_8888 :    // RGB8888
        !strcmp(format, PIXEL_FORMAT_BAYER_RGGB) ?
            HAL_PIXEL_FORMAT_RAW16 :   // Raw sensor data
        -1;
}

bool CameraParameters::isEmpty() const {
    return mMap.isEmpty();
}

}; // namespace android

