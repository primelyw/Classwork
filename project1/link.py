class stuff:
    def __init__(self,num = None,nxt = None):
        self.num = num
        self.nxt = nxt

ship = [stuff(i,None) for i in range(30)]
for i in range(29):
    ship[i].nxt = ship[i+1]
ship[29].nxt = ship[0]

ans = []
total = 0
cur = ship[0]
pre = ship[29]

for i in range(15):
    cnt = 0
    for j in range(8):
        cur = cur.nxt
        pre = pre.nxt
    ans.append(cur.num)
    pre.nxt = cur.nxt
    tmp = cur
    del(tmp)
    cur = cur.nxt
print ans
