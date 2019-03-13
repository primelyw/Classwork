stuff = [1 for i in range(30)]
cnt = 0
cur = 0
ans = []
while cnt <15:
    i = 0
    while i < 8:
        if stuff[(cur+1)%30] == 1:
            i+=1
        cur = (cur+1)%30
    ans.append(cur)
    stuff[cur] = 0
    while stuff[cur]==0: cur = (cur+1)%30
    cnt += 1
print ans
