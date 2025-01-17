/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_TRACE_PROCESSOR_IMPORTERS_ANDROID_BUGREPORT_ANDROID_BUGREPORT_PARSER_H_
#define SRC_TRACE_PROCESSOR_IMPORTERS_ANDROID_BUGREPORT_ANDROID_BUGREPORT_PARSER_H_

#include "src/trace_processor/importers/common/chunked_trace_reader.h"
#include "src/trace_processor/storage/trace_storage.h"

namespace perfetto {
namespace trace_processor {

namespace util {
class ZipReader;
}

class TraceProcessorContext;

// Trace importer for Android bugreport.zip archives.
class AndroidBugreportParser : public ChunkedTraceReader {
 public:
  explicit AndroidBugreportParser(TraceProcessorContext*);
  ~AndroidBugreportParser() override;

  // ChunkedTraceReader implementation.
  util::Status Parse(TraceBlobView) override;
  void NotifyEndOfFile() override;

 private:
  bool DetectYear();
  void ParsePersistentLogcat();

  TraceProcessorContext* const context_;
  int br_year_ = 0;  // The year when the bugreport has been taken.
  bool first_chunk_seen_ = false;
  std::unique_ptr<util::ZipReader> zip_reader_;
};

}  // namespace trace_processor
}  // namespace perfetto

#endif  // SRC_TRACE_PROCESSOR_IMPORTERS_ANDROID_BUGREPORT_ANDROID_BUGREPORT_PARSER_H_
