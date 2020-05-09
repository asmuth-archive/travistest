(layer/resize 1600px 900px)
(layer/set-dpi 240)
(layer/set-font "Latin Modern Roman")

(tools/plotgen
    limit-x (0 400)
    limit-y (0 200)
    axes (
        label-placement-y (subdivide 5))
    points (
        data-x (csv test/testdata/gauss3d.csv x)
        data-y (csv test/testdata/gauss3d.csv y)
        shape (circle-o)
        colors (csv test/testdata/gauss3d.csv z)
        color-map (gradient (0 #aaa) (1.0 #000)))
    legend (
        position (bottom left)
        item (label "Random Data" marker-shape (circle-o))))
