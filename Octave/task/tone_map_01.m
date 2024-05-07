function  Y = tone_map_01( X, a, b )

Y = a * X + b;
Y = max(0,min(1,Y)); % 値域を [0,1] に修正

end % 関数の終了．書かなくても良い．
