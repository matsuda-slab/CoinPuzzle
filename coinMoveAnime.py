import tkinter as tk
import time

def moveCoin(focus_coin, start_x, start_y, stop_x, stop_y):
    x = start_x
    y = start_y
    dx = (stop_x - start_x) / 10
    dy = (stop_y - start_y) / 10
    cnt = 0
    while cnt < 10:
        cvs.move(focus_coin, dx, dy)
        time.sleep(0.05)
        cvs.update()
        cnt += 1
    
WIDTH  = 800
HEIGHT = 800
rects  = []
coins  = []

# それぞれのマスに対応する 中心座標のタプルの辞書
masu_coords = {'A':(225, 325), 'B':(275, 325), 'C':(325, 325), 'D':(325, 375),
               'E':(325, 425), 'F':(325, 475), 'G':(325, 525), 'H':(375, 125),
               'I':(375, 175), 'J':(375, 225), 'K':(375, 275), 'L':(375, 325),
               'M':(425, 325), 'N':(475, 325)}

animation = tk.Tk()
animation.attributes("-topmost", True)
cvs = tk.Canvas(animation, width=WIDTH, height=HEIGHT, bg="#d6eaff")

# ルート要素に追加
cvs.pack()

# 矩形の生成 (左上x, 左上y, 右下x, 右下y)
for masu in masu_coords:
    rects.append(cvs.create_rectangle(masu_coords[masu][0]-25, \
                                      masu_coords[masu][1]-25, \
                                      masu_coords[masu][0]+25, \
                                      masu_coords[masu][1]+25))

statefile = open("state_sample.txt", "r")
colors = ["white", "black"]

# コインを初期位置に配置
for color in colors:
    states = statefile.readline().split(' ')[1]
    for idx in range(4):
        coord = masu_coords[states[idx]]
        coins.append(cvs.create_oval(coord[0]-15, coord[1]-15, coord[0]+15, coord[1]+15, fill=color))

filename = "route.txt"
with open(filename, "r") as f:
    while True:
        line = f.readline()
        focus_coin = coins[0]
        if line:
            print("{} -> {}".format(line[0], line[1]))
            before = masu_coords[line[0]]
            after = masu_coords[line[1]]
            for i in range(8):
                coin_coord = cvs.coords(coins[i])
                if int(coin_coord[0])+15 == before[0] and int(coin_coord[1])+15 == before[1]:
                    focus_coin = coins[i]
                    break
            moveCoin(focus_coin, before[0], before[1], after[0], after[1])
        else:
            break

animation.mainloop()
