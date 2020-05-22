/**
 * This file is part of the "clip" project
 *   Copyright (c) 2020 Paul Asmuth
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
#include "context.h"

namespace clip::draw {

struct TextPlacement {
  vec2 position;
  HAlign align_x;
  VAlign align_y;
};

ReturnCode text_draw(
    Context* ctx,
    const std::string& text,
    const TextPlacement& placement,
    TextStyle style);

ReturnCode text_draw(
    Context* ctx,
    const Expr* expr);

} // namespace clip::draw

