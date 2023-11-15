original_list = [5, 1, 2, 3, 4, 2]

result_list = [item for item in original_list for _ in range(item)]

print(result_list)
print(sum(original_list[:0]))