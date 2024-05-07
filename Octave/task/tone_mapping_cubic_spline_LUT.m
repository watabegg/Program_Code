function Y = tone_mapping_cubic_spline_LUT2( X, px, py )

b = [py(1); 0; py(2); 0; 0; 0; py(3); 0];

% 左側端点に関するもの
x1 = px(1);
A1 = [
    x1^3, x1^2, x1, 1, 0, 0, 0, 0;
    3*x1,    1,  0, 0, 0, 0, 0, 0;
    ];

% 右側端点に関するもの
x3 = px(3);
A3 = [
    0, 0, 0, 0, x3^3, x3^2, x3, 1;
    0, 0, 0, 0, 3*x3,    1,  0, 0;
    ];

% 中間点に関するもの
x2 = px(2);
A2 = [
    x2^3,   x2^2, x2, 1,       0,     0,   0,  0;
    x2^3,   x2^2, x2, 1,   -x2^3, -x2^2, -x2, -1;
    3*x2^2, 2*x2,  1, 0, -3*x2^2, -2*x2,  -1,  0;
    3*x2,      1,  0, 0,   -3*x2,  -1,   0,  0;
    ];

A = [A1; A2; A3];
p = inv(A)*b;

pori = @(X,P) P(1)*X.^3 + P(2)*X.^2 + P(3)*X + P(4);
figure(2), plot( X, pori(X,p(1:4)), X, pori(X,p(5:8)) );
Y = zeros( size(X) );

for i = 1:numel( X )
    x = X(i);
    ind = find( px >= x, 1 ) - 1;
    ind = max( 1, ind );
    Y(i) = pori( x, p((4*ind-3):(4*ind)) );
end

Y = max(0,min(1,Y));

figure(3), plot( X, Y );

end
