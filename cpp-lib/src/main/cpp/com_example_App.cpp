#include "com_example_App.h"
#include <jni.h>
#include <string>

jstring throwNewIllegalArgumentException(JNIEnv *env);

JNIEXPORT jstring JNICALL Java_com_example_App_greetingTo
  (JNIEnv *env, jobject thisObject, jstring name) {
  if (name == NULL) {
    return throwNewIllegalArgumentException(env);
  }
  jsize size = env->GetStringUTFLength(name);
  if (size == 0) {
    return throwNewIllegalArgumentException(env);
  }
  std::string nameValue(env->GetStringUTFChars(name, JNI_FALSE));
  std::string greeting = std::string("Hello, ");
  greeting += nameValue;
  return env->NewStringUTF(greeting.c_str());
}

jstring throwNewIllegalArgumentException(JNIEnv *env) {
  env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"), "invalid argument");
  return NULL;
}
