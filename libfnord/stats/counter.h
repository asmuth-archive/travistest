/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_STATS_COUNTER_H
#define _FNORD_STATS_COUNTER_H
#include <stdlib.h>
#include <stdint.h>
#include "fnord/base/datetime.h"
#include "fnord/base/hash.h"

namespace fnord {
namespace stats {

template <typename ValueType, typename... LabelTypes>
class Counter {
public:
  typedef std::tuple<LabelTypes...> LabelValuesType;

  template <typename... LabelNameTypes>
  Counter(LabelNameTypes... label_names);

  void increment(ValueType value);
  void set(ValueType value);

protected:
  std::unordered_map<LabelValuesType, ValueType, hash<LabelValuesType>> values_;
  std::mutex mutex_;
};

}
}

#include "counter_impl.h"
#endif
