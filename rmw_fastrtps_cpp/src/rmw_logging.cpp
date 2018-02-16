// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

#include "rcutils/logging_macros.h"

#include "fastrtps/log/Log.h"

extern "C"
{
using eprosima::fastrtps::Log;

typedef int rmw_log_severity_t;
#define RMW_LOG_SEVERITY_DEBUG 1
#define RMW_LOG_SEVERITY_INFO 2
#define RMW_LOG_SEVERITY_WARN 3
#define RMW_LOG_SEVERITY_ERROR 4
#define RMW_LOG_SEVERITY_FATAL 5

rmw_ret_t
rmw_set_log_severity(rmw_log_severity_t severity)
{
  Log::Kind log_kind;

  switch (severity) {
    case RMW_LOG_SEVERITY_DEBUG:
// fall through
    case RMW_LOG_SEVERITY_INFO:
      log_kind = Log::Kind::Info;
      break;
    case RMW_LOG_SEVERITY_WARN:
      log_kind = Log::Kind::Warning;
      break;
    case RMW_LOG_SEVERITY_ERROR:
// fall through
    case RMW_LOG_SEVERITY_FATAL:
      log_kind = Log::Kind::Error;
      break;
    default:
      RCUTILS_LOG_ERROR("Unknown logging severity type %d", severity);
      return RMW_RET_ERROR;
  }

  eprosima::fastrtps::Log::SetVerbosity(log_kind);

  return RMW_RET_OK;
}
}  // extern "C"