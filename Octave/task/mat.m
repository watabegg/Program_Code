% 画像が保存されているディレクトリを指定
image_dir = './face_img';

% ディレクトリ内のすべての画像ファイルのリストを取得
image_files = dir(fullfile(image_dir, '*.jpg')); % .jpg形式の画像の場合

% 画像を保存するための空のセルアレイを作成
images = cell(length(image_files), 1);

% 各画像を読み込み、グレースケールに変換し、セルアレイに格納
for i = 1:length(image_files)
    image_path = fullfile(image_dir, image_files(i).name);
    img = imread(image_path);
    gray_img = rgb2gray(img); % グレースケールに変換
    images{i} = gray_img;
end

% 画像をMATファイルとして保存
save('images.mat', 'images');
