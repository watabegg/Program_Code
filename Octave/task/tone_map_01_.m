function Y = tone_map_01_( X, range_src, range_dist )

x1 = range_src(1),   x2 = range_src(2);
y1 = range_dist(1),  y2 = range_dist(2);

T = [x1, 1; x2, 1];
Para = inv(T)*[y1; y2];
a = Para(1);  b = Para(2);

Y = a * X + b;
Y = max(0,min(1, Y ));
end
