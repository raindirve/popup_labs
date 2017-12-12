from subprocess import call

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def posmod(a, m):
	return ((a % m) + m) % m

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        #raise Exception('modular inverse does not exist')
        return -1
    else:
        return posmod(x, m)
import random as r
import io
def gentc():
	n = r.randint(1, 1e1)
	t = 8
	a = r.randint(0, n-1)
	b = r.randint(0, n-1)
	f = open("_pytc", "w")
	f.write(str(n) + " " + str(t) + "\n")
	f.write(str(a) + " + " + str(b) + "\n")
	f.write(str(a) + " - " + str(b) + "\n")
	f.write(str(a) + " * " + str(b) + "\n")
	f.write(str(a) + " / " + str(b) + "\n")
	f.write(str(b) + " + " + str(a) + "\n")
	f.write(str(b) + " - " + str(a) + "\n")
	f.write(str(b) + " * " + str(a) + "\n")
	f.write(str(b) + " / " + str(a) + "\n")
	f.write("0 0\n")
	f.close()
	return a,b,n
	
def genans(a, b, n):
	l = []
	l.append(posmod(a+b, n))
	l.append(posmod(a-b, n))
	l.append(posmod(a*b, n))
	if(modinv(b, n) == -1):
		l.append(-1)
	else:
		l.append(posmod(a*modinv(b, n), n))
	l.append(posmod(b+a, n))
	l.append(posmod(b-a, n))
	l.append(posmod(b*a, n))
	if(modinv(a, n) == -1):
		l.append(-1)
	else:
		l.append(posmod(b*modinv(a, n), n))
	return l
	
	
	
import os
def makeruntc():
	a,b,n = gentc()
	ans = genans(a,b,n)
	f = os.popen("./modmath < _pytc")
	cans = list(f)
	l = [int(x.strip()) for x in cans]
	if( l != ans):
		print(ans)
		print(l)
	
	return l == ans, a,b,n
	
	
i = 0;
while True:
	win,a,b,n = makeruntc();
	if(not win):
		print(a,b,n)
		f = open("FAILEDAT", "w")
		f.write(str(a) +"\t"+ str(b) +"\t"+ str(n))
		f.close()
		break
	if(i%2 == 0):
		print("o\r",end="")
	else:
		print("x\r",end="")
		
	i += 1