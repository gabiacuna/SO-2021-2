import time
from datetime import datetime

now = str(datetime.now().time())
print(str(now))
print(type(now))

print(time.localtime())
# print(datetime.now().time())
# print(datetime.today())
# print(datetime.fromtimestamp(time.time()))