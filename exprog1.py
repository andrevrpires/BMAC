###############################################################
#                                                             #
#  Exercício Programa n. 1 - Maquina de Venda de Produtos     #
#                                                             #
#  MAC110 - IMEUSP - BMAC - 1s 2018 - Prof. Marcilio          #
#                                                             #
#  Andre Vinicius Rocha Pires 10737290                        #
#                                                             #
###############################################################


##### Funcoes #################################################


def main():

	# Variáveis
	qtd = 0
	preco = 0
	vendidos = 0
	soma = 0
	verificacao = [ "0.05", "0.10", "0.25", "0.50", "1", "2", "5", "10" ]
	instrucao = "\nEsta máquina só aceita:\n\nMoedas de 0.05, 0.10, 0.25, 0.50, 1\nNotas de 2, 5, 10\n\nPara comprar, digite 0\nPara devolver o troco, digite -1\n"

	# Carregamento do programa
	print("\n* * * Máquina automática de Venda * * *\n")
	print("* * * Carga de quantidade e preço do produto * * *\n")

	# Entrada de quantidade de produtos, consistencia
	while (qtd < 1) or (qtd > 50):
		qtd = int(input("Entre com a quantidade do produto (valor entre 1 e 50): "))

	# Entrada do preco do produto, consistencia
	while (preco == 0) or ((preco % 5) != 0) :
		preco = int(float(input("Entre com o preco do produto (com duas casas decimais, multiplo de 0.05): "))*100)

	# Instrucao de venda
	print("\n\n* * * Venda do Produto * * *\n\n")
	print(instrucao)

	# Início da operacao
 
	while True:

		#aguarda input
		dado = input("\nAguardando Entrada: ")

		# caso insercao de credito, faz consistência do input
		if dado in verificacao:
		
			# se deu certo, soma os créditos
			dado = int(float(dado)*100)
			soma += dado
			print ("Crédito Atual = ","%5.2f" %(float(soma)/100))
	
		# caso compra
		elif dado == "0":
		
			# checa se tem produto disponível
			if qtd == 0:
				print("Não há produto para vender")
		
			# checa se tem crédito suficiente
			elif soma < 175:
				print("Crédito insuficiente = ","%5.2f" %(float(soma)/100))
		
			# se deu certo, debita dos créditos e dos produtos, e printa o crédito restante
			else:
				soma -= preco
				qtd -= 1
				vendidos += 1
				print("Produto Vendido")
				print ("Crédito Atual = ","%5.2f" %(float(soma)/100))

		# caso devolver troco
		elif dado == "-1":
	
			# testa se tem troco pra devolver
			if soma == 0:
				print("Não há troco a ser devolvido")
			else:	
				# variáveis que contam o troco
				conta1 = 0
				conta050 = 0
				conta025 = 0
				conta010 = 0
				conta005 = 0

				# printa o crédito restante
				print("Troco de ", "%5.2f" %(float(soma)/100), " reais - composto de:")

				# subtrai das notas/moedas maiores para as menores e conta quantas notas/moedas foram usadas	
				while soma >= 100:
					soma -=	100
					conta1 += 1

				while soma >= 50:
					soma -=	50
					conta050 += 1

				while soma >= 25:
					soma -=	25
					conta025 += 1

				while soma >= 10:
					soma -=	10
					conta010 += 1	

				while soma >= 5:
					soma -= 5
					conta005 += 1

				# printa as notas/moedas usadas e quantidades
				if conta1 > 0:
					print("   ", conta1, " moeda(s) de um reais")
				if conta050 > 0:
					print("   ", conta050, " moeda(s) de cinquenta centavos")
				if conta025 > 0:
					print("   ", conta025, " moeda(s) de vinte e cinco centavos")	
				if conta010 > 0:
					print("   ", conta010, " moeda(s) de dez centavos")
				if conta005 > 0:
					print("   ", conta005, " moeda(s) de cinco centavos")	

		# caso printar qtd produtos vendidos e valor vendido 
		elif dado == "-2":
			print("Total de Produtos vendidos = ", vendidos)
			print("Valor total da venda até agora = ","%5.2f" %(float(preco*(vendidos))/100))

		# caso o usuário digite algum valor diferente dos previstos
		else:
			print("Valor Inválido")
			print(instrucao)


##### MAIN ####################################################


main()
