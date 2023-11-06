import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import csv
import matplotlib.patches as patches
import os

from matplotlib import rcParams
rcParams['font.family'] = 'sans-serif'
rcParams['font.sans-serif'] = ['Hiragino Maru Gothic Pro', 'Yu Gothic', 'Meirio',
                               'Takao', 'IPAexGothic', 'IPAPGothic', 'VL PGothic', 'Noto Sans CJK JP']


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
    shortrect = patches.Rectangle((1, 5), width=2, height=0, linewidth=22, edgecolor="#FFFFFF", facecolor="#FFFFFF")
    ax.add_patch(shortrect)

    ax.invert_yaxis()
    for i in range(10):
        ys, xs = np.where(Matrix == i)
        w = xs.max() - xs.min() + 1
        h = ys.max() - ys.min() + 1
        col = color(i)
        rect = patches.Rectangle((xs.min(), ys.min()), w, h, linewidth=4, ec="#575757", fc=col)

        ax.add_patch(rect)

        center_x = xs.min() + w / 2
        center_y = ys.min() + h / 2

        text = name(i)
        ax.annotate(text, xy=(center_x, center_y), ha='center', va='center', fontsize=12)

    ax.set_aspect('equal')
    ax.set_axis_off()
    plt.axis('scaled')


def name(i):
    if (i == 1):
        return "父親"
    elif (i == 2):
        return "母親"
    elif (i == 3):
        return "祖父"
    elif (i == 4):
        return "祖母"
    elif (i == 5):
        return "兄弟"
    elif (i == 6):
        return "華道"
    elif (i == 7):
        return "茶道"
    elif (i == 8):
        return "書道"
    elif (i == 9):
        return "武道"
    elif (i == 0):
        return "娘"


def color(i):
    if (i == 1):
        return "#f5244d"
    elif (i == 2):
        return "#85ccff"
    elif (i == 3):
        return "#ffc033"
    elif (i == 4):
        return "#ff8733"
    elif (i == 5):
        return "#22db1f"
    elif (i == 6):
        return "#badb1f"
    elif (i == 7):
        return "#f094d1"
    elif (i == 8):
        return "#7460e6"
    elif (i == 9):
        return "#e619c4"
    elif (i == 0):
        return "#f34844"
    elif (i == 10):
        return "#f0f0f0"


folder_name = 'clearroute_images'
if not os.path.exists(folder_name):
    os.mkdir(folder_name)
figure, oneframe = plt.subplots()
lis.reverse()
for frame in range(len(lis)):
    plt.cla()  # グラフをクリア
    write_board(lis[frame])
    oneframe.set_title(f'Frame {frame}')
    oneframe.set_axis_off()
    n = str(frame).zfill(3)
    image_file_path = os.path.join(folder_name, n + "edge.png")
    plt.savefig(image_file_path)
print(f'Images saved to the folder: {folder_name}')