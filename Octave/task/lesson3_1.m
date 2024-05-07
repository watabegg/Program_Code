% Octave 6.2.0 と MATLAB 2021a で動作確認済み

I = im2double( imread( '../images/balloon.png' ) );
Iycc = rgb2ycbcr( I );
Y = Iycc(:,:,1);

iy = 100; ix = 100;
r = 5;

Y_local = Y( iy-r:iy+r, ix-r:ix+r );

figure(1), imshow( Y );
hold on;
rectangle('Position', [ix-r,iy-r,2*r+1,2*r+1], ...
'EdgeCOlor', 'red', 'LineWidth', 3 );
hold off;

figure(2), imshow( imresize( Y_local, 4, 'nearest' ) );


Y_out = zeros( size( Y ) );

mu = mean( Y_local(:) );
% mu = sum( Y_local(:) );
% mu = mu / numel( Y_local );

Y_out( iy, ix ) = mu;

figure(3), imshow( Y_out );


[sy,sx] = size( Y );

for ix = 1+r:sx-r
  for iy = 1+r:sy-r

    Y_local = Y( iy-r:iy+r, ix-r:ix+r );
    mu = mean( Y_local(:) );
    Y_out( iy, ix ) = mu;
  end
end
figure(12), imshow( Y_out ); drawnow;

Y_struct = Y_out;
Y_detail = Y - Y_struct;
Y_reconst = Y_struct + 2*Y_detail;

figure(10), imshow( Y_detail + 0.5 );
figure(11), imshow( Y_reconst );



K = ones( 2*r+1, 2*r+1 );
K = K / sum( K(:) );

Y_out2 = zeros( size(Y ) );

for ix = 1+r:sx-r
  for iy = 1+r:sy-r

  Y_local = Y( iy-r:iy+r, ix-r:ix+r );

  KY = K .* Y_local;

  mu = sum( KY(:) );

  Y_out2( iy, ix ) = mu;

  end
end

figure(4), imshow( Y_out2 );


Y_out3 = filter2( K, Y, 'same' );

figure(5), imshow( Y_out3 );


ss = 2;

[CX,CY] = meshgrid( -r:r, -r:r );
D2 = CX.^2 + CY.^2;

Kg = exp( -D2 / (2*ss^2) );
Kg = Kg / sum( Kg(:) );

figure(6), meshz( Kg );

Y_out4 = filter2( Kg, Y, 'same' );
figure(7), imshow( Y_out4 );

wnd = 2*round( 4*ss ) + 1;

Kg = fspecial( 'gaussian', [wnd, wnd], ss );

figure(8), meshz( Kg );


[U,S,V] = svd( Kg, 'econ' );

diag( S )


s1 = S(1,1);
u1 = U(:,1);
v1 = V(:,1);

u1 = sqrt(s1) * u1;
v1 = sqrt(s1) * v1;

figure(8), plot( u1 );
figure(9), meshz( u1 * v1' );


tic
Yh = filter2( u1, Y, 'same' );
Yhv = filter2( v1', Yh, 'same' );
toc

figure(10), imshow( Yhv );

tic
Y_conv = conv2( Y, Kg, 'same' );
toc

figure(11), imshow( Y_conv );




tic
[sy,sx,sc] = size( Y );

FY = fft2( Y );
FK = conj(psf2otf( Kg, [sy,sx] ));

FY_out = FY .* FK;

Y_out5 = ifft2( FY_out );
Y_out5 = real( Y_out5 );

toc

figure(13), imshow( Y_out5 );




SAT = cumsum( Y, 1 );
SAT = cumsum( SAT, 2 );

iy = 100;  ix = 100;  r = 5;
area = (2*r+1)^2;


Y_local = Y( iy-r:iy+r, ix-r:ix+r );
mu_naive = sum( Y_local(:) ) / area;


a = SAT( iy-r-1, ix-r-1 ); b = SAT( iy-r-1, ix+r );
c = SAT( iy+r, ix-r-1 ); d = SAT( iy+r, ix+r );
mu_SAT = (a + d - b - c) / area;

mu_naive
mu_SAT


Y_out_SAT = zeros( size(Y) );

for ix = 1+r+1:sx-r
  for iy = 1+r+1:sy-r


a = SAT( iy-r-1, ix-r-1 ); b = SAT( iy-r-1, ix+r );
c = SAT( iy+r, ix-r-1 ); d = SAT( iy+r, ix+r );
Y_out_SAT(iy,ix) = (a + d - b - c);

end
end

Y_out_SAT = Y_out_SAT / area;

figure(14), imshow( [Y_out, Y_out_SAT] );
figure(15), meshz( Y_out(1+30:end-30,1+30:end-30) - Y_out_SAT(1+30:end-30,1+30:end-30) );




































































