% Octave 6.2.0 と MATLAB 2021a で動作確認済み

load( '../images/faces.mat' );

K = 32;
I_list = I_list(:,:,1:K);

[sy,sx] = size( I_list(:,:,17) );

figure(1);
for k = 17:K
  subplot(4,4,k-16); imshow( I_list(:,:,k) );
end



X = reshape( I_list, [sy*sx, K] );

mu = mean( X, 2 );
X_ = X - mu;

C = (X_'*X_) / size(X,2);

[V, D, ~] = svd( C );
%[V, D] = eig( C );



D_inv = diag( 1./diag(D) );
%D_inv = inv( D );

U = X_ * V * sqrt( D_inv );

U_im = reshape( U, [sy,sx,K] );

figure(2);
for k = 17:K
  subplot(4,4,k-16); imagesc( U_im(:,:,k) );
  axis image;
end




W = sqrt(D)*V';

j = 4;

w_j = W(:,j);
y_j = U * w_j + mu;

J_j = reshape( y_j, [sy,sx] );

figure(3); imshow( J_j );



j = 1;
l = 6;

y_jl = U(:,1:l) * W(1:l,j) + mu;

J_jl = reshape( y_jl, [sy,sx] );

figure(4); imshow( J_jl );



p = 5;
q = 15;
S = (4:0)/4;

w_p = W(:,p);
w_q = W(:,q);


cnt = 0;
for s = S

w = (1-s) * w_p + s * w_q;
y_pq = U * w + mu;
J_pq = reshape( y_pq, [sy,sx] );

cnt = cnt + 1;
figure(5); subplot(1,length(S),cnt);
imshow( J_pq );

end









































