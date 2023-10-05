import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import csv
import matplotlib.patches as patches

lis = []

with open('/home/poyoyonland/projects/Hakoiricpp/build/example.csv') as puzzle:
    reader = csv.reader(puzzle)
    for row in reader:
        row_arr = np.array(row)
        reshaped_arr = row_arr.reshape(5, 4)
        reshaped_arr = reshaped_arr.astype(int)
        lis.append(reshaped_arr)

def write_board(Matrix):
    fig, ax = plt.subplots()
    bigrect = patches.Rectangle((0, 0), width=4, height=5, linewidth=20, edgecolor="#575757", facecolor="#FFFFFF")
    ax.add_patch(bigrect)
    bigrect2 = patches.Rectangle((0, 0), width=4, height=5, linewidth=2, edgecolor="#575757", facecolor="#FFFFFF")
    ax.add_patch(bigrect2)
    shortrect = patches.Rectangle((1, 0), width=2, height=0, linewidth=22, edgecolor="#FFFFFF", facecolor="#FFFFFF")
    ax.add_patch(shortrect)

    for i in range(10):
        ys, xs = np.where(Matrix == i)
        w = xs.max() - xs.min() + 1
        h = ys.max() - ys.min() + 1
        col = color(i)
        rect = patches.Rectangle((xs.min(), ys.min()), w, h, linewidth=4, ec="#575757", fc=col)
        ax.add_patch(rect)


    ax.set_aspect('equal')
    ax.set_axis_off()
    plt.axis('scaled')


def color(i):
    if(i == 1):
        return "#f5244d"
    elif(i == 2):
        return "#85ccff"
    elif(i == 3):
        return "#ffc033"
    elif(i == 4):
        return "#ff8733"
    elif(i == 5):
        return "#22db1f"
    elif(i == 6):
        return "#badb1f"
    elif(i == 7):
        return "#f094d1"
    elif(i == 8):
        return "#7460e6"
    elif(i == 9):
        return "#e619c4"
    elif(i == 0):
        return "#f34844"
    elif(i == 10):
        return "#f0f0f0"

figure, oneframe = plt.subplots()
lis.reverse()
for frame in range(len(lis)):
    plt.cla()  # グラフをクリア
    write_board(lis[frame])
    oneframe.set_title(f'Frame {frame}')
    oneframe.set_axis_off()
    n = str(frame).zfill(3)
    plt.savefig(  n + "edge.png")

