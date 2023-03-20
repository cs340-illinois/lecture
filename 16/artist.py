from pymongo import MongoClient
mongo = MongoClient('localhost', 27017)
db = mongo["17-artist-database"]

store = db["waf"]
doc = store.find_one({
  "Favorite Artist": {"$exists": True }
})

if doc:
  print("Favorite Artist: ")
  print(doc)
else:
  store.insert_one({
    "Favorite Artist": "Taylor Swift"
  })
  print("Added Favorite Artist!")
