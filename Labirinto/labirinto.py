import numpy

def LeiaMatriz(Mat, NomeArq):

	# retorna True se conseguiu ler o arquivo e False caso contrário
	
	# abrir o arquivo para leitura
	try:
		arq = open(NomeArq, "r")
	except:
		print("\nErro no open")
		return False

	# ler cada uma das linhas do arquivo
	i = 0
	for linha in arq:

		# consistencia
		# se nao eh a primeira repeticao do laco, salva o numero de elementos da linha anterior
		if i != 0:
			numelementosantes = len(v)

		# se der alguma exception retorna False
		try:	   	
			# separa os elementos da string
			v = linha.split()

			# consistencia
			# se nao eh a primeira repeticao, agora checa se a linha tem o mesmo numero de elementos das anteriores
			if i != 0:
				if len(v) != numelementosantes:
					print("\nLinha", i, "do labirinto tem quantidade de elementos diferente das outras")
					return False
			
			# adiciona uma nova linha a matriz
			Mat.append([]) 

			# transforma os strings numéricos em números inteiros
			# e adiciona cada int à matriz
			for j in range(len(v)):
				
				# consistencia
				# checa se os elementos sao todos 0s e -1s
				if (v[j] == '0') or (v[j] == '-1'):
					Mat[i].append(int(v[j]))
				else:
					print("\nO elemento", j, "da linha", i, "nao eh 0 ou nao eh -1. Eh um \"", v[j], "\"")
					return False
				
			i = i + 1
	
		except:
			# algum erro no trecho acima
			print("\nErro no split, int ou nos appends")
			return False

	# fechar arquivo
	arq.close()
	return True


# printa a matriz

def PrintaMatriz(Mat):

	for i in range(len(Mat)):

		print(Mat[i])

	#print(Mat)

def numera_vizinhos(lab, linhas, colunas, k):

# Varre a matriz lab[0..n-1][0..m-1], procurando todos os elementos [i][j] tais que de lab[i][j] == k.
# Rotula com k+1 os vizinhos destes elementos (horizontal e vertical) que ainda não tenham sido rotulados.

	# controla se foi encontrado algum k
	flag = False

	#procura pelo k e rotula os vizinhos onde tem 0
	for i in range(linhas):

		for j in range(colunas):

			if lab[i][j] == k:

				# confirma que foi encontrado algum k
				flag = True

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
		numera_vizinhos(lab, linhas, colunas, k+1)


# def imprime_mais_distante(lab, n, m, dist):
# Imprime as posições com distância igual a dist. Usada para
# imprimir as posições de caminho máximo e sem caminho (dist = 0).


# copia matriz
def CopiaMatriz(Mat):

	matcopia = [len(Mat)]

	for i in range(len(Mat)):

		matcopia[i] = Mat[i][:]
	
	print(matcopia)

	return matcopia


# MAIN, exemplo de chamada da LeiaMatriz

# pede o nome do arquivo da matriz
arquivomatriz = "labirinto.txt" #input("Entre com o nome do arquivo: ")

# inicializa a matriz
mat = []

if (LeiaMatriz(mat, arquivomatriz)):

	# Imprime a matriz labirinto
	print("\nMatriz labirinto com", len(mat), "linhas por", len(mat[0]), "colunas.")
	PrintaMatriz(mat)

	# Imprime cada uma das matrizes numerada com os pesos dos caminhos
	
	# busca cada uma das portas nas extremidades
	# para isso, testa(mat[i][j] == 0) nas linhas extremas e nas colunas extremas

	# primeiro as linhas
	for i in range(len(mat[0])):


		# define/zera a matriz a ser alterada
		matnumerada = CopiaMatriz(mat)

		#busca as portas na primeira linha
		if matnumerada[0][i] == 0:
			
			#define a porta como 1
			matnumerada[0][i] = 1
	
			# numera
			numera_vizinhos(matnumerada, len(matnumerada), len(matnumerada[0]), 1)

			# printa
			print("\nMatriz labirinto numerada de porta [0][",i,"]")
			PrintaMatriz(matnumerada)
