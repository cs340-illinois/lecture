import boto3
s3 = boto3.client(
  's3',
  endpoint_url='http://127.0.0.1:9000',
  aws_access_key_id='ROOTNAME',
  aws_secret_access_key='CHANGEME123'
)

# Create bucket if it does not exit:
try:
  s3.create_bucket(Bucket="cs340")
  print("Created `cs340` bucket!")
except:
  # bucket already exists
  print("Bucket `cs340` already exists!")

import json

# Add an object as a string:
s3.put_object(Bucket="cs340", Key="session_data", Body=json.dumps({"hello": "world"}))

# Upload a file:
s3.upload_file("cs340.png", Bucket="cs340", Key="profile-picture.png")
