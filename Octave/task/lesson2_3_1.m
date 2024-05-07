% Octave 6.2.0 と MATLAB 2021a で動作確認済み

%
% 画像の読み込み
%
I = im2double(imread('./img/MtIbuki.jpg'));
Iycc = rgb2ycbcr( I );
G = Iycc(:,:,1);


%
% ヒストグラムの計算
%
N = 256;
X = (0:N-1)/(N-1);
H = hist( G(:), X );
H = H / sum(H);

figure(1), bar( X, H );
xlim( [0,1] );

%
% ヒストグラム平坦化用のトーンマップ関数の作成
%

% ヒストグラムを離散的な関数とみなして積分
F = cumsum( H ); % 累積和

% トーンマップ関数の表示
figure(2), plot( X, F );
xlim( [0,1] );  ylim([0,1]);   axis equal;


%
% 画素を走査し，輝度値を変換
%
Tone = round( (N-1)*G ) + 1;

G_out = G;
for i = 1:numel( G )
  tone = Tone( i );
  G_out( i ) = F( tone );
end

% 得られた画像のヒストグラムの表示
H_out = hist( G_out(:), X );
figure(3), bar( X, H_out );
xlim( [0,1] );

%
% カラー画像への反映
%
Jycc = Iycc;
Jycc(:,:,1) = G_out;
J = ycbcr2rgb( Jycc );
figure(4), imshow( [I,J] );
figure(5), imshow(J);
