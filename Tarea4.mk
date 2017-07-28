data_targets = datos.txt

PuntoNemo.pdf : datos.txt
	python Plots.py 

$(data_targets) : punto.x
	./punto.x

punto.x : PuntoGeographicPoint.c
	cc PuntoGeographicPoint.c -o punto.x -lm
 	
