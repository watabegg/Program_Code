% Octave 6.2.0 と MATLAB 2021a で動作確認済み

I = imread( '../img/Mandrill.png' );
I = im2double( I );

len = 10;
ang = 20;
K = fspecial( 'motion', len, ang );


padd_mode = 'replicate';

J = imfilter( I, K, 'conv', padd_mode );

figure(1), imshow( [I, J] );
figure(2), imagesc( K ); axis image;



FI = fft2( I );

[sy,sx,sc] = size( I );
FK = psf2otf( K, [sy,sx] );

FJ = FI .* FK;

J_ft = real( ifft2( FJ ) );

figure(3), imshow( [J, J_ft, J-J_ft+0.5] );




K = [1; 2; 1]/4 * [-1 0 1]/2;

J = imfilter( I, K, 'corr', padd_mode );

[sy,sx,sc] = size( I );
FI = fft2( I );
FK = psf2otf( K, [sy,sx] );

FJ = FI .* conj( FK );
J_ft = real( ifft2( FJ ) );

figure(4), imshow( [J, J_ft, J-J_ft]+0.5 );



c = 1;
FI_abs = abs( FI(:,:,c) );
FJ_abs = abs( FJ(:,:,c) );
FK_abs = abs( conj(FK) );

DB = @(X) log10( X + 0.01 );

figure(5), meshz( DB( FI_abs ) );
figure(6), meshz( DB( FK_abs ) );
figure(7), meshz( DB( FJ_abs ) );



rate = 1/50;
dy = round( sy/2*rate );
dx = round( sx/2*rate );

FK_cut = zeros(sy,sx);
FK_cut( 1:dy, : ) = 1;  FK_cut( end-dy+1:end, : ) = 1;
FK_cut( :, 1:dy ) = 1;  FK_cut( :, end-dx+1:end ) = 1;

figure(8), meshz( DB( FK_cut ) );

FI_cut = FI .* FK_cut;
figure(9), meshz( DB( abs( FI_cut(:,:,c) ) ) );

I_cut = real( ifft2( FI_cut ) );
figure(10), imshow( [I, I_cut, I-I_cut+0.5] );



Iycc = rgb2ycbcr( I );

FK_ycc = cat( 3, ones(sy,sx), FK_cut, FK_cut );

FIycc = fft2( Iycc );
FIycc_cut = FK_ycc .* FIycc;
Iycc_cut = real( ifft2( FIycc_cut ) );

I_cut = ycbcr2rgb( Iycc_cut );

figure(11), imshow( [I,I_cut,I-I_cut+0.5] );
figure(12), imshow( Iycc(:,:) );
figure(13), imshow( Iycc_cut(:,:) );



K = fspecial( 'motion', 10, 30 );
J = imfilter( I, K, 'conv', padd_mode );

FJ = fft2( J );
FK = psf2otf( K, [sy,sx] );

FI_deconv = (conj(FK).*FJ) ./ (conj(FK).*FK + 0.001);

I_deconv = real( ifft2( FI_deconv ) );

figure(14), imshow( [J, I_deconv, I] );



R = I - I_deconv;
figure(15), imshow( R + 0.5 );

R_conv = imfilter( R, K, 'conv', padd_mode );
figure(16), imshow( R_conv + 0.5 );

s = 5;
J_r = imfilter( I + s*R, K, 'conv', padd_mode );
figure(17), imshow( [J, J_r] );























































































