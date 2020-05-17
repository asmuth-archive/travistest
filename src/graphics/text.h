/**
 * This file is part of the "clip" project
 *   Copyright (c) 2018 Paul Asmuth
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "path.h"
#include "color.h"
#include "measure.h"
#include "layout.h"
#include "font_lookup.h"

namespace clip {
namespace text {
struct TextSpan;
}

enum class TextDirection {
  LTR, RTL
};

struct TextStyle {
  TextStyle();
  TextDirection direction;
  FontInfo font;
  Number font_size;
  Color color;
  std::string default_script;
  std::string default_language;
};

/**
 * Convenience function to measure the size of a simple piece of text.
 */
Status text_measure_label(
    const std::string& text,
    TextDirection text_direction_base,
    const FontInfo& font,
    double font_size,
    double dpi,
    Rectangle* bbox);

Status text_measure_label(
    const std::string& text,
    TextDirection text_direction_base,
    const FontInfo& font,
    Number font_size,
    double dpi,
    Rectangle* bbox);


} // namespace clip

