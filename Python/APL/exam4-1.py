from math import factorial

def calculate_group_combinations():
    
    combinations = factorial(10) // (factorial(5) * factorial(10 - 5))
    
    unique_combinations = combinations // 2
    
    return unique_combinations

if __name__ == "__main__":
    result = calculate_group_combinations()
    print(f"10人を5人ずつの2グループに分ける組み合わせの数: {result}")