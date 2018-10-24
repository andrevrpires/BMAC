#!/usr/bin/python3

import glob, zipfile, re, pyoo, textract #, subprocess

def removeXMLMarkup(s, replace_with_space):
    s = re.compile("<!--.*?-->", re.DOTALL).sub('', s)
    repl = ''
    if replace_with_space:
        repl = ' '
    s = re.compile("<[^>]*>", re.DOTALL).sub(repl, s)
    return s

def buscapatrim(texto,matriz,cabecalho):

    for l in texto:
        for w in l.split():
            if re.search("[2-6]\\d{5}", w):
                numero = re.sub("\D","",w)              
                if 200000 < int(numero) < 699999:
                    linha = list(cabecalho)
                    linha.append(numero)
                    matriz.append(linha)

def cabecalhoodt(texto,cabecalho):

    listatexto = str.splitlines(texto)[1].split()
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

    cabecalho.append(listatexto[memoindex+1:dataindex])
    cabecalho.append(listatexto[dataindex+1:deindex])
    cabecalho.append(listatexto[deindex+1:paraindex])
    cabecalho.append(listatexto[paraindex+1:fimindex])

    print(cabecalho)
    return cabecalho

def parseodt(matriz):

    listaodts = (glob.glob("*.odt"))
    for f in listaodts:
        myfile = zipfile.ZipFile(f)
        listoffiles = myfile.infolist()

        for s in listoffiles:
            if s.orig_filename == "content.xml":
                cabecalho = []
                cabecalho.append(f)
                textoXML = str(myfile.read(s.orig_filename), 'utf-8')
                texto = removeXMLMarkup(textoXML, replace_with_space=1)
                cabecalho = cabecalhoodt(texto,cabecalho)
                buscapatrim(texto,matriz,cabecalho)

def parsepdf(matriz):

    listapdfs = (glob.glob("*.pdf"))
    for pdf in listapdfs:
        texto = str.splitlines(str(textract.process(pdf), 'utf-8'))
        if texto == '':
            print("PDF vazio")
        else:
            cabecalho = []
            cabecalho.append(pdf)
            for i in range(1,14,2):
                cabecalho.append(texto[i])
            buscapatrim(texto,matriz,cabecalho) 




matriz = []
#parseodt(matriz)
parsepdf(matriz)

#proc = subprocess.call('soffice --accept="socket,host=localhost,port=2002;urp;" --norestore --nologo --nodefault # --headless', shell=True)

desktop = pyoo.Desktop()
doc = desktop.create_spreadsheet()
sheet = doc.sheets[0]

for i in range(len(matriz)):
    for j in range(len(matriz[i])):
        sheet[i,j].value = matriz[i][j]

doc.save('Novo.ods')
doc.close()

#proc.terminate()
