def SomaLin(A, sl, sc):
	
	soma = 0

	for i in A:

		for j in i:

			soma += j

		sl.append(soma)
		soma = 0




mat = [[1,2,5],[1,2,2]]

linhas = []

colunas = []

SomaLin(mat, linhas, colunas)

print(linhas)
