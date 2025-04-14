def count(digits: int) -> int:
  count = 0

  x_start = 0
  x_end = 2999

  b = (digits + 100) * 2

  for x in range(x_start, x_end + 1):
    if -x**2 + b * x - 5000 > 0:
      count += 1

  return count

def main() -> None:
  digits = 166
  print(f"結果: {count(digits)}")

if __name__ == "__main__":
  main()