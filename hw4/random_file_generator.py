import random

x = int(input("HOw many inputs? :"))
y = input("Input file name : ")
f = open(y, "w")
count = 0
for i in range(x):
    w = random.randrange(1,20)
    v = random.randrange(1,50)
    data = str(w)+" "+str(v)+"\n"
    f.write(data)
    count+=w


print("weight : %d" %(count))
y = int(input("Knapsack Weights? :"))
data = str(y) + " -1\n"
f.write(data)

f.close()

