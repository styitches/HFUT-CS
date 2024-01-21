import math
import re
#(P8 22 0) (P7 27.7 30)
pos_re=re.compile(r'\((.*?)\s(.*?)\s(.*?)\)\s\((.*?)\s(.*?)\s(.*?)\)')
pos_re1=re.compile(r'\((.*?)\,(.*?)\)')
position={
    'C':'(0,0)',
    'P1':'(-52.5,-32)',
    'P2':'(-52.5, 32)',
    'P3':'(52.5,32)',
    'P4':'(52.5,-32)',
    'P5':'(0,-32)',
    'P6':'(0,32)',
    'P7':'(-30,-7)',
    'P8':'(-30, 7)',
    'P9':'(30,7)',
    'P10':'(30, -7)',
    'G1':'(-52.5,0)',
    'G2':'(52.5,0)'
}
# line='(P8 22 0) (P7 27.7 30)'
line=input('请输入相关点位信息\n')
n=pos_re.match(line)
n1=pos_re1.match(position[n.group(1)])
n2=pos_re1.match(position[n.group(4)])#正则匹配
angle=float(n.group(6))-float(n.group(3))#角度计算
d2=pow(float(n1.group(1))-float(n2.group(1)),2)+pow(float(n1.group(2))-float(n2.group(2)),2)#两点距离的平方
a=(pow(float(n.group(2)),2)-pow(float(n.group(5)),2)+d2)/(math.sqrt(d2)*2)#a的值
cosa=(float(n2.group(1))-float(n1.group(1)))/math.sqrt(d2)#cosa的值
sina=(float(n2.group(2))-float(n1.group(2)))/math.sqrt(d2)#sina的值
pxpie=float(n1.group(1))+a*cosa#求解px‘
pypie=float(n1.group(2))+a*sina#求解py’

h=math.sqrt(pow(float(n.group(2)),2)-pow(a,2))
if angle>=0:
    sign=1
else:
    sign=-1
px=pxpie-h*sign*sina
py=pypie+h*sign*cosa
px=round(px,2)
py=round(py,2)
#px=-8.2，py=10.14；
print('px='+str(px)+',py='+str(py)+';')
