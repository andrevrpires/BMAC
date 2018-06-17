import math


##### FUNÇÕES ##############################


def Integral_Retangulo(a, b, M, f):

	contador = 0	
	int_retangulo = 0
	d = (b-a)/M

	while (contador <= M ):

		int_retangulo += f(a+(contador*d))*d
		
		contador+=1
	
	return int_retangulo

def Integral_Trapezio(a, b, M, f):

	contador = 0
	int_trapezio = 0
	d = (b-a)/M

	while (contador <= M ):

		int_trapezio += (f(a+(contador*d))+f(a+((contador+1)*d)))*d/2
		
		contador+=1

	return int_trapezio

def Polinomio(x):

	return 3*(x**3) +2*(x**2) + x + 1

def Valor_Integral_Polinomio(a, b):

	return (3/4)*(b**4) + (2/3)*(b**3) + (b**2)/2 + b - (3/4)*(a**4) - (2/3)*(a**3) - (a**2)/2 - a

def main():

	continuar = "s"

	while True:
	
		#verificação do "s"
		if continuar == "s":

			#entrada dos dados
			
			#a e consistência	
			a = input("\nEntre com o limite inferior do intervalo: ")
	
			while not str.isdigit(a):

				print("O limite inferior deve ser um número")
				a = input("\nEntre com o limite inferior do intervalo: ")
			
			a = float(a)
			
			#b e consistência
			b = input("Entre com o limite superior do intervalo: ")
			
			while not str.isdigit(b):

				print("O limite superior deve ser um número")
				b = input("\nEntre com o limite superior do intervalo: ")
			
			b = float(b)

			#M e consistência
			M = input("Entre com a quantidade de subintervalos: ")	
			
			while not isinstance(M, int):

				try:

					M = int(M)

				except ValueError:
				
					print("A quantidade de subintervalos deve ser um número inteiro")
					M = input("\nEntre com a quantidade de subintervalos: ")
			

			#saída de dados
		
			print("\nFunção Cosseno\n")
			print("Integral pelo método dos retângulos: ", Integral_Retangulo(a, b, M, math.cos))
			print("Integral pelo método dos trapézios: ", Integral_Trapezio(a, b, M, math.cos))
			print("Integral usando a função intrínseca: ", (math.sin(b) - math.sin(a)))
		
			print("\nFunção Seno\n")
			print("Integral pelo método dos retângulos: ", Integral_Retangulo(a, b, M, math.sin))
			print("Integral pelo método dos trapézios: ", Integral_Trapezio(a, b, M, math.sin))
			print("Integral usando a função intrínseca: ", (math.cos(a) - math.cos(b)))
	
			print("\nFunção Exponencial\n")
			print("Integral pelo método dos retângulos: ", Integral_Retangulo(a, b, M, math.exp))
			print("Integral pelo método dos trapézios: ", Integral_Trapezio(a, b, M, math.exp))
			print("Integral usando a função intrínseca: ", (math.exp(b) - math.exp(a)))
			
			print("\nFunção Polinomial\n")
			print("Integral pelo método dos retângulos: ", Integral_Retangulo(a, b, M, Polinomio))
			print("Integral pelo método dos trapézios: ", Integral_Trapezio(a, b, M, Polinomio))
			print("Integral usando a própria integral do polinômio: ", Valor_Integral_Polinomio(a, b), "\n")
		
		#verificação do "n"
		elif continuar == "n":

			break

		#consistência
		else:
			print("ATENÇÃO: responda com \"s\" ou \"n\"")
			continuar = input("Continuar? (s/n)")

		continuar = input("\nContinuar? (s/n)")

##### EXECUÇÃO ##############################



main()
