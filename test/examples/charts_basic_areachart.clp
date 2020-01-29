(default limit-y (0 20000000))
(default limit-x (1404278100 1404299700))

(plot/axes
    position (bottom left)
    label-format-y (scientific)
    label-format-x (datetime "%H:%M:%S"))

(plot/grid
    color #fff)

(plot/areas
    data-x (csv "test/testdata/measurement.csv" time)
    data-y (csv "test/testdata/measurement.csv" value1)
    color #888)
