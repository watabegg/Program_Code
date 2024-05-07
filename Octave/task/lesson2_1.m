% Octave 6.2.0 と MATLAB 2021a で動作確認済み

%
% 画像の読み込み
%
I = im2double( imread('./img/Morita.jpg' ) );
Iycc = rgb2ycbcr( I );
Y = Iycc(:,:,1);


%
% ヒストグラムを計算
%
bin_pos = 0:(1/255):1; % 0～1までを 256 等分
H = hist( Y(:), bin_pos ); % Y(:) で２次元配列を１次元に変換


%figure(1),  imshow( I );
%figure(2),  imshow( Y );
figure(3),  bar( bin_pos, H );
xlim([0,1]);


%
% 線形濃度変換，アフィン変換のトーンマップ関数
%
x1 = 0.061,   x2 = 0.91;
y1 = 0.0,   y2 = 1.0;

%x1 = 0.1,   x2 = 0.9;
%y1 = 0.3,   y2 = 0.6;
%x1 = 0.3,   x2 = 0.7;
%y1 = 0,     y2 = 1;

% パラメータの計算
T = [x1, 1; x2, 1];
Para = inv(T) * [y1; y2]; % 連立方程式を解く
a = Para(1);  b = Para(2);

Y_adj = a * Y + b; % 線形濃度変換
Y_adj = max(0,min(1, Y_adj )); % [0,1] の範囲外の値を丸め込み

% 関数版
% 関数本体は，このスクリプトファイルの最後に記載
% 通常は，外部に別の関数ファイルとして保存する

Y_adj = tone_map_01( Y, a, b );
% Y_adj = tone_map_01_( Y, [0.1,0.9], [0,1] );
% Y_adj = tone_map_02( Y, 0.1, 0.9 );

H_adj = hist( Y_adj (:), bin_pos );

%figure(4),  imshow( Y_adj );
figure(5),  bar( bin_pos, H_adj );
xlim([0,1]);

%
% カラー画像への反映
%
Jycc = Iycc;
Jycc(:,:,1) = Y_adj;

J = ycbcr2rgb( Jycc );

%figure(6), imshow( J );

figure(9), imshow([I, J]);

%
% R, G, B の各成分を処理する場合
%
J_1 = a * I + b;
J_1 = max(0,min(1,J_1));
%figure(7), imshow( J_1 );

%
% Y, Cb, Cr の各成分を処理する場合
%
Jycc = a * Iycc + b;
Jycc = max(0,min(1, Jycc));
J_2 = ycbcr2rgb( Jycc );
%figure(8), imshow( J_2 );


%
% トーンマップ関数の表示
%
X_sample = 0:0.01:1;
Y_sample = tone_map_02( X_sample, 0.1, 0.9 );

%figure, plot( X_sample, Y_sample );
%xlim( [0,1] ); % 描画範囲を [0,1] に収めたい場合
%ylim( [0,1] );



%
% 関数，スクリプトファイルの一番下か，外部に関数ファイルとして用意する．
%
% Octave ではこの書き方は動かない．
% MATLAB のみ可能．
%

function  Y = tone_map_01( X, a, b )

Y = a * X + b;
Y = max(0,min(1,Y)); % 値域を [0,1] に修正

end % 関数の終了．書かなくても良い．


function Y = tone_map_01_( X, range_src, range_dist )

x1 = range_src(1),   x2 = range_src(2);
y1 = range_dist(1),  y2 = range_dist(2);

T = [x1, 1; x2, 1];
Para = inv(T)*[y1; y2];
a = Para(1);  b = Para(2);

Y = a * X + b;
Y = max(0,min(1, Y ));
end


function  Y = tone_map_02( X, a, b )

Y = X + a * tan( b * pi * (X - 0.5) );
Y = max(0,min(1,Y)); % 値域を [0,1] に修正

end % 関数の終了．書かなくても良い







