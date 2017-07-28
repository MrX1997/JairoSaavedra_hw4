import numpy as np
import matplotlib.pyplot as plt


datos=np.genfromtxt('map_data.txt',delimiter=' ')
punto= np.genfromtxt('datos.txt')
xp, yp, r =punto[:,0],punto[:,1],punto[:,2]

theta = np.linspace(0, 2*np.pi, 100)
pos = r.argmax()
r_ = r[pos].mean()
X = xp[pos]
Y = yp[pos]

x = r_*np.cos(theta) + X
y = r_*np.sin(theta) + Y

plt.plot(y, x)
plt.plot([Y], [X],'o',color='g')
plt.grid()	
plt.imshow(datos)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Punto Nemo')

plt.savefig("PuntoNemo.pdf")

