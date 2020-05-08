(width 2048px)
(height 800px)
(dpi 240)

(limit-x (0 24))
(scale-y (categorical (csv "test/testdata/gdp_per_capita_2010.csv" country)))

(axes
    position (left))

(bars
    data-x (csv "test/testdata/gdp_per_capita_2010.csv" gdp)
    data-y (csv "test/testdata/gdp_per_capita_2010.csv" country)
    labels (csv "test/testdata/gdp_per_capita_2010.csv" gdp_label)
    direction horizontal
    width (1.4em)
    color #4c7bb0)
