//FIXME update to ndk 10e+
/*
#include "fnadroid-wrapper.h"

#include <jni.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <android/sensor.h>
#include <android/log.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/utils/mono-logger.h>
*/

//cpp to j

void showMsg(const char* title, const char* msg) {
    jstring jsTitle = jnienv->NewStringUTF(title);
    jstring jsMsg = jnienv->NewStringUTF(msg);
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID showMsgID = jnienv->GetStaticMethodID(clazz, "showMsg", "(Ljava/lang/String;Ljava/lang/String;)V");
    jnienv->CallStaticVoidMethod(clazz, showMsgID, jsTitle, jsMsg);
    jnienv->DeleteLocalRef(jsTitle);
    jnienv->DeleteLocalRef(jsMsg);
}
void showDebug(const char* msg) {
    jstring jsMsg = jnienv->NewStringUTF(msg);
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID showMsgID = jnienv->GetStaticMethodID(clazz, "showDebug", "(Ljava/lang/String;)V");
    jnienv->CallStaticVoidMethod(clazz, showMsgID, jsMsg);
    jnienv->DeleteLocalRef(jsMsg);
}
void showError(const char* msg) {
    jstring jsMsg = jnienv->NewStringUTF(msg);
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID showMsgID = jnienv->GetStaticMethodID(clazz, "showError", "(Ljava/lang/String;)V");
    jnienv->CallStaticVoidMethod(clazz, showMsgID, jsMsg);
    jnienv->DeleteLocalRef(jsMsg);
}

char* getGamePath() {
    return fnadir;
}
char* getHomePath() {
    return homedir;
}
char* getPackageName() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getPackageName", "()Ljava/lang/String;");
    jstring jsVal = (jstring) jnienv->CallStaticObjectMethod(clazz, mID);
    const char* val = jnienv->GetStringUTFChars(jsVal, 0);
    char* valdup = strdup(val); //TODO is that duplication required?!
    jnienv->ReleaseStringUTFChars(jsVal, val);
    return valdup;
}
char* getDataPath() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getDataPath", "()Ljava/lang/String;");
    jstring jsVal = (jstring) jnienv->CallStaticObjectMethod(clazz, mID);
    const char* val = jnienv->GetStringUTFChars(jsVal, 0);
    char* valdup = strdup(val); //TODO is that duplication required?!
    jnienv->ReleaseStringUTFChars(jsVal, val);
    return valdup;
}
char* getMainObbPath() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getMainObbPath", "()Ljava/lang/String;");
    jstring jsVal = (jstring) jnienv->CallStaticObjectMethod(clazz, mID);
    const char* val = jnienv->GetStringUTFChars(jsVal, 0);
    char* valdup = strdup(val); //TODO is that duplication required?!
    jnienv->ReleaseStringUTFChars(jsVal, val);
    return valdup;
}
char* getPatchObbPath() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getPatchObbPath", "()Ljava/lang/String;");
    jstring jsVal = (jstring) jnienv->CallStaticObjectMethod(clazz, mID);
    const char* val = jnienv->GetStringUTFChars(jsVal, 0);
    char* valdup = strdup(val); //TODO is that duplication required?!
    jnienv->ReleaseStringUTFChars(jsVal, val);
    return valdup;
}
char* getInstallerPackageName() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getInstallerPackageName", "()Ljava/lang/String;");
    jstring jsVal = (jstring) jnienv->CallStaticObjectMethod(clazz, mID);
    const char* val = jnienv->GetStringUTFChars(jsVal, 0);
    char* valdup = strdup(val); //TODO is that duplication required?!
    jnienv->ReleaseStringUTFChars(jsVal, val);
    return valdup;
}
int getMaximumGLES() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getMaximumGLES", "()I");
    return (int) jnienv->CallStaticIntMethod(clazz, mID);
}

void vibrationCancel() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "vibrationCancel", "()V");
    jnienv->CallStaticVoidMethod(clazz, mID);
}
bool vibrationAvailable() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "vibrationAvailable", "()Z");
    return (bool) jnienv->CallStaticBooleanMethod(clazz, mID);
}
void vibrate(long long milliseconds) {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "vibrate", "(J)V");
    jnienv->CallStaticVoidMethod(clazz, mID, (jlong) milliseconds);
}

bool accelerometerAvailable() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "accelerometerAvailable", "()Z");
    return (bool) jnienv->CallStaticBooleanMethod(clazz, mID);
}
float getAccelerometerAxis(int axis) {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getAccelerometerAxis", "(I)F");
    return (float) jnienv->CallStaticFloatMethod(clazz, mID);
}

bool gyroscopeAvailable() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "gyroscopeAvailable", "()Z");
    return (bool) jnienv->CallStaticBooleanMethod(clazz, mID);
}
float getGyroscopeRotationRateAxis(int axis) {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getGyroscopeRotationRateAxis", "(I)F");
    return (float) jnienv->CallStaticFloatMethod(clazz, mID);
}

int getMaximumTouchCount() {
    jclass clazz = jnienv->FindClass("com/angelde/fnadroid/FNADroidWrapper");
    jmethodID mID = jnienv->GetStaticMethodID(clazz, "getMaximumTouchCount", "()I");
    return (int) jnienv->CallStaticIntMethod(clazz, mID);
}

//m to c, c to cpp
#ifdef __cplusplus
extern "C" {
#endif

void PrintInfo(const char* msg) {
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", msg);
}
void PrintWarn(const char* msg) {
    __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "%s", msg);
}
void PrintError(const char* msg) {
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", msg);
}

void Popup(const char* title, const char* msg) {
    showMsg(title, msg);
}
void PopupDebug(const char* msg) {
    showDebug(msg);
}
void PopupError(const char* msg) {
    showError(msg);
}

char* GetGamePath() {
    return getGamePath();
}
char* GetHomePath() {
    return getHomePath();
}
char* GetPackageName() {
    return getPackageName();
}
char* GetDataPath() {
    return getDataPath();
}
char* GetMainObbPath() {
    return getMainObbPath();
}
char* GetPatchObbPath() {
    return getPatchObbPath();
}
char* GetInstallerPackageName() {
    return getInstallerPackageName();
}
int j_GetMaximumGLES() {
    return getMaximumGLES();
}

void VibrationCancel() {
    vibrationCancel();
}
bool VibrationAvailable() {
    return vibrationAvailable();
}
void Vibrate(long long milliseconds) {
    vibrate(milliseconds);
}

bool AccelerometerAvailable() {
    return accelerometerAvailable();
}
float GetAccelerometerAxis(int axis) {
    return getAccelerometerAxis(axis);
}

bool GyroscopeAvailable() {
    return gyroscopeAvailable();
}
float GetGyroscopeRotationRateAxis(int axis) {
    return getGyroscopeRotationRateAxis(axis);
}

int GetMaximumTouchCount() {
    return getMaximumTouchCount();
}

#ifdef __cplusplus
}
#endif
