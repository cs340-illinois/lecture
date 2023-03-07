import requests

r = requests.get("https://www.colr.org/json/color/random")
print(f"Status Code: {r.status_code}")
print(f"Character Encoding: {r.encoding}")

print("== Headers ==")
for header in r.headers:
  print(header + ": " + r.headers[header])

print("== Payload (text) ==")
print(r.text)

print("== Payload (json) ==")
data = r.json()
print(data["colors"][0]["hex"])
