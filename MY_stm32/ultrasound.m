% 数据
actual_distance = [2.8, 5, 8.2, 10, 13, 18, 20, 21.5, 57.7, 92, 106, 109, 120, ...
    130, 140, 155, 156.5, 179, 189, 199, 217, 219, 225, 239, 259, ...
    267, 287, 307, 317, 327, 337, 300, 320, 350, 376, 400, 425, ...
    450, 475, 500, 530, 572];
measured_distance = [2.55, 4.73, 7.48, 9.78, 12.8, 18, 19.8, 21.1, 55.3, 90.4, ...
    104, 107.5, 118.5, 129.06, 138.7, 154, 155, 177.4, 188, 197.5, ...
    216.7, 218, 223.6, 238, 257.8, 267.3, 287.1, 306.7, 317.5, 327.4, ...
    337.6, 300, 319.42, 349, 378, 400.49, 425.9, 449.8, 475.5, 500, ...
    530.52, 572];

% 找到最小和最大测量距离
[~, minIndex] = min(actual_distance); % 最小实际距离的索引
[~, maxIndex] = max(actual_distance); % 最大实际距离的索引

% 线性拟合
coeffs = polyfit(actual_distance, measured_distance, 1); % 一次线性拟合
fit_line = polyval(coeffs, actual_distance);

% 绘制散点图
figure;
scatter(actual_distance, measured_distance, 'b', 'filled');
hold on;

% 添加拟合虚线
plot(actual_distance, fit_line, '--k', 'LineWidth', 1.5);

% 标记最小测量距离和最大测量距离
scatter(actual_distance(minIndex), measured_distance(minIndex), 'r', 'filled');
text(actual_distance(minIndex), measured_distance(minIndex), ...
    '最小测量距离2.55CM', 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');

scatter(actual_distance(maxIndex), measured_distance(maxIndex), 'g', 'filled');
text(actual_distance(maxIndex), measured_distance(maxIndex), ...
    '最大测量距离572CM', 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');

% 添加图形标签和标题
xlabel('实际距离 (厘米)');
ylabel('测量距离 (厘米)');
title('实际距离与测量距离的散点图');
legend('数据点', '拟合线', '最小测量距离', '最大测量距离', 'Location', 'Best');
grid on;
hold off;

% 显示拟合函数公式在左上角
equation = sprintf('y = %.4fx  %.4f', coeffs(1), coeffs(2)); % 格式化拟合公式
x_pos = min(actual_distance) + 3; % 左上角的 X 位置（稍微偏移一点）
y_pos = max(measured_distance) - 3; % 左上角的 Y 位置（稍微偏移一点）
text(x_pos, y_pos, equation, 'FontSize', 10, 'Color', 'black', 'HorizontalAlignment', 'left');