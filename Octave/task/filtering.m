I = im2double( imread('./img/Morita.jpg') );
Iycc = rgb2ycbcr( I );
Y = Iycc(:,:,1);

rate_sp = 0.1;
Y_rate_sp = imnoise( Y, 'salt & pepper', rate_sp );

figure(1), imshow(Y_rate_sp);

std_gauss = 0.1;
Y_gauss = imnoise( Y, 'gaussian', 0, std_gauss^2 );

figure(2), imshow(Y_gauss);

m_r = 1; %小さいとノイズを取り除けず、大きいとエッジがなくなる

% 空間フィルタ（ガウシアンフィルタを使用）
ss = 1; % 空間フィルタの標準偏差 (standard deviation for spatial)
g_r = round(3*ss);

Ks = fspecial('gaussian', 2*[g_r,g_r]+1, ss);
Ks = Ks / sum( Ks(:) );

% レンジフィルタ　関数の定義（ガウス関数を使用）
sr = 0.1; % レンジフィルタの標準偏差 (standard deviation for range)
k_r = @(X,xi,sr) exp( (-0.5/sr^2)*(X-xi).^2 );


T = 10;
psi = @(X,t,T) max(0,-abs(X-t)/(1/T)+1);

% --- solt & pepper noise -> bilateral filter ---

Nume = zeros( size(Y_rate_sp) );

for t = 0:1/T:1
    PI = psi( Y_rate_sp, t, T ) .* Y_rate_sp;
    PI_s = imfilter( PI, Ks, 'corr', 'replicate' );
    Nume = Nume + k_r( Y_rate_sp, t, sr ) .* PI_s;
end

Deno = zeros( size(Y_rate_sp) );
U = ones( size(Y_rate_sp) );

for t = 0:1/T:1
    PU = psi( Y_rate_sp, t, T ) .* U;
    PU_s = imfilter( PU, Ks, 'corr', 'replicate' );
    Deno = Deno + k_r( Y_rate_sp, t, sr ) .* PU_s;
end

Y_sp_bil = Nume ./ Deno;
figure(3), imshow( [Y_rate_sp, Y_sp_bil] );
figure(13), imshow( Y_sp_bil-Y_rate_sp );
K = im

% --- gauss noise -> bilateral filter ---

Nume = zeros( size(Y_gauss) );

for t = 0:1/T:1
    PI = psi( Y_gauss, t, T ) .* Y_gauss;
    PI_s = imfilter( PI, Ks, 'corr', 'replicate' );
    Nume = Nume + k_r( Y_gauss, t, sr ) .* PI_s;
end

Deno = zeros( size(Y_gauss) );
U = ones( size(Y_gauss) );

for t = 0:1/T:1
    PU = psi( Y_gauss, t, T ) .* U;
    PU_s = imfilter( PU, Ks, 'corr', 'replicate' );
    Deno = Deno + k_r( Y_gauss, t, sr ) .* PU_s;
end

Y_gauss_bil = Nume ./ Deno;

figure(4), imshow( [Y_gauss, Y_gauss_bil] );

Y_sp_med = medfilt2( Y_rate_sp, [2*m_r+1, 2*m_r+1] );
Y_gauss_med = medfilt2( Y_gauss, [2*m_r+1, 2*m_r+1]);

figure(5), imshow( [Y_rate_sp, Y_sp_med] );
figure(6), imshow( [Y_gauss, Y_gauss_med]);
