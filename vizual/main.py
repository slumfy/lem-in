#!/usr/bin/python3
import  sys
import	pygame as pg
from	random import *
from	math import *
import	time
from	array import *
import	d_v_p as ft_math
red = (255,0,0)
green = (0,255,0)
blue = (0,0,255)
darkBlue = (0,0,128)
white = (255,255,255)
black = (0,0,0)
pink = (255,200,200)
brown = (61, 31, 33)
colors = [red, green, blue, white, pink]
win_w = 1080
win_h = 720
room_w = 90
room_h = 70
ant_size = 95
speed = 30
ant_num = []
step = 0
move = []
ant = []
raw_inst = []
name = []
x = []
y = []
pipe_l = []
pipe_r = []
room = [name, x, y, pipe_l, pipe_r]
start_img = pg.transform.scale(pg.image.load("start.png"), (room_w, room_h))
end_img = pg.transform.scale(pg.image.load("end.png"), (room_w, room_h))
ant_p1 = pg.transform.scale(pg.image.load("pos1_ant_bl.png"), (ant_size, ant_size))
ant_p2 = pg.transform.scale(pg.image.load("pos2_ant_bl.png"), (ant_size, ant_size))
def	read_stdin():
	l_stdin = []
	for line in sys.stdin:
		l_stdin.append(line)
	return l_stdin;
def	parse_stdin(l_stdin):
	len_stdin = []
	ant.append(int(l_stdin[0]))
	l_stdin.pop(0)
	for tmp in l_stdin:
		len_stdin.append(len(tmp))
	for line in l_stdin:
		if line[0] == '#' and line[1] != '#':
			continue
		if len(line.split()) == 3:
			name.append(line.split()[0])
			x.append(randint(room_w + (max(len_stdin)*10), win_w - room_w))
			y.append(randint(room_h, win_h - room_h))
		elif len(line.split("-")) == 2 and line.split("-")[0][0] != 'L':
			ret = line.split("-")
			pipe_l.append(name.index(ret[0].rstrip()))
			pipe_r.append(name.index(ret[1].rstrip()))
		elif line.split("-")[0][0] == 'L':
			ret = line.split()
			ant_m = []
			x_m = []
			y_m = []
			room_m = [x_m, y_m]
			move.append([ant_m, room_m])
			raw_inst.append(line.rstrip())
			for tmp in ret:
				tmp = tmp.split("-")
				index = int(tmp[0].split('L')[1].rstrip())
				ant_m = []
				x_m = []
				y_m = []
				room_m = [x_m, y_m]
				if index >= len(move):
					move.append([ant_m, room_m])
				move[index][0].append(index)
				# tmp[0].rstrip()
				move[index][1][0].append(x[name.index(tmp[1].rstrip())]+room_w/2)	
				move[index][1][1].append(y[name.index(tmp[1].rstrip())]+room_h/2)
	move.pop(0)
	return room;

# def gen_coord(room):
# 	i = 0
# 	while i < len(room[1]):
# 		room[1][i] = randint(0, win_w - room_w)
# 		# int((room[1][i]*(win_w-room_w))/max(room[1]))
# 		room[2][i] = randint(0, win_h - room_h)
# 		# int((room[2][i]*(win_h-room_h))/max(room[2]))
# 		i += 1
# 	return room;

def put_start(room):
	i = 0
	while i < len(room[0][i]):
		if room[0][i] == "start":
			ant_p = [room[1][i], room[2][i]]
		i += 1
	return (ant_p)

def	count_ant(j):
	my_str = ""
	while j > 0:
		my_str += "|"
		j -= 1
	return my_str

def	print_map(room, ant_start):
	done = False
	flag = True
	ant_stat_str = "No. of ant(s) on "
	j = 0
	ant_p = put_start(room)
	tmp = win_gen(done, room, ant_p)
	ant_end = 0
	screen = tmp[0]
	solid_bg = tmp[1]
	launch = True
	# screen.blit(txtfmt.render(ant_stat_str + "[START]" + count_ant(j), False, white), (10, 10))
	pg.display.flip()
	while not done:
		if launch == True:
			launch_screen(screen)
			launch = False
		while j < ant[0] and not done:
			i = 0
			anim = True
			a = ft_math.Point(ant_p[0]+room_w/2, ant_p[1]+room_h/2)
			b = ft_math.Point(move[j][1][0][0], move[j][1][1][0])
			ant_start -= 1;
			while i < (len(move[j][1][0])) and anim and not done:
				d1 = ft_math.Droite(a, b)
				done = print_ant(flag, ant_p, move[j], [screen, solid_bg], d1, i, done, [ant_start, ant_end])
				if i+1 == len(move[j][1][0]):
					anim=False
					ant_end += 1
					break
				a = ft_math.Point(move[j][1][0][i], move[j][1][1][i])
				b = ft_math.Point(move[j][1][0][i+1], move[j][1][1][i+1])
				i += 1
				for event in pg.event.get():
					if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
						done = True
				pg.display.flip()
			ant_p = put_start(room)
			j += 1
			ant_num[0] += 1
		for event in pg.event.get():
			if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
				done = True
	pg.quit()

def win_gen(done, room, ant_p):
	pg.init()
	pg.font.init()
	screen = pg.display.set_mode([win_w, win_h])
	bg = pg.image.load("dirt800x535.jpg")
	bg = pg.transform.scale(bg, (win_w, win_h))
	room_name = pg.font.SysFont('Arial', 25)
	screen.blit(bg, [0, 0])
	i = 0
	while i < len(room[3]):
		pg.draw.line(
			screen,
			white,
			(room[1][room[4][i]]+room_w/2, room[2][room[4][i]]+room_h/2),
			(room[1][room[3][i]]+room_w/2, room[2][room[3][i]]+room_h/2),
			2
		)
		i += 1
	i = 0
	while (i < len(room[1])):
		pg.draw.rect(
			screen,
			brown,
			pg.Rect(room[1][i], room[2][i], room_w, room_h))
		pg.draw.rect(
			screen,
			white,
			pg.Rect(room[1][i], room[2][i], room_w, room_h),
			2)
		if room[0][i] == "start":
			screen.blit(start_img, (room[1][i], room[2][i]))
		elif room[0][i] == "end":
			screen.blit(end_img, (room[1][i], room[2][i]))
		s_room_name = room_name.render(room[0][i], False, white)
		screen.blit(s_room_name, (room[1][i], room[2][i]- 20))
		i += 1
	solid_bg = pg.Surface.copy(screen)
	surface = [screen, solid_bg]
	return surface;

def	print_txt(screen, solid_bg, ant_cpt):
	y = 160 + 50
	txtfmt = pg.font.SysFont('Arial', 45)
	screen.blit(solid_bg, [0, 0])
	screen.blit(txtfmt.render("Lem-in | By rvalenti & vifonne @ 42", False, white), (10, 10))
	screen.blit(txtfmt.render("Number of ant(s) on [START] : " + str(ant_cpt[0]), False, white), (10, 60))
	screen.blit(txtfmt.render("Number of ant(s) on [END] : " + str(ant_cpt[1]), False, white), (10, 110))
	screen.blit(txtfmt.render("Number of rooms: : " + str(len(room[0])), False, white), (10, 160))

	for line in raw_inst:
		screen.blit(txtfmt.render(line, False, white), (10, y))
		y += 50
	screen.blit(txtfmt.render("Ant No : " + str(ant_num[0]), False, white), (10, y))
def print_ant(flag, ant_p, move, screen, d1, i, done, ant):
	if ant_p[0] > move[1][0][i]:
		while ant_p[0] > move[1][0][i] and ant_p[1] != move[1][1][i] and not done:	
			flag = not flag
			for event in pg.event.get():
				if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
					done = True
			print_txt(screen[0], screen[1], ant)
			if flag:
				rot_p1 = pg.transform.rotate(ant_p1, 90)
				screen[0].blit(rot_p1, [ant_p[0]-ant_size/2, ant_p[1]-ant_size/2])
			else:
				rot_p2 = pg.transform.rotate(ant_p2, 90)
				screen[0].blit(rot_p2, [ant_p[0]-ant_size/2, ant_p[1]-ant_size/2])
			ant_p[0] -= speed
			ant_p[1] = d1.reduite(ant_p[0])
			time.sleep(0.10)
			pg.display.flip()
	elif move[0][i]:
		while ant_p[0] < move[1][0][i] and ant_p[1] != move[1][1][i] and not done:
			flag = not flag
			for event in pg.event.get():
				if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
					done = True
			print_txt(screen[0], screen[1], ant)
			if flag:
				rot_p1 = pg.transform.rotate(ant_p1, 90)
				screen[0].blit(rot_p1, [ant_p[0]-ant_size/2, ant_p[1]-ant_size/2])
			else:
				rot_p2 = pg.transform.rotate(ant_p2, 90)
				screen[0].blit(rot_p2, [ant_p[0]-ant_size/2, ant_p[1]-ant_size/2])
			ant_p[0] += speed
			ant_p[1] = d1.reduite(ant_p[0])
			time.sleep(0.10)
			pg.display.flip()
	return done;

def launch_screen(screen):
	pressed = False
	lnchr = pg.transform.scale(pg.image.load("launch-screen.png"), (win_w, win_h))
	screen.blit(lnchr, (0, 0))
	pg.display.flip()
	while pressed == False:
		for event in pg.event.get():
			if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_SPACE):
				pressed = True


def	main():
	ant_num.append(1)
	l_stdin = read_stdin()
	room = parse_stdin(l_stdin)
	ant_start = ant[0]
	if (room):
		print_map(room, ant_start)
	sys.exit()

main()
