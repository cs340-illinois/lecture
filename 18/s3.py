import boto3
s3 = boto3.client('s3', endpoint_url='http://127.0.0.1:9000', aws_access_key_id='ROOTNAME', aws_secret_access_key='CHANGEME123')

# Reading data from S3:
obj = s3.get_object(Bucket="cs340", Key="session_data")
f = obj["Body"]

print("== S3 Response ==")
print(obj)
print()

print("== Contents ==")
print(f.read().decode("utf-8"))
print()