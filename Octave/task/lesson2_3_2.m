% Octave 6.2.0 と MATLAB 2021a で動作確認済み

%
% ２枚の画像の読み込み
%
I_dst = im2double( imread('../images/face1.png') );
I_src = im2double( imread('../images/face2.png') );

%Iycc_dst = rgb2ycbcr( I_dst );
%Iycc_src = rgb2ycbcr( I_src );
Iycc_dst = I_dst; % 追加
Iycc_src = I_src; % 追加

Jycc = Iycc_dst; % 追加


for c = 1:3   %  c は色のインデックス
    
    %
    % 各色成分の取り出し
    %
    %G_dst = Iycc_dst(:,:,1);
    %G_src = Iycc_src(:,:,1);
    G_dst = Iycc_dst(:,:,c); % 追加
    G_src = Iycc_src(:,:,c); % 追加
    
    
    %
    % ヒストグラムの計算と積分関数を取得
    %
    N = 256;
    X = (1:(N-1))/(N-1);
    
    H_dst = hist( G_dst(:), X ) / numel( G_dst );
    H_src = hist( G_src(:), X ) / numel( G_src );
    
    figure(5);
    subplot(2,2,1), imshow( G_dst );
    subplot(2,2,2), imshow( G_src );
    subplot(2,2,3), plot( X, H_dst, 'LineWidth', 2 );
    subplot(2,2,4), plot( X, H_src, 'LineWidth', 2 );
    
    F_dst = cumsum( H_dst );
    F_src = cumsum( H_src );
    
    figure(6);
    subplot(1,2,1), plot( X, F_dst, 'LineWidth', 2 );
    subplot(1,2,2), plot( X, F_src, 'LineWidth', 2 );
    
    
    %
    % トーンマップ関数の作成
    %
    Y = ones( size(X) );
    for i = 1:N-1
        f_dst = F_dst( i );
        i_src = max( 1, find( F_src >= f_dst, 1 ) - 1 );
        
        if ~isempty( i_src )
            Y(i) = X( i_src );
        end
    end
    figure(7), plot( X, Y, 'LineWidth', 2 );
    
    
    %
    % 画素の走査と輝度値の変換
    %
    Tone = round( (N-1)*G_dst ) + 1;
    
    G_out = G_dst;
    for i = 1:numel( G_dst )
        tone = Tone( i );
        
        tone = max(1,min(N-1,tone) ); % 追加 範囲補正
        
        G_out( i ) = Y( tone );
    end
    
    H_out = hist( G_out(:), X );
    figure(8), bar( X, H_out );
    
    %
    % カラー画像への反映
    %
    %Jycc = Iycc_dst;
    %Jycc(:,:,1) = G_out;
    Jycc(:,:,c) = G_out;
    
end % 追加  for c = 1:3 に対応


%I_out = ycbcr2rgb( Jycc );
I_out = Jycc; % 追加

figure(9), imshow( [I_dst, I_out] );


