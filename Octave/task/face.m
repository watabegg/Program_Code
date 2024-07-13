% Octave 6.2.0 と MATLAB 2021a で動作確認済み

load( 'images.mat' );

% imagesがセルアレイとして保存されているため、行列に変換
K = 17; % 画像の数
sample_image = images{1};
[sy, sx, sz] = size(sample_image); % 画像のサイズ
I_list = zeros(sy, sx, K);

for k = 1:K-1
    I_list(:,:,k) = double(images{k});
end

figure(1);
for k = 1:K-1
  subplot(4,4,k); imshow( uint8(I_list(:,:,k)) );
end



X = reshape( I_list, [sy*sx, K] ); # 顔画像をベクトル化

mu = mean( X, 2 ); # 平均顔
X_ = X - mu; # 平均顔を引く

C = (X_'*X_) / size(X,2); # 共分散行列

[V, D, ~] = svd( C ); # 固有値分解
%[V, D] = eig( C );



D_inv = diag( 1./diag(D) ); # 固有値の逆数を対角行列にする
%D_inv = inv( D );

U = X_ * V * sqrt( D_inv ); # 特異値行列

U_im = reshape( U, [sy,sx,K] ); # 画像に戻す

% figure(2);
% for k = 1:K-1
%   subplot(4,4,k); imagesc( U_im(:,:,k) );
%   axis image;
% end




W = sqrt(D)*V'; # 特異値行列

j = 2; # 4番目の固有顔

w_j = W(:,j); # 固有顔
y_j = U * w_j + mu; # 顔画像に戻す

J_j = reshape( y_j, [sy,sx] ); # 画像に戻す

% figure(3); imshow( uint8(J_j) );


j = 3; # 1番目の固有顔
l = 10; # 6番目の固有顔

y_jl = U(:,1:l) * W(1:l,j) + mu; # 顔画像に戻す

J_jl = reshape( y_jl, [sy,sx] ); # 画像に戻す

figure(4); imshow( uint8(J_jl) );



p = 3;
q = 10;
S = (4:-1:0)/4;

w_p = W(:,p);
w_q = W(:,q);


cnt = 0;
figure(5);
for s = S

  w = (1-s) * w_p + s * w_q;
  y_pq = U * w + mu;
  J_pq = reshape( y_pq, [sy,sx] );

  cnt = cnt + 1;
  subplot(1,length(S),cnt);
  imshow( uint8(J_pq) );

end
