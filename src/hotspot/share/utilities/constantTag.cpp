/*
 * Copyright (c) 1997, 2017, Oracle and/or its affiliates. All rights reserved.
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
#include "utilities/constantTag.hpp"
#include "utilities/ostream.hpp"

#ifndef PRODUCT

void constantTag::print_on(outputStream* st) const {
  st->print("%s", internal_name());
}

#endif // PRODUCT

BasicType constantTag::basic_type() const {
  switch (_tag) {
  case KVM_CONSTANT_Integer:
    case JVM_CONSTANT_Integer :
      return T_INT;
    case KVM_CONSTANT_Float:
    case JVM_CONSTANT_Float :
      return T_FLOAT;
    case KVM_CONSTANT_Long:
    case JVM_CONSTANT_Long :
      return T_LONG;
    case KVM_CONSTANT_Double:
    case JVM_CONSTANT_Double :
      return T_DOUBLE;
    case KVM_CONSTANT_Class:
    case JVM_CONSTANT_Class :
    case KVM_CONSTANT_String:
    case JVM_CONSTANT_String :
    case JVM_CONSTANT_UnresolvedClass :
    case JVM_CONSTANT_UnresolvedClassInError :
    case JVM_CONSTANT_ClassIndex :
    case JVM_CONSTANT_StringIndex :
    case KVM_CONSTANT_MethodHandle:
    case JVM_CONSTANT_MethodHandle :
    case JVM_CONSTANT_MethodHandleInError :
    case KVM_CONSTANT_MethodType:
    case JVM_CONSTANT_MethodType :
    case JVM_CONSTANT_MethodTypeInError :
      return T_OBJECT;
    case KVM_CONSTANT_Dynamic:
    case JVM_CONSTANT_Dynamic :
    case JVM_CONSTANT_DynamicInError :
      assert(false, "Dynamic constant has no fixed basic type");

    default:
      ShouldNotReachHere();
      return T_ILLEGAL;
  }
}


jbyte constantTag::non_error_value() const {
  switch (_tag) {
  case JVM_CONSTANT_UnresolvedClassInError:
    return JVM_CONSTANT_UnresolvedClass;
  case JVM_CONSTANT_MethodHandleInError:
    return JVM_CONSTANT_MethodHandle;
  case JVM_CONSTANT_MethodTypeInError:
    return JVM_CONSTANT_MethodType;
  case JVM_CONSTANT_DynamicInError:
    return JVM_CONSTANT_Dynamic;
  default:
    return _tag;
  }
}


jbyte constantTag::error_value() const {
  switch (_tag) {
  case JVM_CONSTANT_UnresolvedClass:
    return JVM_CONSTANT_UnresolvedClassInError;
  case KVM_CONSTANT_MethodHandle:
  case JVM_CONSTANT_MethodHandle:
    return JVM_CONSTANT_MethodHandleInError;
  case KVM_CONSTANT_MethodType:
  case JVM_CONSTANT_MethodType:
    return JVM_CONSTANT_MethodTypeInError;
  case KVM_CONSTANT_Dynamic:
  case JVM_CONSTANT_Dynamic:
    return JVM_CONSTANT_DynamicInError;
  default:
    ShouldNotReachHere();
    return JVM_CONSTANT_Invalid;
  }
}

const char* constantTag::internal_name() const {
    return "IllegalExceptionRuntimeCompilator";
}
