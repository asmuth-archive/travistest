/**
 * This file is part of the "plotfx" project
 *   Copyright (c) 2018 Paul Asmuth
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
#pragma once
#include <memory>
#include <string>
#include <vector>

namespace clip {
struct Property;

using PropertyList = std::vector<Property>;

enum class PropertyKind {
  MAP, TUPLE, LIST, ENUM, VALUE, VALUE_LITERAL
};

struct Property {
  std::string name;
  PropertyKind kind;
  std::unique_ptr<std::vector<Property>> next;
  std::string value;

  const Property& operator[](size_t i) const;
  size_t size() const;

  operator const std::string&() const;

};

bool is_map(const Property& prop);
bool is_list(const Property& prop);
bool is_tuple(const Property& prop);
bool is_enum(const Property& prop);
bool is_enum(const Property& prop, const std::string& cmp);
bool is_value(const Property& prop);
bool is_value(const Property& prop, const std::string& cmp);
bool is_value_literal(const Property& prop);
bool is_value_literal(const Property& prop, const std::string& cmp);
bool is_value_quoted(const Property& prop);
bool is_value_quoted(const Property& prop, const std::string& cmp);

std::vector<std::string> flatten(const Property& prop);

} // namespace clip

