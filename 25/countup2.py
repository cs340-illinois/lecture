import asyncio
import sys

ct = 0
THREAD_COUNT_AMOUNT = 10000000

async def countup(tid):
  global ct
  for i in range(THREAD_COUNT_AMOUNT):
    if i % 10000 == 0:
      sys.stdout.write(tid)
      sys.stdout.flush()
      
    ct += 1
    await asyncio.sleep(0)

async def main():
  await asyncio.gather(
    countup("A"),
    countup("B"),
    countup("C"),
  )

  print(ct)

asyncio.run(main())