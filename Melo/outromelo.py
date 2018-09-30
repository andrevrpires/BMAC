#Este codigo busca por padroes ou "strings definidas" em arquivos de texto e pdfs contidos em uma pasta

import glob, zipfile, re, pyoo

def removeXMLMarkup(s, replace_with_space):

    s = re.compile("<!--.*?-->", re.DOTALL).sub('', s)
    repl = ''
    if replace_with_space:
        repl = ' '
    s = re.compile("<[^>]*>", re.DOTALL).sub(repl, s)
    return s


def ParseOdtFiles(planilha, busca):

	# cria a lista de arquivos
	arquivos = (glob.glob("*.odt"))

	# inicializa com zero o contador de linhas para os matches da busca
	linha = 0
	for f in arquivos:

		# para cada um dos arquivos de texto(arquivo zip) extrai sua lista de XMLs
		myfile = zipfile.ZipFile(f)
		listoffiles = myfile.infolist()

		for s in listoffiles:
		
			# busca o XML que contem os dados do documento
			if s.orig_filename == "content.xml":

				# extrai os dados do documento
				content = str(myfile.read(s.orig_filename), 'utf-8')
				content = removeXMLMarkup(content, replace_with_space=1)
				for w in content.split():

					# itera sobre as palavras do documento
					if re.search("^\\d[2-6]\\d{5}$", w):

						# quando encontra um match, salva o dado encontrado e o arquivo onde se encontra   
						sheet[linha, 0].value = f
						sheet[linha, 1].value = w
						linha += 1
                    
def main():

	# cria a planilha onde serao salvos os matches das buscas
	desktop = pyoo.Desktop()
	planilha = desktop.create_spreadsheet()
	sheet = planilha.sheets[0]

	# busca o dado

	#salva a planilha e fecha
	planilha.save('example.ods')
	planilha.close()

