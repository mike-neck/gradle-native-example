#include "com_example_App.h"
#include <jni.h>
#include <string>

jstring throwNewIllegalArgumentException(JNIEnv *env);
jobject throwNewIllegalStateException(JNIEnv *env, const char *target);

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

JNIEXPORT jobject JNICALL Java_com_example_App_repeat
  (JNIEnv *env, jobject thisObject, jint times, jstring target) {

  if (times < 0) {
    throwNewIllegalArgumentException(env);
    return NULL;
  }
  if (target == NULL) {
    throwNewIllegalArgumentException(env);
    return NULL;
  }
  jclass arrayListClass = env->FindClass("java/util/ArrayList");
  if (arrayListClass == NULL) {
    return throwNewIllegalStateException(env, "class java/util/ArrayList");
  }
  jmethodID constructor = env->GetMethodID(arrayListClass, "<init>", "()V");
  if (constructor == NULL) {
    return throwNewIllegalStateException(env, "constructor of java/util/ArrayList");
  }
  jobject arrayList = env->NewObject(arrayListClass, constructor);
  if (arrayList == NULL) {
    return throwNewIllegalStateException(env, "init of java/util/ArrayList");
  }

  jmethodID addMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
  if (addMethod == NULL) {
    return throwNewIllegalStateException(env, "add of java/util/ArrayList");
  }

  jint i = 0;
  for (; i < times; i++) {
    env->CallBooleanMethod(arrayList, addMethod, target);
  }
  return arrayList;
}

jobject throwNewIllegalStateException(JNIEnv *env, const char *target) {
    std::string message = std::string(target);
    message += " not found";
    env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"), message.c_str());
    return NULL;
}
