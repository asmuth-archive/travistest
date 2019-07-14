/**
 * This file is part of the "fviz" project
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
#include "areas.h"
#include "scale.h"
#include "sexpr_conv.h"
#include "sexpr_util.h"
#include "graphics/path.h"
#include "graphics/brush.h"
#include "graphics/text.h"
#include "graphics/layout.h"
#include "config_helpers.h"
#include "core/environment.h"

#include <numeric>

using namespace std::placeholders;

namespace fviz::elements::chart::areas {

struct PlotAreaConfig {
  PlotAreaConfig();
  Direction direction;
  std::vector<Measure> x;
  std::vector<Measure> xoffset;
  std::vector<Measure> y;
  std::vector<Measure> yoffset;
  ScaleConfig scale_x;
  ScaleConfig scale_y;
  std::vector<Color> colors;
  LayoutSettings layout;
};

PlotAreaConfig::PlotAreaConfig() :
    direction(Direction::VERTICAL) {}

ReturnCode draw_horizontal(
    PlotAreaConfig config,
    const LayoutInfo& layout,
    Layer* layer) {
  const auto& clip = layout.content_box;

  /* convert units */
  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_x), _1),
        bind(&convert_unit_relative, clip.w, _1)
      },
      &*config.x.begin(),
      &*config.x.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_x), _1),
        bind(&convert_unit_relative, clip.w, _1)
      },
      &*config.xoffset.begin(),
      &*config.xoffset.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_y), _1),
        bind(&convert_unit_relative, clip.h, _1)
      },
      &*config.y.begin(),
      &*config.y.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_y), _1),
        bind(&convert_unit_relative, clip.h, _1)
      },
      &*config.yoffset.begin(),
      &*config.yoffset.end());

  /* draw areas */
  Path path;

  for (size_t i = 0; i < config.x.size(); ++i) {
    auto sx = clip.x + config.x[i];
    auto sy = clip.y + clip.h - config.y[i];

    if (i == 0) {
      path.moveTo(sx, sy);
    } else {
      path.lineTo(sx, sy);
    }
  }

  auto x0 = clip.h * std::clamp(scale_translate(config.scale_x, 0), 0.0, 1.0);
  for (int i = config.x.size() - 1; i >= 0; --i) {
    auto sx = clip.x + (config.xoffset.empty() ? x0 : config.xoffset[i]);
    auto sy = clip.y + clip.h - config.y[i];
    path.lineTo(sx, sy);
  }

  path.closePath();

  FillStyle style;
  style.color = config.colors.empty()
      ? Color{}
      : config.colors[0];

  fillPath(layer, clip, path, style);

  return OK;
}

ReturnCode draw_vertical(
    PlotAreaConfig config,
    const LayoutInfo& layout,
    Layer* layer) {
  const auto& clip = layout.content_box;

  /* convert units */
  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_x), _1),
        bind(&convert_unit_relative, clip.w, _1)
      },
      &*config.x.begin(),
      &*config.x.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_x), _1),
        bind(&convert_unit_relative, clip.w, _1)
      },
      &*config.xoffset.begin(),
      &*config.xoffset.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_y), _1),
        bind(&convert_unit_relative, clip.h, _1)
      },
      &*config.y.begin(),
      &*config.y.end());

  convert_units(
      {
        bind(&convert_unit_typographic, layer->dpi, layer->font_size.value, _1),
        bind(&convert_unit_user, scale_translate_fn(config.scale_y), _1),
        bind(&convert_unit_relative, clip.h, _1)
      },
      &*config.yoffset.begin(),
      &*config.yoffset.end());

  /* draw areas */
  Path path;

  for (size_t i = 0; i < config.x.size(); ++i) {
    auto sx = clip.x + config.x[i];
    auto sy = clip.y + clip.h - config.y[i];

    if (i == 0) {
      path.moveTo(sx, sy);
    } else {
      path.lineTo(sx, sy);
    }
  }

  auto y0 = clip.h * std::clamp(scale_translate(config.scale_y, 0), 0.0, 1.0);
  for (int i = config.x.size() - 1; i >= 0; --i) {
    auto sx = clip.x + config.x[i];
    auto sy = clip.y + clip.h - (config.yoffset.empty() ? y0 : config.yoffset[i]);
    path.lineTo(sx, sy);
  }

  path.closePath();

  FillStyle style;
  style.color = config.colors.empty()
      ? Color{}
      : config.colors[0];

  fillPath(layer, clip, path, style);

  return OK;
}

ReturnCode draw(
    std::shared_ptr<PlotAreaConfig> config,
    const LayoutInfo& layout,
    Layer* layer) {
  switch (config->direction) {
    case Direction::HORIZONTAL:
      return draw_horizontal(*config, layout, layer);
    case Direction::VERTICAL:
      return draw_vertical(*config, layout, layer);
    default:
      return ERROR;
  }
}

ReturnCode build(
    const Environment& env,
    const Expr* expr,
    ElementRef* elem) {
  /* set defaults from environment */
  auto config = std::make_shared<PlotAreaConfig>();

  /* parse properties */
  auto config_rc = expr_walk_map(expr_next(expr), {
    {"xdata", bind(&expr_to_measures, _1, &config->x)},
    {"ydata", bind(&expr_to_measures, _1, &config->y)},
    {"xoffsetdata", bind(&expr_to_measures, _1, &config->xoffset)},
    {"yoffsetdata", bind(&expr_to_measures, _1, &config->yoffset)},
    {"xmin", bind(&expr_to_float64_opt, _1, &config->scale_x.min)},
    {"xmax", bind(&expr_to_float64_opt, _1, &config->scale_x.max)},
    {"xscale", bind(&scale_configure_kind, _1, &config->scale_x)},
    {"xscale-padding", bind(&expr_to_float64, _1, &config->scale_x.padding)},
    {"ymin", bind(&expr_to_float64_opt, _1, &config->scale_y.min)},
    {"ymax", bind(&expr_to_float64_opt, _1, &config->scale_y.max)},
    {"yscale", bind(&scale_configure_kind, _1, &config->scale_y)},
    {"yscale-padding", bind(&expr_to_float64, _1, &config->scale_y.padding)},
    //{"direction", bind(&expr_to_direction, _1, &config->direction)},
    {"color", expr_tov_fn<Color>(bind(&expr_to_color, _1, _2), &config->colors)},
    {"colors", expr_tov_fn<Color>(bind(&expr_to_color, _1, _2), &config->colors)},
  });

  if (!config_rc) {
    return config_rc;
  }

  /* check configuraton */
  if (config->x.size() != config->y.size()) {
    return ReturnCode::error(
        "EARG",
        "the length of the 'xs' and 'ys' properties must be equal");
  }

  if (!config->xoffset.empty() &&
      config->xoffset.size() != config->x.size()) {
    return ReturnCode::error(
        "EARG",
        "the length of the 'xs' and 'x-offsets' properties must be equal");
  }

  if (!config->yoffset.empty() &&
      config->yoffset.size() != config->y.size()) {
    return ReturnCode::error(
        "EARG",
        "the length of the 'ys' and 'y-offsets' properties must be equal");
  }

  /* scale autoconfig */
  for (const auto& v : config->x) {
    if (v.unit == Unit::USER) {
      scale_fit(v.value, &config->scale_x);
    }
  }

  for (const auto& v : config->xoffset) {
    if (v.unit == Unit::USER) {
      scale_fit(v.value, &config->scale_x);
    }
  }

  for (const auto& v : config->y) {
    if (v.unit == Unit::USER) {
      scale_fit(v.value, &config->scale_y);
    }
  }

  for (const auto& v : config->yoffset) {
    if (v.unit == Unit::USER) {
      scale_fit(v.value, &config->scale_y);
    }
  }

  *elem = std::make_shared<Element>();
  (*elem)->draw = bind(&draw, config, _1, _2);
  return OK;
}

} // namespace fviz::elements::chart::areas

