import asyncio

async def fibonacci(x, tid):
  # Base Cases:
  if x == 0: return 0
  if x == 1: return 1

  print(f"{tid}: Calculating fibonacci({x})...")
  await asyncio.sleep(0.1)
  fx_minus1 = await fibonacci(x - 1, tid)
  fx_minus2 = await fibonacci(x - 2, tid)
  
  return fx_minus1 + fx_minus2

async def main():
  r = await asyncio.gather(
    fibonacci(15, "A"),
    fibonacci(14, "B"),
    fibonacci(13, "C"),
  )

  print(r)

asyncio.run(main())