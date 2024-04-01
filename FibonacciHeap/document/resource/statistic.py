import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sn

if __name__ == '__main__':
    containers = ['Linked List', 'Binary Heap', 'Fibonacci Heap']
    data = pd.read_csv('./../../code/test/output.csv', sep='\t', names=containers)
    data['n'] = data.index + 1
    data['average'] = 0
    for i in range(3):
       data['average'] += data[containers[i]]
    data['average'] /= 3
    for i in range(3):
       data[containers[i]] /= data['average']
       data[containers[i]] *= 100
    for i in range(3):
      sn.lineplot(data=data, x='n', y=containers[i], label=containers[i])
    plt.axhline(y=100, c='black', linestyle='--')
    plt.xlabel('number of vertex')
    plt.ylabel('cost of time (%)')
    plt.legend()
    plt.savefig('./time.png')