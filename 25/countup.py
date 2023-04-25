import asyncio

ct = 0
THREAD_COUNT_AMOUNT = 10000000

async def countup():
  global ct
  for i in range(THREAD_COUNT_AMOUNT):
    ct += 1

async def main():
  await asyncio.gather(
    countup(),
    countup(),
    countup(),
  )

  print(ct)

asyncio.run(main())