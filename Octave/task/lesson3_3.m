% Octave 6.2.0 と MATLAB 2021a で動作確認済み

Y = repmat( [ones(1,5), zeros(1,5)], [1,3] );
Y = Y + 0.1 * randn( size(Y) );
figure(1), plot( Y );

k_r = @(X,xi,tau) abs(X-xi) < tau;

i = 14;  yi = Y(i);
figure(11), hold on; plot(i,yi,'ro'); hold off;

Kr = k_r( Y, yi, 0.5 ); %  Kr = abs(Y-yi) < 0.5;
figure(2), plot( Kr );


KrY = Kr .* Y;
figure(21), hold on; plot( KrY ); hold off;



r = 2;
Ks = ones(1,2*r+1);
Ks = Ks/sum(Ks(:));

X = zeros( size( Y ) );

for i = 1+r:numel(Y)-r

yi = Y(i);
Yj = Y( i-r:i+r );

Kr = k_r( Yj, yi, 0.5 );


KsKr = Kr .* Ks;
KsKrY = Yj .* KsKr;


X(i) = sum( KsKrY ) / sum( KsKr );


end

figure(3), plot( X );





I = im2double( imread('../images/match.png') );
rate_sp = 0.1;
I = imnoise( I, 'salt & pepper', rate_sp );
[sy,sx,sc] = size( I );

% 空間フィルタ（ガウシアンフィルタを使用）
ss = 2; % 空間フィルタの標準偏差 (standard deviation for spatial)
r = round(3*ss);
Ks = fspecial('gaussian', 2*[r,r]+1, ss);

% レンジフィルタ　関数の定義（ガウス関数を使用）
sr = 0.1; % レンジフィルタの標準偏差 (standard deviation for range)
k_r = @(X,xi,sr) exp( (-0.5/sr^2)*(X-xi).^2 );


J = zeros( size(I) );


for ix = 1+r:sx-r
  for iy = 1+r:sy-r
    for ic = 1:sc
      ii = I(iy,ix, ic );
      Ij = I( iy-r:iy+r, ix-r:ix+r, ic );

      Kr = k_r( Ij, ii, sr );

      KsKr = Ks .* Kr;
      KsKrI = KsKr .* Ij;

      J(iy,ix,ic) = sum(KsKrI(:)) / sum(KsKr(:));
    end
  end
end
figure(4), imshow( [I, J] );
figure(14), imshow( [I-J] );


Ks = Ks / sum( Ks(:) );
figure(100), meshz( Ks );



T = 20;
psi = @(X,t,T) max(0,-abs(X-t)/(1/T)+1);

X = 0:0.01:1;
Y = psi( X, 0.15, T );
figure(101), plot( X, Y );

Nume = zeros( size(I) );

for t = 0:1/T:1
PI = psi( I, t, T ) .* I;
PI_s = imfilter( PI, Ks, 'corr', 'replicate' );
Nume = Nume + k_r( I, t, sr ) .* PI_s;
end

Deno = zeros( size(I) );
U = ones( size(I) );

for t = 0:1/T:1
PU = psi( I, t, T ) .* U;
PU_s = imfilter( PU, Ks, 'corr', 'replicate' );
Deno = Deno + k_r( I, t, sr ) .* PU_s;
end

J_fast = Nume ./ Deno;
figure(5), imshow( [I, J, J_fast] );
figure(15), imshow( [I-J_fast] );




























