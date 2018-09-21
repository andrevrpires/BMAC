def binsearch(v, busca):

	# busca binaria sem recursividade

	ini, fim = 0, len(v) - 1

	while ini <= fim:

		meio = (ini + fim)//2	

		'''
		print(ini)
		print(fim)
		print(meio)
		'''

		if busca == v[meio]:
			print("encontrado")
			return True
		else:
			if v[meio] < busca: ini = meio + 1
			
			else: fim = meio - 1

	print("nada encontrado")
	return False

x = [0,1,2,3,4,5]

y = [4]

print(binsearch(x, 0))

print(binsearch(x, 6))

print(binsearch(x, 3))

print(binsearch(y, 0))

print(binsearch(y, 4))
