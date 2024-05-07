% Octave 6.2.0 と MATLAB 2021a で動作確認済み

clear all;
close all;
clc;


I = im2double( imread( '../images/family.png' ) );
Iycc = rgb2ycbcr( I );
G = Iycc(:,:,1); % use G instead Y, Y is used later

N = 256; % the number of tones

% conversion from luminance to [1,N] indexes
Tone = round( G * (N-1) ) + 1;


%
% Tone mapping for representative luminance values.
%

% reprensentative luminance values
X = (0:N-1)/(N-1);

% linear
%Y = tone_mapping_linear_LUT( X, 1.5, -0.1 );

% cubic spline
Y = tone_mapping_cubic_spline_LUT( X, [0,0.3,1], [0,0.4,1] );


%
% write the results out to the output image pixels
%

G_out = G;
for i = 1:numel(G)
	tone = Tone(i);
	G_out(i) = Y(tone);
end


%
% write the results out to the output image pixels
%

Jycc = Iycc;
Jycc(:,:,1) = G_out; % equal to Jycc = cat( 3, G_out, Iycc(:,:,1:2) );
J = ycbcr2rgb( Jycc );
figure(1), imshow( [I,J] );

%
% 関数，スクリプトファイルの一番下か，外部に関数ファイルとして用意する．
%
% Octave ではこの書き方は動かない．
% MATLAB のみ可能．
%

%
% -------------------------------------------------------------------------
%

function Y = tone_mapping_linear_LUT( X, a, b )

Y = a * X + b;
Y = max(0,min(1,Y));

end

%
% -------------------------------------------------------------------------
%

function Y = tone_mapping_cubic_spline_LUT( X, px, py )

b = [py(1); 0; py(2); 0; 0; 0; py(3); 0];

x1 = px(1);
A1 = [ x1^3, x1^2, x1, 1, 0, 0, 0, 0;
	3*x1,    1,  0, 0, 0, 0, 0, 0;];

x3 = px(3);
A3 = [0, 0, 0, 0, x3^3, x3^2, x3, 1;
	0, 0, 0, 0, 3*x3,    1,  0, 0;];

x2 = px(2);
A2 = [
	x2^3, x2^2, x2, 1,       0,     0,   0,  0;
	x2^3, x2^2, x2, 1,   -x2^3, -x2^2, -x2, -1;
	3*x2^2, 2*x2,  1, 0, -3*x2^2, -2*x2,  -1,  0;
	3*x2,   1,  0, 0,   -3*x2,   -1,   0,  0;];

A = [A1; A2; A3];
p = inv(A)*b;

pori = @(X,P) P(1)*X.^3 + P(2)*X.^2 + P(3)*X + P(4);
figure(2), plot( X, pori(X,p(1:4)), X, pori(X,p(5:8)) );

Y = zeros( size(X) );
for i = 1:numel( X )
	x = X(i);

	% find the section by linear search
	ind = find( px >= x, 1 ) - 1;
	ind = max( 1, ind );

	Y(i) = pori( x, p((4*ind-3):(4*ind)) );
end
figure(3), plot( X, Y );

end
