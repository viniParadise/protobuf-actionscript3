// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.
// http://code.google.com/p/protobuf/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Robert Blackwood (ported from Kenton's)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#include <google/protobuf/compiler/as3/as3_extension.h>
#include <google/protobuf/compiler/as3/as3_helpers.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/io/printer.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace as3 {

ExtensionGenerator::ExtensionGenerator(const FieldDescriptor* descriptor)
  : descriptor_(descriptor) {}

ExtensionGenerator::~ExtensionGenerator() {}

void ExtensionGenerator::Generate(io::Printer* printer) {
  map<string, string> vars;
  vars["name"] = UnderscoresToCamelCase(descriptor_);
  vars["containing_type"] = ClassName(descriptor_->containing_type());
  vars["index"] = SimpleItoa(descriptor_->index());

  As3Type as3_type = GetAs3Type(descriptor_);
  string singular_type;
  switch (as3_type) {
    case AS3TYPE_MESSAGE:
      vars["type"] = ClassName(descriptor_->message_type());
      break;
    case AS3TYPE_ENUM:
      vars["type"] = ClassName(descriptor_->enum_type());
      break;
    default:
      vars["type"] = BoxedPrimitiveTypeName(as3_type);
      break;
  }

  //if (descriptor_->is_repeated()) {
  //  printer->Print(vars,
  //    "public static final\n"
  //    "  com.google.protobuf.GeneratedMessage.GeneratedExtension<\n"
  //    "    $containing_type$,\n"
  //    "    as3.util.List<$type$>> $name$ =\n"
  //    "      com.google.protobuf.GeneratedMessage\n"
  //    "        .newRepeatedGeneratedExtension(\n"
  //    "          getDescriptor().getExtensions().get($index$),\n"
  //    "          $type$.class);\n");
  //} else {
  //  printer->Print(vars,
  //    "public static final\n"
  //    "  com.google.protobuf.GeneratedMessage.GeneratedExtension<\n"
  //    "    $containing_type$,\n"
  //    "    $type$> $name$ =\n"
  //    "      com.google.protobuf.GeneratedMessage.newGeneratedExtension(\n"
  //    "        getDescriptor().getExtensions().get($index$),\n"
  //    "        $type$.class);\n");
  //}
}

}  // namespace as3
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
