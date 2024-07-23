% パラメータ設定
mu_list = {[0, 0], [5, 5], [6, 0]};
sigma_list = [0.9, 0.8, 1.0];
num_samples = 1000;
% ランダムサンプル生成
data = rand_mixture_of_gaussians(mu_list, sigma_list, num_samples);
% プロット設定
figure;
plot(data(:,1), data(:,2), 'b.');
xlabel('x');
ylabel('y');
axis equal;

% k-meansクラスタリングの実行
k = 3;
[centroids, labels, obj_values] = kmeans(data, k);
% プロット設定
figure;
% 元のデータプロット
subplot(2, 2, 1);
scatter(data(:, 1), data(:, 2), 50, 'b', 'flled');
title('Original Data Points');
axis equal;
set(gca, 'xtick', [], 'ytick', []); % tickの線を非表示
% クラスタリング後のデータプロット
subplot(2, 2, 2);
hold on;
colors = hsv(k); % 動的に色を生成
for i = 1:k
scatter(data(labels == i, 1), data(labels == i, 2), 50, colors(i, :), 'flled');
end
scatter(centroids(:, 1), centroids(:, 2), 100, 'k', 'flled', 'd'); % クラスタ中心をプロット
title('k-means Clustering');
axis equal;
set(gca, 'xtick', [], 'ytick', []);
hold off;
% 目的関数の収束の様子をプロット
subplot(2, 2, [3, 4]);
plot(obj_values, '-o', 'LineWidth', 2, 'MarkerSize', 4);
title('Objective Function Convergence');
xlabel('Iteration', 'fontsize', 12);
ylabel('Objective Function Value', 'fontsize', 12);
grid on;
