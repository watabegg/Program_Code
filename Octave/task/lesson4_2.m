% Octave 6.2.0 と MATLAB 2021a で動作確認済み

X = magic(3);

x = X(:,1)
M = length( x );

fft(x)


k = 0:M-1;
m = 0:M-1;

Fv = exp( (complex(0,-2*pi)/M) * k' * m );

y = Fv * x



ifft( y )

1/M * conj(Fv) * y

inv( Fv )
1/M * conj(Fv)

1/M*Fv' * Fv




fft( X, [], 1 )

Y = Fv * X

1/M * conj(Fv) * Y





x = X(1,:)
N = length( x );

fft(x)


k = 0:N-1;
n = 0:N-1;

Fh = exp( (complex(0,-2*pi)/N) * k' * n );

x * Fh.'


fft( X, [], 2 )
X * Fh.'




fft2( X )

Y = Fv * X * Fh.'


ifft2( Y )

(1/M)*conj(Fv).' * Y * (1/N)*conj(Fh)



U = inv( Fv );
V = inv( Fh );

X = zeros( size( Y ) );

for j = 1:N
  for i = 1:M

ui = U(:,i);
vj = V(:,j);

yij = Y(i,j);

X = X + yij * ui * vj.';

end
end

X





X = imread( '../images/face8.jpg' );
X = im2double( X );
X = rgb2gray( X );
figure(1), imshow( X );


[M,N] = size( X );

DFTmtx = @(M) ...
  exp( complex(0,-2*pi)/M * (0:M-1)' * (0:M-1) );
  

Fv = DFTmtx( M );
Fh = DFTmtx( N );

Y = Fv*X*Fh.';
figure(2), imagesc( log( abs(Y) + 0.01 ) );




figure(3), imshow( [real( Fv ), imag( Fv )] );
figure(4), imshow( [real( Fh.'), imag( Fh.')] );



U = 1/M * conj( Fv );
figure(5), imagesc( [real( U ), imag( U )] );


V = 1/N * conj( Fh );
figure(6), imagesc( [real( V.'), imag( V.')] );



Z = zeros( size(X) );
for i = 1:20
for j = 1:20

ui = U(:,i);
vj = V(:,j);

yij = Y(i,j);

uvt = ui * vj.';

Z = Z + yij * uvt;

% figure(7), imagesc( [real(uvt), imag(uvt)] );
% figure(8), imagesc( real( Z ) ); axis image;
  drawnow;
end
end


[U,D,V] = svd(  X  );

figure(9), imagesc( U ); axis image;
figure(10), imagesc( V ); axis image;
figure(11), plot( diag( D ) );




Z = zeros( size(X) );
for i = 1:20

ui = U(:,i);
vi = V(:,i);

dij = D(i,i);

uvt = ui * vi.';

Z = Z + dij * uvt;

figure(7), imagesc( uvt );
figure(8), imagesc( real( Z ) ); axis image;
  drawnow;
end












