import turtle

def hs(pen, x, y, r, cir=360):
    pen.up()
    pen.goto(x, y)
    pen.down()
    pen.begin_fill()
    pen.circle(r, cir)
    pen.end_fill()


def cir(pen, x, y, r, cir=360):
    pen.up()
    pen.goto(x, y)
    pen.down()
    pen.circle(r, cir)


pen = turtle
pen.setup(1200, 700, 200, 20)
pen.pencolor("#E49E2D")
pen.pensize(15)
pen.speed(100)

# ----------------------------画边框
pen.right(60)             # 下半部分
pen.fillcolor("#FFD83F")
hs(pen, -216, -125, 250, cir=120)

pen.fillcolor("#FFD950")   # 中间部分1
pen.begin_fill()
pen.circle(250, 30)
pen.left(180)
cir(pen, -250, 0, 250, 30)
pen.end_fill()

pen.fillcolor("#FFD950")   # 中间部分2
pen.left(150)
pen.up()
pen.goto(250, 0)
pen.down()
pen.begin_fill()
pen.circle(250, 30)
pen.left(120)
cir(pen, -216, 125, 250, 30)
pen.end_fill()

pen.fillcolor("#FAD664")    # 上半部分
pen.right(150)
hs(pen, 216, 125, 250, 120)

# -------------------------------------画嘴巴
pen.left(120)
pen.pensize(15)
pen.pencolor("#D0530C")
cir(pen, 0, -207, 207, 80)
pen.right(80)
cir(pen, 0, -207, 207, -80)

# ------------------------------小红腮
pen.pensize(1)
pen.pencolor("#FFDC5C")
pen.fillcolor("#FECE60")
hs(pen, -230, 45, 70)
hs(pen, 85, 45, 70)

pen.pencolor("#FECE60")
pen.fillcolor("#FDC663")
hs(pen, -215, 45, 55)
hs(pen, 102, 45, 55)

pen.pencolor("#FDC663")
pen.fillcolor("#FBBC67")
hs(pen, -202, 45, 42)
hs(pen, 115, 45, 42)

# --------------------------左眼眶部分
pen.fillcolor("#FDFBFA")
pen.pencolor("#D2975C")
pen.pensize(10)
pen.left(50)
pen.up()                # 左眼眶右
pen.goto(-70, 60)
pen.down()
pen.begin_fill()
pen.circle(33, 170)
pen.fd(5)

pen.left(4)             # 左眼眶上
pen.fd(5)
pen.circle(135, 70)
pen.fd(10)

pen.circle(35, 155)      # 左眼眶左
pen.circle(100, 6)
pen.fd(5)

pen.left(12)            # 左眼眶下
pen.circle(-110, 45)
pen.fd(15)
pen.circle(33, 5)
pen.end_fill()

# --------------------------右眼眶部分
pen.right(20)
pen.up()                  # 右眼眶右
pen.goto(160, 60)
pen.down()
pen.begin_fill()
pen.circle(33, 170)
pen.fd(10)

pen.left(4)               # 右眼眶上
pen.circle(135, 70)
pen.fd(10)

pen.circle(35, 155)        # 右眼眶左
pen.circle(100, 6)
pen.fd(5)

pen.left(12)              # 右眼眶下
pen.circle(-110, 45)
pen.fd(15)
pen.circle(33, 5)
pen.end_fill()

# -------------------------------眼珠
pen.pencolor("#6E411E")
pen.fillcolor("#6E411E")
hs(pen, -186, 70, 20)
hs(pen, 45, 75, 20)

pen.done()
