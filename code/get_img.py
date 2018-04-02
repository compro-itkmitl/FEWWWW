from urllib import request
file_ = open('url.txt', 'r')
read = file_.readlines()
file_.close()
c, count = 0, 0
for i in read:
    count += 1
    text = i
    if c != 85:
        text = i.replace('\n', '')
    name = open('user/user0.'+str(count)+'.jpg', 'wb')
    name.write(request.urlopen(text).read())
    name.close()


