#include "com_example_App.h"
#include <jni.h>
#include <string>

JNIEXPORT jstring JNICALL Java_com_example_App_greetingTo
  (JNIEnv *env, jobject thisObject, jstring name) {
  jsize size = env->GetStringUTFLength(name);
  if (size == 0) {
    env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"), "invalid argument");
    return NULL;
  }
  std::string nameValue(env->GetStringUTFChars(name, false));
  std::string greeting = std::string("Hello, ");
  greeting += nameValue;
  return env->NewStringUTF(greeting.c_str());
}
