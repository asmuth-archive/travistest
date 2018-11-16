/**
 * This file is part of the "plotfx" project
 *   Copyright (c) 2018 Paul Asmuth
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "layer.h"
#include <utils/stringutil.h>
#include "png.h"

namespace signaltk {

Layer::Layer(
    double w,
    double h,
    double rem_ /* = 12 */,
    double dpi_ /* = 96 */) :
    width(w),
    height(h),
    dpi(dpi_),
    rem(rem_),
    pixmap(PixelFormat::RGBA8, w, h),
    text_shaper(dpi),
    rasterizer(&pixmap, dpi) {}

Layer::~Layer() {}

Status Layer::writeToFile(const std::string& path) {
  if (StringUtil::endsWith(path, ".png")) {
    return pngWriteImageFile(pixmap, path);
  }

  return ERROR_INVALID_ARGUMENT;
}

Status Layer::loadFromFile(const std::string& path) const {
  return ERROR_INVALID_ARGUMENT;
}

void Layer::clear(const Colour& c) {
  pixmap.clear(c);
}

double from_rem(const Layer& l, double v) {
  return from_pt(l, l.rem) * v;
}

double from_px(const Layer& l, double v) {
  return v;
}

double from_pt(const Layer& l, double v) {
  return (v / 72.0) * l.dpi;
}

double to_pt(const Layer& l, double v) {
  return (v / l.dpi) * 72;
}

} // namespace signaltk

