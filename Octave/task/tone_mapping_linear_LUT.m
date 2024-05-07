function Y = tone_mapping_linear_LUT( X, a, b )

Y = a * X + b;
Y = max(0,min(1,Y));

end
