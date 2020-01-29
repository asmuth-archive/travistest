(width 2048px)
(height 800px)
(dpi 240)

(default limit-y (0 70))
(default limit-x (-0.05 2.05))

(plot/axes
    position (bottom)
    label-placement-x (linear-interval 0.2 0 2.1))

(plot/bars
    data-x (csv "test/testdata/stacked.csv" x)
    data-y (csv "test/testdata/stacked.csv" y4)
    width (1em)
    color #9fc3f5)

(plot/bars
    data-x (csv "test/testdata/stacked.csv" x)
    data-y (csv "test/testdata/stacked.csv" y3)
    width (1em)
    color #88ade0)

(plot/bars
    data-x (csv "test/testdata/stacked.csv" x)
    data-y (csv "test/testdata/stacked.csv" y2)
    width (1em)
    color #6393c9)

(plot/bars
    data-x (csv "test/testdata/stacked.csv" x)
    data-y (csv "test/testdata/stacked.csv" y1)
    width (1em)
    color #4c7bb0)

(figure/legend
    item (label "Variable D" color #9fc3f5)
    item (label "Variable C" color #88ade0)
    item (label "Variable B" color #6393c9)
    item (label "Variable A" color #4c7bb0))
