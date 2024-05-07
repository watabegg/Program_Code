% Octave 6.2.0 と MATLAB 2021a で動作確認済み

I = im2double( imread( '../images/23.png' ) );
Iycc = rgb2ycbcr( I );
Y = Iycc(:,:,1);

iy = 70; ix = 190;
r = 1;

Y_local = Y( iy-r:iy+r, ix-r:ix+r );

figure(1), imshow( Y );
hold on;
rectangle('Position', [ix-r,iy-r,2*r+1,2*r+1], ...
'EdgeColor', 'red', 'LineWidth', 3 );
hold off;

figure(2), imshow( imresize( Y_local, 4, 'nearest' ) );


Y_sorted = sort( Y_local(:) );
M = numel( Y_sorted );

if mod(M,2) == 1
  mu = Y_sorted( (M+1)/2 );
else
  mu = 0.5 * sum( Y_sorted( (M/2):(M/2+1) ) );
end

mean( Y_sorted )
mu




[sy,sx] = size( Y );
Y_out = zeros( sy, sx );

for ix = 1+r:sx-r
  for iy = 1+r:sy-r

    Y_local = Y( iy-r:iy+r, ix-r:ix+r );
    mu = median( Y_local(:) );
    Y_out( iy, ix ) = mu;

  end
end
figure(3), imshow( Y_out ); drawnow;



rate = 0.1;
Y_noise = imnoise( Y, 'salt & pepper', rate );

Y_med = medfilt2( Y_noise, [2*r+1, 2*r+1] );

figure(4), imshow( [Y_noise, Y_med] );


B_noise = Y_noise < 0.1 | Y_noise > 0.9;
figure(5), imshow( B_noise );

Y_switch = Y_noise;
Y_switch( B_noise ) = Y_med( B_noise );

figure(6), imshow( [Y_noise, Y_med, Y_switch] );



nTone = 256;
Tone = round( Y * (nTone-1) ) + 1;

Backet_idx = 1:nTone;

iy = 70;   ix = 190;
r = 5;

T_local = Tone( iy-r:iy+r, ix-r:ix+r );

Backet = hist( T_local(:), Backet_idx );
Backet_cum = cumsum( Backet );

figure(7), bar( Backet );
figure(8), plot( Backet_cum );



ix = 191; % 隣の画素

T_rem = Tone( iy-r:iy+r, ix-r-1 ); % 削除分
T_add = Tone( iy-r:iy+r, ix+r ); % 追加分

for i = 1:numel( T_rem )
  Backet( T_rem(i) ) = Backet( T_rem(i) ) - 1;
end
for i = 1:numel( T_add )
  Backet( T_add(i) ) = Backet( T_add(i) ) + 1;
end

% 以降同様
Backet_cum = cumsum( Backet );

total = numel( T_local );
half = total / 2;


if mod(total,2) == 1 % 奇数なら
  idx = find( Backet_cum > half, 1 );
  mu = idx;

else % 偶数の場合，直前の累積和がちょうど半値である可能性がある
  idx = find( Backet_cum > half, 1 );
  mu = idx;
  if ( Backet_cum( idx-1 ) == half )
     mu = 0.5 * ( mu + (idx-1) );
  end
end

% 通常のソートを用いた方法との比較
T_local = Tone( iy-r:iy+r, ix-r:ix+r );
median( T_local(:) )
mu

