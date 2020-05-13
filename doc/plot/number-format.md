Formatters
==========

The `<format>` setting controls how values are formatted for display. Here
is the list of valid values:

  - [`fixed`](#format-fixed)
  - [`scientific`](#format-scientific)
  - [`datetime`](#format-datetime)
  - [`base`](#format-base)
  - [`integer`](#format-integer)


## List of `<format>` values

### `fixed`
<a id="format-fixed"></a>

The `fixed` label formatter will format values as decimal floating point numbers
with a fixed precision of `N` decimal places to the right of the decimal point.
If no parameter `N` is given, it defaults to one (1).

    (fixed)
    (fixed <N>)

Example: [`charts-reference/format_fixed`](/examples/charts-reference/format_fixed):
[![format_fixed.svg](/examples/charts-reference/format_fixed.svg)](/examples/charts-reference/format_fixed)


---
### `scientific`
<a id="format-scientific"></a>

The `scientific` formatter will format values using scientific notation. If a
precision `N` is provided, the significand will be formatted to `N` decimal places
to the right of the decimal point. If no parameter `N` is given, it defaults to
one (1).

    (scientific)
    (scientific <N>)

Example: [`charts-reference/format_scientific`](/examples/charts-reference/format_scientific):
[![format_scientific.svg](/examples/charts-reference/format_scientific.svg)](/examples/charts-reference/format_scientific)


---
### `datetime`
<a id="format-datetime"></a>

The `datetime` formatter formats Unix timestamps (given as integers) as human
readable date strings. The optional `<fmt>` format string uses the standard
`strftime` format specifiers and syntax.

    (datetime)
    (datetime <fmt>)

Example: [`charts-reference/format_datetime`](/examples/charts-reference/format_datetime):
[![format_datetime.svg](/examples/charts-reference/format_datetime.svg)](/examples/charts-reference/format_datetime)


---
### `base`
<a id="format-base"></a>

The `base` formatter will format values using an arbitrary base B and an optional
precision N.

    (base <B> <N>)

Example: [`charts-reference/format_base`](/examples/charts-reference/format_base):
[![format_base.svg](/examples/charts-reference/format_base.svg)](/examples/charts-reference/format_base)


---
### `integer`
<a id="format-integer"></a>

The `integer` formatter will format values as integers.

    (integer)

Example: [`charts-reference/format_integer`](/examples/charts-reference/format_integer):
[![format_integer.svg](/examples/charts-reference/format_integer.svg)](/examples/charts-reference/format_integer)
