(layer/resize 1024px 512px)
(layer/set-dpi 96)

(figure/plot
    points (
        limit-x (0 10)
        limit-y (0 10000)
        scale-y (log)
        data-x (2 4 6 8)
        data-y (5 50 500 5000)))