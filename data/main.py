import matplotlib.pyplot as plt
from statistics import mean
import json

def avgBlock(data):
    dif = []

    for block in data['blocks']:
        dif.append(block.get("timeMined"))

    return int(mean(dif))


def openFile(dif):
    f = open('../blockchain/blockchain_' + dif.__str__() + '.json')
    data = json.load(f)

    return data


def main():

    blocks = []
    for i in range(2, 6):
        blocks.append(avgBlock(openFile(i)))

    fig, ax = plt.subplots()
    difs = list(range(2, 6))
    ax.plot(difs, blocks, marker='o')
    ax.set_xticks(difs)
    ax.set_title('Dificuldade x Média de tempo de execução')
    ax.set_ylabel('Média tempo de execução(milisegundos)')
    ax.set_xlabel('Dificuldade')
    plt.savefig('plot.png')
    plt.show()



if __name__ == '__main__':
    main()
