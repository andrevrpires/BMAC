#!/usr/bin/python3

# este script cria uma planilha de patrimonios a partir de um memorando em pdf ou odt

import glob, zipfile, re, pyoo, textract #, subprocess


def removeXMLMarkup(s, replace_with_space):

    # remove marcacao XML de arquivos de texto(copiado e colado de loook)

    s = re.compile("<!--.*?-->", re.DOTALL).sub('', s)
    repl = ''
    if replace_with_space:
        repl = ' '
    s = re.compile("<[^>]*>", re.DOTALL).sub(repl, s)
    return s


def buscapatrim(texto,matriz,cabecalho):

    # extrai os patrimonios a partir de dados no formato texto    

    # em cada uma das linhas
    for l in texto:
        # procura palavra por palavra
        for w in l.split():
            # pelo padrao dos patrimonios
            if re.search("[2-6]\\d{5}", w):
                numero = re.sub("\D","",w)              
                if int(numero) < 699999:
                    # se o padrao foi encontrado, adiciona na matriz
                    linha = list(cabecalho)
                    linha.append(numero)
                    matriz.append(linha)


def cabecalhoodt(texto,cabecalho):

    # extrai o vetor cabecalho inteiro e com imperfeicoes
    listatexto = str.splitlines(texto)[1].split()
    
    # busca a posicao dos dados passados como parametro
    memoindex = listatexto.index('Memorando')
    dataindex = listatexto.index('Data:')
    deindex = listatexto.index('De:')
    paraindex = listatexto.index('Para:')
    if 'ref:' in listatexto:
        fimindex = listatexto.index('ref:')
    elif 'Ref:' in listatexto:
        fimindex = listatexto.index('Ref:')
    elif 'Assunto:' in listatexto:
        fimindex = listatexto.index('Assunto:')
    else:
        print("ERRO!!!")
        print(cabecalho[0])
        exit(1)

    # preenche os itens do vetor cabecalho com os dados limpos
    cabecalho.append(listatexto[memoindex+1:dataindex])
    cabecalho.append(listatexto[dataindex+1:deindex])
    cabecalho.append(listatexto[deindex+1:paraindex])
    cabecalho.append(listatexto[paraindex+1:fimindex])

    # print para conferencia
    print(cabecalho)

def parseodt(matriz):

    # extrai os dados de um odt e transforma em texto

    # lista todos os arquivos odt da pasta
    listaodts = (glob.glob("*.odt"))
    for f in listaodts:

        # extrai os arquivos internos do odt
        myfile = zipfile.ZipFile(f)
        listoffiles = myfile.infolist()

        for s in listoffiles:
            if s.orig_filename == "content.xml":
                # cria o vetor cabecalho dos dados
                cabecalho = []
                # nome do arquivo
                cabecalho.append(f)
                # extrai os dados do odt
                textoXML = str(myfile.read(s.orig_filename), 'utf-8')
                # remova a marcacao XML
                texto = removeXMLMarkup(textoXML, replace_with_space=1)
                # preeche o cabecalho
                cabecalho = cabecalhoodt(texto,cabecalho)
                # extrai os codigos dos patrimonios
                buscapatrim(texto,matriz,cabecalho)

def parsepdf(matriz):

    # extrai os dados de um pdf pesquisavel e transforma em texto

    # lista todos os arquivos pdf da pasta
    listapdfs = (glob.glob("*.pdf"))


    for pdf in listapdfs:

        # extrai os dados do pdf
        texto = str.splitlines(str(textract.process(pdf), 'utf-8'))
        
       
        if texto == '':
            # se n extraiu nada
            print("PDF vazio")
        
        else:
            # cria o vetor cabecalho dos dados
            cabecalho = []
            # nome do arquivo
            cabecalho.append(pdf)
            # itens do cabecalho memorando
            for i in range(1,14,2):
                cabecalho.append(texto[i])
            
            # extrai os codigos dos patrimonios
            buscapatrim(texto,matriz,cabecalho) 


def main():

 # cria a matriz que recebe os dados
 matriz = []

 # extrai os dados dos arquivos, preenchendo a matriz
 #parseodt(matriz)
 parsepdf(matriz)

 # inicializa o LibreOffice
 #proc = subprocess.call('soffice --accept="socket,host=localhost,port=2002;urp;" --norestore --nologo --nodefault # --headless', shell=True)

 # cria uma planilha no Calc
 desktop = pyoo.Desktop()
 doc = desktop.create_spreadsheet()
 sheet = doc.sheets[0]

 # preenche a planilha com os dados da matriz
 for i in range(len(matriz)):
    for j in range(len(matriz[i])):
        sheet[i,j].value = matriz[i][j]

 # salva a planilha
 doc.save('Novo.ods')
 #fecha a planilha
 doc.close()

 #encerra o office
 #proc.terminate()
