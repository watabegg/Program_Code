def count_multiples_of_45():
    count = 0
    
    for a in range(1, 7): 
        for b in range(1, 7): 
            for c in range(1, 7): 
                for d in range(1, 7): 
                    n = a * 1000 + b * 100 + c * 10 + d
                    
                    if n % 45 == 0:
                        count += 1
    
    return count

result = count_multiples_of_45()
print(f"サイコロを4回振って得られる数のうち、45の倍数となる場合は{result}通りあります。")