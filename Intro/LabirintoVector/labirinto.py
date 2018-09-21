import numpy as np

### FUNCOES

def LeiaArquivo(v, NomeArq):

	# le o arquivo e joga numa matriz/vetor, linha a linha, separando os elementos da linha por espacos(split)
	# retorna True se conseguiu ler o arquivo e False caso contrário

	# abrir o arquivo para leitura
	try:
		arq = open(NomeArq, "r")
	except:
		print("\nErro no open")
		return False

	# ler cada uma das linhas do arquivo
	for linha in arq:

		# se der alguma exception retorna False
		try:
			#separa os elementos da string
			v.append(linha.split())

		except:
			# algum erro no trecho acima
			print("\nErro no split ou no append")
			return False

	# fechar arquivo
	arq.close()
	return True

def ChecaMatriz(v):

	# faz consistencia da matriz a ser usada, a partir do vetor/matriz da leitura do arquivo
	# retorna True se os dados estao ok, e False se nao estao

	# itera sobre o vetor
	for i in range(len(v)):

		for j in range(len(v[0])):

			# consistencia do numero de elementos por linha(devem ser iguais)
			if len(v[i]) != len(v[0]):
				print("A linha", i, "tem numero de elementos diferente da primeira linha")

			else: 
				# consistencia dos elementos da matriz labirinto
				if v[i][j] not in ("0", "-1"):
					print("\nO elemento", j, "da linha", i, "nao eh 0 ou nao eh -1. Eh um \"", v[i][j], "\"")
					return False

	return True

def numera_vizinhos(lab, linhas, colunas, k):

# Varre a matriz lab[0..n-1][0..m-1], procurando todos os elementos [i][j] tais que de lab[i][j] == k.
# Rotula com k+1 os vizinhos destes elementos (horizontal e vertical) que ainda não tenham sido rotulados.

	flag = False	# controla se foi encontrado algum k

	#procura pelo k e rotula os vizinhos onde tem 0
	for i in range(linhas):

		for j in range(colunas):

			if lab[i][j] == k:
	
				flag = True 	# confirma que foi encontrado algum k

				if (i+1 < linhas):
					if (lab[i+1][j] == 0):
						lab[i+1][j] = k + 1
				
				if (i-1 >= 0):
					if lab[i-1][j] == 0:
						lab[i-1][j] = k + 1
		
				if (j+1 < colunas):
					if lab[i][j+1] == 0:
						lab[i][j+1] = k + 1
		
				if (j-1 >= 0):
					if lab[i][j-1] == 0:
						lab[i][j-1] = k + 1
			
	# se foi encontrado algum k, tenta o proximo valor
	if flag:
	
		return numera_vizinhos(lab, linhas, colunas, k+1)

	else:

		return k - 1	#retorna ultimo k encontrado
	
def BuscaPortas(Mat):

	# busca cada uma das portas nas extremidades
	# para isso, testa(mat[i][j] == 0) nas linhas extremas e nas colunas extremas
	# retorna um vetor com os pares ordenados das portas		

	# inicializa vetor
	portas = []

	# primeiro as linhas extremas
	linhafim = len(Mat) - 1

	for i in (0, linhafim):
		
		for j in range(len(Mat[i])):

			#busca as portas
			if Mat[i][j] == 0:
				par = [i, j]
				portas.append(par)
	
	# agora colunas extremas
	colunafim = len(Mat[0]) - 1
			
	for i in range(1, linhafim):
		
		for j in (0, colunafim):

			#busca as portas
			if Mat[i][j] == 0:
				par = [i, j]
				portas.append(par)

	return portas

def BuscaCaminho(Mat, dist):
	
	# Imprime as posições com caminho máximo e sem caminho (dist = 0).

	# inicializa vetores
	posicoesmax = []
	posicoeszero = []

	for i in range(len(Mat)):
		
		for j in range(len(Mat[i])):

			#busca as portas
			if Mat[i][j] == 0:
				par = [i, j]
				posicoeszero.append(par)
			
			elif Mat[i][j] == dist:	
				par = [i, j]
				posicoesmax.append(par)

	return posicoesmax, posicoeszero

### MAIN

while True:

	# recebe o input do nome do arquivo do labirinto
	arquivolab = input("\n\nEntre com o nome do arquivo do labirinto: ")

	# inicializa o vetor que recebe os dados do arquivo
	vetor = []

	# checa se a leitura do arquivo teve sucesso
	if LeiaArquivo(vetor, arquivolab):

		# consistencia da matriz
		if ChecaMatriz(vetor):
		
			# transforma o vetor numa matriz numpy		
			lab = np.array(vetor).astype(int)

			# Imprime a matriz labirinto
			print("\nMatriz labirinto com", len(lab), "linhas por", len(lab[0]), "colunas.")	
			print(lab)

			# Imprime cada uma das matrizes numerada com os pesos dos caminhos
			labportas = (BuscaPortas(lab))

			for parporta in labportas:		

				# define/zera a matriz a ser alterada
				labnum = np.copy(lab)
	
				# define a porta como 1
				labnum[parporta[0]][parporta[1]] = 1
	
				# numera e guarda maior caminho
				maior = (numera_vizinhos(labnum, len(labnum), len(labnum[0]), 1))
			
				# busca maximos e sem caminho
				maximos, semcaminho = BuscaCaminho(labnum, maior)

				# Imprime
				print("\nPorta " + str(parporta))	
				print("Caminhos possiveis e comprimento:")
				print(labnum)
			
				print("\nPosicoes com caminho de maximo comprimento:")
				for parcaminho in maximos:
			
					print(parcaminho)
			
				print("\nPosicoes sem caminho:")
				for parcaminho in semcaminho:

					print(parcaminho)
