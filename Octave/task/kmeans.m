function [centroids, labels, obj_values] = kmeans(data, k, max_iter=1000)
    n = size(data, 1); % データ点の数
    centroids = data(randperm(n, k), :); % 初期クラスタ中心の選定
    x2 = sum(data.^2, 2); % 各データ点の平方和
    prev_centroids = inf(k, size(data, 2)); % 前回のクラスタ中心
    labels = zeros(n, 1); % クラスタラベルの初期化
    obj_values = []; % 目的関数の値を記録するリスト
    for iter = 1:max_iter
        m2 = sum(centroids.^2, 2); % クラスタ中心の平方和
        d = m2 + x2' - 2 * centroids * data'; % 距離行列の計算（ブロードキャスティングを利用）
        [min_d, labels] = min(d, [], 1); % データ点の所属クラスタを求める
        for t = 1:k
            cluster_points = data(labels == t, :);
            if ~isempty(cluster_points)
                centroids(t, :) = mean(cluster_points, 1); % 新しいクラスタ中心の計算
            end
        end
        obj_values = [obj_values; sum(min_d)]; % 目的関数の値を記録
        if norm(centroids - prev_centroids) < 0.001 % 収束条件の判定
            break;
        end
        prev_centroids = centroids;
    end
end