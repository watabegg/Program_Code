import itertools

def count_arrangements():
    count_a_three_or_more = 0
    count_contains_ab = 0
    
    for combo in itertools.product(['a', 'b'], repeat=8):
        s = ''.join(combo)
        
        if s.count('a') >= 3:
            count_a_three_or_more += 1
        
        if 'ab' in s:
            count_contains_ab += 1
    
    return count_a_three_or_more, count_contains_ab

a_three_or_more, contains_ab = count_arrangements()

print(f"aが3回以上現れるものの総数: {a_three_or_more}")
print(f"abという並びをもつものの総数: {contains_ab}")