SALAS = ("LAB1", "LAB2", "LAB3")
ESTADOS = ("Operacional", "Avariado", "Em reparação")
tipos = ["computador","monitor","impressora","router","switch","projector"]
inventario = {
    'PC01': {
    'nome': 'Desktop hp elitedesk',
    'tipo': 'computador',
    'sala': 'LAB1',
    'quantidade': 11,
    'estado': 'operacional',
},
    'PC02': {
        'nome': 'Desktop hp elitedesk2',
        'tipo': 'computador',
        'sala': 'LAB1',
        'quantidade': 12,
        'estado': 'operacional'
    },
    'PC03': {
        'nome': 'Desktop hp elitedesk3',
        'tipo': 'computador',
        'sala': 'LAB1',
        'quantidade': 13,
        'estado': 'operacional'
        },
    'SWITCH': {
        'nome': 'Switch01',
        'tipo': 'switch',
        'sala': 'LAB2',
        'quantidade': 2,
        'estado': 'Avariado'
    },
    'ROUTER': {
        'nome': 'Router01',
        'tipo': 'router',
        'sala': 'LAB2',
        'quantidade': 3,
        'estado': 'Avariado'
    },
    'IMPRESSORA': {
        'nome': 'Impressora01',
        'tipo': 'impressora',
        'sala': 'LAB3',
        'quantidade': 1,
        'estado': 'Avariado'
        },
}

lista_reparacao = []
lista_reparados = []
lista_historico = []
ativo = True

while ativo:
    lista_reparacao = [nome for nome in inventario if inventario[nome]['estado'] == 'Avariado']
    menu = "Gestor de Inventário\n"
    menu += "1 - Listar equipamentos\n"
    menu += "2 - Adicionar equipamento\n"
    menu += "3 - Pesquisar equipamento\n"
    menu += "4 - Alterar estado de um equipamento\n"
    menu += "5 - Remover equipamento\n"
    menu += "6 - Lista de reparação\n"
    menu += "7 - Estatísticas\n"
    menu += "8 - Histórico de operações\n"
    menu += "0 - Sair\n"
    menu += "Escolha uma opção: "

    resposta = int(input(menu))

    if resposta == 0:
        resposta0 = input("Queres mesmo sair? S/N: ").title()
        if resposta0 == "S":
            print("Até Amanhã.") 
            ativo = False
        elif resposta0 == "N":
            print("Ok...")
            ativo = True

    if resposta == 1:

        if inventario == None:
            print("O Inventário está vazio")
            resposta1 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()
            if resposta1 == "S":
                ativo = True
            elif resposta1 == "N":
                ativo = False
    
        for equipamento, dados in inventario.items():
            print(equipamento)
            print(dados)
        
        print(f"Existem cerca de {len(inventario)} registros")
        lista_historico.append("Listagem dos registros dos equipamentos")
        resposta1 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()

        if resposta1 == "S":
            ativo = True
        elif resposta1 == "N":
            ativo = False

    if resposta == 2:
        resposta2 = input("Que equipamentos desejas adicionar, primeiro o código: ")
        resposta2.strip().upper()

        if resposta2 in inventario:
            print("Esse código de equipamento já existe")
        else:
            nome = input("Mete o nome desse equipamento: ").title()
            while not nome:
                nome = input("Faz o favor de repetir: ").title()

            tipo = input("Mete o tipo desse equipamento: ").lower()
            sala = input("Mete a sala desse equipamento: ").upper()
            quantidade = int(input("Mete a quantidade desse equipamento: "))

            inventario[resposta2] = {
                "nome": nome,
                "tipo": tipo,
                "sala": sala,
                "quantidade": quantidade,
                "estado": "operacional"
            }
            lista_historico.append(f"Adição de equipamento: {resposta2}")
            print("Equipamento adicionado com sucesso!")

    if resposta == 3:
        resposta3 = input("Mete ai o codigo que queres pesquisar: ")
        equipamento = inventario.get(resposta3)

        if equipamento:
            print(f"Equipamento encontrado: {resposta3}")
            print(f"Nome: {equipamento['nome']}")
            print(f"Tipo: {equipamento['tipo']}")
            print(f"Sala: {equipamento['sala']}")
            print(f"Quantidade: {equipamento['quantidade']}")
            print(f"Estado: {equipamento['estado']}")
            lista_historico.append(f"Pesquisa de equipamento: {resposta3}")
        else:
            print("Código não existente.")
            lista_historico.append(f"Tentativa de pesquisa de equipamento inválida.")

        resposta3 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()
        if resposta3 == "S":
            ativo = True
        elif resposta3 == "N":
            ativo = False

    if resposta == 4:
        resposta4 = input("Mete ai o codigo que queres alterar o estado: ")
        equipamento = inventario.get(resposta4)

        if equipamento:
            print(f"Equipamento encontrado: {resposta4}")
            print(f"Nome: {equipamento['nome']}")
            print(f"Tipo: {equipamento['tipo']}")
            print(f"Sala: {equipamento['sala']}")
            print(f"Quantidade: {equipamento['quantidade']}")
            print(f"Estado: {equipamento['estado']}")
            estado_novo = input("Mete o estado do equipamento: ").title()

            if estado_novo in ESTADOS:
                equipamento['estado'] = estado_novo
                print("Estado novo aplicado.")
                lista_historico.append(f"Alteração de estado do equipamento {resposta4} para {estado_novo}")
                if estado_novo == "Avariado":
                    lista_reparacao.append(resposta4)
                    print(f"O equipamento {resposta4} foi adicionado à lista de reparação.")
            else:
                print("Estado não foi alterado.")
        
        resposta4 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()
        if resposta4 == "S":
            ativo = True
        elif resposta4 == "N":
            ativo = False

    if resposta == 5:
        resposta5 = input("Mete ai o codigo que queres remover: ")
        print(f"Tens mesmo certeza que queres remover o equipamento {resposta5}?")
        confirmacao = input("Se sim faz S se não faz N: ").upper()

        if confirmacao == "S":
            while resposta5 in lista_reparacao:
                lista_reparacao.remove(resposta5)
            print(f"O equipamento {resposta5} foi removido do inventário.")
            lista_historico.append(f"Remoção do equipamento {resposta5} do inventário")
            inventario.pop(resposta5, None)

        elif confirmacao == "N":
            print("O equipamento não foi removido.")
            lista_historico.append(f"Remoção cancelada do {resposta5} do inventário")
        resposta5 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()

        if resposta5 == "S":
            ativo = True
        elif resposta5 == "N":
            ativo = False

    if resposta == 6:
        print(lista_reparacao)

        for codigo, dados in inventario.items():
            if dados['estado'] == 'Avariado':
                print(f"O equipamento {dados['nome']} tá avariado")
                resposta6 = input(f"Queres consertar este equipamento: {dados['nome'] }? Se sim faz S se não faz N: ").upper()
                if resposta6 == "S":
                    dados['estado'] = 'Operacional'
                    lista_historico.append(f"Reparação do equipamento {codigo} concluida")
                    print(f"Equipamento {codigo} reparado.")
                elif resposta6 == "N":
                    print("Ok, o equipamento não foi reparado.")
                    lista_historico.append(f"Equipamento {codigo} não foi reparado")

        if not lista_reparacao and not any(dados['estado'] == 'Avariado' for dados in inventario.values()):
            print("Nao tens nada avariado")
        
        resposta6 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()

        if resposta6 == "S":
            ativo = True
        elif resposta6 == "N":
            ativo = False

    if resposta == 7:
        if inventario == None:
            print("Tá vazio o inventário")

        lista_numero_total = len(registros := inventario)
        quantidade = [dados['quantidade'] for dados in registros.values()]
        menor = min(quantidade)
        maior = max(quantidade)
        print(f"Existem {lista_numero_total} equipamentos no inventário")
        print(f"O equipamento com menos unidades é: {menor}, {[nome for nome, dados in registros.items() if dados['quantidade'] == menor][0]}")
        print(f"O equipamento com mais unidades é: {maior}, {[nome for nome, dados in registros.items() if dados['quantidade'] == maior][0]}")
        resposta7 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()

        if resposta7 == "S":
            ativo = True
        elif resposta7 == "N":
            ativo = False

    if resposta == 8:
        if not lista_historico:
           print("Não existem operações no histórico.")
           lista_historico.append("Tentativa de visualização do histórico sem operações registradas.")
        else:
            print("Histórico de operações: ")
            for operacao in lista_historico:
                print(operacao)
    
        resposta8 = input("Queres voltar ao menu ou sair do programa? Se sim faz S se não faz N: ").upper()
        lista_historico.append("Visualização do histórico de operações")

        if resposta8 == "S":
            ativo = True
        elif resposta8 == "N":
            ativo = False