#!/Users/vifonne/.brew/bin/python3
class Vecteur:
    def __init__(self,x,y):
        self.x=x
        self.y=y

    def affichage(self):
        return '('+str(self.x)+';'+str(self.y)+')'

    def norme(self):
        return hypot(self.x,self.y)

    def __add__(self,v):
        return Vecteur(self.x+v.x,self.y+v.y)

    def __rmul__(self,r):
        return Vecteur(self.x*r,self.y*r)

    def __mul__(self,v):
        return self.x*v.x+self.y*v.y

    def colin(self,v):
        return self.x*v.y==self.y*v.x

    def ortho(self,v):
        return self*v==0
class Point:
    def __init__(self,x,y):
        self.x=x
        self.y=y

    def affichage(self):
        return '('+str(self.x)+';'+str(self.y)+')'

    def milieu(self,p):
        return Point((self.x+p.x)/2,(self.y+p.y)/2)

    def vecteur(self,p):
        return Vecteur(p.x-self.x,p.y-self.y)

    def distance(self,p):
        return self.vecteur(p).norme()
class Droite:
    def __init__(self,a,b):
        self.a=a
        self.b=b

    def directeur(self):
        return self.a.vecteur(self.b)

    def normal(self):
        return Vecteur(-self.directeur().y,self.directeur().x)

    def cartesienne(self):
        return '('+str(self.normal().x)+')x+('+str(self.normal().y)+')y='+str(self.normal().x*self.a.x+self.normal().y*self.a.y)

    def cd(self):
        return self.directeur().y/self.directeur().x

    def oalo(self):
        return self.a.y-self.cd()*self.a.x

    def reduite(self, x):
        return (self.cd() * x) + self.oalo()

    def parallele(self,d):
        return self.directeur().colin(d.directeur())

    def perpendiculaire(self,d):
        return self.normal().ortho(d.normal())