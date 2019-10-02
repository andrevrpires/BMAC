from tqdm import tqdm_notebook # barra de progresso
import datetime as dt # para contar a tempo de processamento
from statistics import mean
import numpy as np # biblioteca para matrizes
import pandas as pd # biblioteca para dataframes
from scipy.io import mmread # biblioteca para ler o arquivo .mtx



def SOR(A, b, w, N, TOL = 10**(-5)):
    
    n = A.get_shape()[0] # obtendo o número de equações
    x0 = np.zeros(n) # inicializando o vetor iteração anterior
    x = np.zeros(n) # inicialmente, x = x0, e para evitar slices
    time_dot = np.empty(n) # inicializando o vetor de tempo de execução por linha
    mean_dot = np.empty(N) # inicializando o vetor de médias de tempo de execução
    # obtemos os valores da diagonal principal,
    # criamos nova matriz e zeramos a diagonal da nova matriz
    D = A.diagonal(0); newA = A.copy(); newA.setdiag(0); newA.eliminate_zeros()
    
    sum_dot = 0
    start_it = dt.datetime.today().timestamp()
    
    for k in tqdm_notebook(range(N)):
        
        for i in range(n):
            
            start_dot = dt.datetime.today().timestamp()
            #calculando a soma evitando slices
            summ = newA[i,].dot(x)
            time_dot[i] = dt.datetime.today().timestamp() - start_dot
            
            #calculando x[i]
            x[i] = (1-w)*x0[i] + (w*(- summ + b[i]))/D[i]
    
        sum_dot += sum(time_dot)
        mean_dot[k] = mean(time_dot)
        #norma da diferença entre o 'x atual' e o 'anterior'
        diff = np.linalg.norm(x - x0)
        #Se a tolerância foi atingida, interrompe o loop
        if diff < TOL: break
        #atualiza k e x0
        k += 1; x0[:] = x
        
    time_it = dt.datetime.today().timestamp() - start_it
    per_it = time_it/k
    per_dot = mean(mean_dot[:k+1])
    
    
    return diff, k, per_it, per_dot, sum_dot/time_it


def ConjGrad(A, b, N, TOL):
    
    n = A.get_shape()[0] # obtendo o número de equações
    x = np.zeros(n) # inicializando o vetor iteração anterior
    time_dot = np.empty(N) # inicializando o vetor
    
    r = b - A.dot(x) # inicializando r
    v = r # inicializando v
    alfa = r.dot(r) # calculando primeiro alfa
    
    start_it = dt.datetime.today().timestamp()
    
    for k in range(N):
        
        # primeiro critério de parada
        if np.linalg.norm(v) < TOL: break
    
        start_dot = dt.datetime.today().timestamp()
        u = A.dot(v)
        time_dot[k] = dt.datetime.today().timestamp() - start_dot
        t = alfa/v.dot(u)
        x = x + t*v
        r = r - t*u
        beta = r.dot(r)
        
        if beta < TOL: 
            if np.linalg.norm(r) < TOL: break
        
        s = beta/alfa
        v = r + s*v
        alfa = beta
    
    time_it = dt.datetime.today().timestamp() - start_it
    per_it = time_it/k
    per_dot = mean(time_dot[:k+1])
    
    return np.linalg.norm(r), k, per_it, per_dot, sum(time_dot[:k+1])/time_it


def table(file, N, TOL):
    
    # obtendo os valores para cálculo
    # obtém a matrix esparsa contida em um arquivo .mtx
    A = mmread(file).tocsr() # a matriz é retornada no formato CSR
    n = A.get_shape()[0] # obtendo o número de equações 
    b = A.dot(np.ones(n)) # vetor b, produto da matriz A com o vetor unitário
    nz = A.nnz # contando não zeros da matriz
    
    # gerando a tabela para receber os dados
    indexes = [1, 1.25, 1.5, 1.75, 2, 'CG']
    columns = ['erro','iterações', 'segs/iteração', 'segs/dotproduct', 'soma_dotproduct/iteração']
    table = pd.DataFrame(index = indexes, columns = columns) # inicializando
    table = table.rename_axis(index=('w'))
    
    # preenchendo a tabela
    print('n = ', n, ', não-zeros = ', nz,', densidade = ', nz/(n**2))
    for i, w in enumerate(tqdm_notebook(indexes)):
        
        if w == 'CG':
            table.loc[w] = ConjGrad(A, b, N, TOL)
        else:
            table.loc[w] = SOR(A, b, w, N, TOL)
        
    return table

print(table("Journals.mtx", 1000, 1e-10))
print(table("bcsstk01.mtx", 1000, 1e-10))
print(table("bcsstk02.mtx", 1000, 1e-10))
print(table("494_bus.mtx", 1000, 1e-10))


A = mmread("shallow_water1.mtx").tocsr()
n = A.get_shape()[0]
b = A.dot(np.ones(n))
nz = A.nnz
data = (ConjGrad(A, b, 1000, 1e-10))
print('n = ', n,
      '\nnão-zeros = ', nz,
      '\ndensidade = ', nz/(n**2),      
      '\nerro = ', data[0],
      '\niterações = ', data[1],
      '\nsegs/iteração = ', data[2],
      '\nsegs/dotproduct = ', data[3],
      '\nproporção = ', data[4])

A = mmread("shallow_water2.mtx").tocsr()
n = A.get_shape()[0]
b = A.dot(np.ones(n))
nz = A.nnz
data = (ConjGrad(A, b, 1000, 1e-10))
print('n = ', n,
      '\nnão-zeros = ', nz,
      '\ndensidade = ', nz/(n**2),      
      '\nerro = ', data[0],
      '\niterações = ', data[1],
      '\nsegs/iteração = ', data[2],
      '\nsegs/dotproduct = ', data[3],
      '\nproporção = ', data[4])