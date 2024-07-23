function samples = sample_gaussian2d(mu, sigma, num_samples)
    samples = mu + sigma * randn(num_samples, 2);
end

mu = 0;             % 平均
sigma = sqrt(.2);   % 標準偏差
num_samples = 1000; % サンプル数

% サンプリング
samples = sample_gaussian2d(mu, sigma, num_samples);

% プロット
figure;
plot(samples(:,1), samples(:,2), 'b.');
xlabel('X');
ylabel('Y');
title('2D Gaussian Distribution Samples');
axis equal;
grid off;