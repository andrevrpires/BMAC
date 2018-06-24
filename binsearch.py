def binsearch(v, ini, fim, busca):

	ref = int((fim - ini)/2 + ini)

	if busca == v[ref]:
		print(v[ref])
	else:
		if ini == fim:
			print("nao encontrado")
		else:
			if v[ref] < busca:
				return binsearch(v, ref+1, fim, busca)
			else:
				return binsearch(v, ini, ref-1, busca)

x = [0,1,2,3,4,5]

binsearch(x, 0, 5, 0)

binsearch(x, 0, 5, 6)
