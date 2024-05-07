function  Y = tone_map_02( X, a, b )

Y = X + a * tan( b * pi * (X - 0.5) );
Y = max(0,min(1,Y)); % 値域を [0,1] に修正

end % 関数の終了．書かなくても良い
