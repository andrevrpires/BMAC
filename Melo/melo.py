import glob, zipfile, re, pyoo, textract

def removeXMLMarkup(s, replace_with_space):
    s = re.compile("<!--.*?-->", re.DOTALL).sub('', s)
    repl = ''
    if replace_with_space:
        repl = ' '
    s = re.compile("<[^>]*>", re.DOTALL).sub(repl, s)
    return s

desktop = pyoo.Desktop()
planilha = desktop.create_spreadsheet()
sheet = planilha.sheets[0]
linha = 0

arquivos = (glob.glob("*.odt"))

for f in arquivos:
    myfile = zipfile.ZipFile(f)
    listoffiles = myfile.infolist()

    for s in listoffiles:
        if s.orig_filename == "content.xml":
            content = str(myfile.read(s.orig_filename), 'utf-8')
            content = removeXMLMarkup(content, replace_with_space=1)
            for w in content.split():
                if re.search("[3-6]\\d{5}", w):
                    limpa = re.sub("\D","",w)
                    if len(limpa) == 6:
                         sheet[linha, 0].value = f
                         sheet[linha, 1].value = limpa
                         linha += 1
                    
listapdfs = (glob.glob("*.pdf"))
print(listapdfs)

for pdf in listapdfs:

    print(pdf)
    text = str(textract.process(pdf), 'utf-8')
    if text == '':
        print("PDF vazio")

    for w in text.split():
        if re.search("\d{6}", w):
            limpa = re.sub("\D","",w)
            if len(limpa) == 6:
                
                sheet[linha, 0].value = pdf
                sheet[linha, 1].value = limpa
                linha += 1
                    
planilha.save('Novo.ods')
planilha.close()

