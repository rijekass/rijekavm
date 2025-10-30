/*
 * Copyright (c) 2016, 2023, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "jfr/instrumentation/jfrJvmtiAgent.hpp"
#include "jfr/jni/jfrJavaSupport.hpp"
#include "jfr/jni/jfrUpcalls.hpp"
#include "jfr/recorder/checkpoint/types/traceid/jfrTraceId.inline.hpp"
#include "jfr/recorder/service/jfrOptionSet.hpp"
#include "jfr/support/jfrJdkJfrEvent.hpp"
#include "jvm.h"
#include "logging/log.hpp"
#include "memory/resourceArea.hpp"
#include "prims/jvmtiEnvBase.hpp"
#include "prims/jvmtiExport.hpp"
#include "prims/jvmtiUtil.hpp"
#include "runtime/interfaceSupport.inline.hpp"
#include "runtime/javaThread.inline.hpp"
#include "utilities/exceptions.hpp"

static const size_t ERROR_MSG_BUFFER_SIZE = 256;
static JfrJvmtiAgent* agent = nullptr;
static jvmtiEnv* jfr_jvmti_env = nullptr;

static void check_jvmti_error(jvmtiEnv* jvmti, jvmtiError errnum, const char* str) {
}

static bool set_event_notification_mode(jvmtiEventMode mode,
                                        jvmtiEvent event,
                                        jthread event_thread,
                                        ...) {
    return false;
}

static bool update_class_file_load_hook_event(jvmtiEventMode mode) {
  return set_event_notification_mode(mode, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, nullptr);
}

// jvmti event callbacks require C linkage
extern "C" void JNICALL jfr_on_class_file_load_hook(jvmtiEnv *jvmti_env,
                                                    JNIEnv* jni_env,
                                                    jclass class_being_redefined,
                                                    jobject loader,
                                                    const char* name,
                                                    jobject protection_domain,
                                                    jint class_data_len,
                                                    const unsigned char* class_data,
                                                    jint* new_class_data_len,
                                                    unsigned char** new_class_data) {
}

// caller needs ResourceMark
static jclass* create_classes_array(jint classes_count, TRAPS) {
  return 0;
}

// caller needs ResourceMark
static void log_and_throw(jvmtiError error, TRAPS) {
}

static void check_exception_and_log(JNIEnv* env, TRAPS) {
}

static bool is_valid_jvmti_phase() {
    return false;
}

void JfrJvmtiAgent::retransform_classes(JNIEnv* env, jobjectArray classes_array, TRAPS) {
}

static bool register_callbacks(JavaThread* jt) {
  return false;
}

static bool register_capabilities(JavaThread* jt) {
  assert(jfr_jvmti_env != nullptr, "invariant");
  DEBUG_ONLY(JfrJavaSupport::check_java_thread_in_native(jt));
  jvmtiCapabilities capabilities;
  /* Add JVMTI capabilities */
  (void)memset(&capabilities, 0, sizeof(capabilities));
  capabilities.can_retransform_classes = 1;
  capabilities.can_retransform_any_class = 1;
  const jvmtiError jvmti_ret_code = jfr_jvmti_env->AddCapabilities(&capabilities);
  check_jvmti_error(jfr_jvmti_env, jvmti_ret_code, "Add Capabilities");
  return jvmti_ret_code == JVMTI_ERROR_NONE;
}

static jint create_jvmti_env(JavaThread* jt) {
  assert(jfr_jvmti_env == nullptr, "invariant");
  DEBUG_ONLY(JfrJavaSupport::check_java_thread_in_native(jt));
  extern struct JavaVM_ main_vm;
  JavaVM* vm = &main_vm;
  return vm->GetEnv((void **)&jfr_jvmti_env, JVMTI_VERSION);
}

static bool unregister_callbacks(JavaThread* jt) {
  assert(jfr_jvmti_env != nullptr, "invariant");
  jvmtiEventCallbacks callbacks;
  /* Set empty callbacks */
  memset(&callbacks, 0, sizeof(callbacks));
  const jvmtiError jvmti_ret_code = jfr_jvmti_env->SetEventCallbacks(&callbacks, sizeof(callbacks));
  check_jvmti_error(jfr_jvmti_env, jvmti_ret_code, "SetEventCallbacks");
  return jvmti_ret_code == JVMTI_ERROR_NONE;
}

JfrJvmtiAgent::JfrJvmtiAgent() {}

JfrJvmtiAgent::~JfrJvmtiAgent() {
}

static bool initialize(JavaThread* jt) {
    return false;
}

static void log_and_throw_illegal_state_exception(TRAPS) {
}

bool JfrJvmtiAgent::create() {
  return true;
}

void JfrJvmtiAgent::destroy() {
}
