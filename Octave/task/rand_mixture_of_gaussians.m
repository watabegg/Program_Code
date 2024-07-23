function samples = rand_mixture_of_gaussians(mu_list, sigma_list, num_samples)
    num_distributions = length(mu_list);
    samples_per_distribution = round(num_samples / num_distributions);
    samples = [];
    for i = 1:num_distributions
        mu = mu_list{i};
        sigma = sigma_list(i);
        % 指定されたガウス分布から2次元のサンプルを生成
        samples_i = bsxfun(@plus, mu, sigma * randn(samples_per_distribution, 2));
        samples = [samples; samples_i];
    end
    % 必要な数のサンプルに調整
    if size(samples, 1) > num_samples
        samples = samples(1:num_samples, :);
    end
end