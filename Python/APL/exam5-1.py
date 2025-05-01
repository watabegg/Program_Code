import numpy as np

def count(digits: int) -> int:
    x_start = 0
    x_end = 2999
    
    # NumPy配列を作成
    x = np.arange(x_start, x_end + 1)
    
    b = (digits + 100) * 2
    
    # 条件を満たすx値の個数をカウント
    result = np.sum((-x**2 + b * x - 5000) > 0)
    
    return result

def main() -> None:
    digits = 166
    print(f"結果: {count(digits)}")

if __name__ == "__main__":
    main()