import time

FACTOR=15

Func_count=0

def My_func3(r):
    #return 1/(1+25*(pow(r[0],2)+pow(r[1],2)+pow(r[2],2)))
    global Func_count
    Func_count+=1
    return pow(r[0],2)+pow(r[1],2)+pow(r[2],2)

def Rectanglar_3D(a,b,f):
    m=[0,0,0]
    V=1
    for i in range(3):
        m[i]=(a[i]+b[i])/2
        V*=abs(a[i]-b[i])
    return f(m)*V

# get_Division: returns a list, containing the point in the mesh.
# Example: get_Division([0,0,0],[1,2,3],[1,0,2]) returns [0.5,0,3]
def get_Division(a,b,n):
    result=[0,0,0]
    for i in range(3):
        result[i]=a[i]+(b[i]-a[i])*n[i]/2
    #print(result, a, b, n)
    return result

def Adaptive_Rectanglar_3D(a,b,epsilon,f,level):
    result=Rectanglar_3D(a,b,f)
    sub_result=0
    if level>20:
        #print('return point 1, level=',level)
        return result
    for x in (0,1):
        for y in (0,1):
            for z in (0,1):
                sub_result+=Rectanglar_3D(get_Division(a,b,[x,y,z]),get_Division(a,b,[x+1,y+1,z+1]),f)
    if abs(result-sub_result)<FACTOR*epsilon:
        #print('return point 2, result={0}, sub_result={1}'.format(result,sub_result))
        return sub_result+(sub_result-result)/FACTOR
    else:
        result=0
        for x in (0,1):
            for y in (0,1):
                for z in (0,1):
                    result+=Adaptive_Rectanglar_3D(get_Division(a,b,[x,y,z]),get_Division(a,b,[x+1,y+1,z+1]),epsilon/8,f,level+1)
        #print('return point 3, result={0}, sub_result={1}'.format(result,sub_result))
        return result

start=time.time()
#Rectanglar_3D()
print(Adaptive_Rectanglar_3D([-1,-1,-1],[1,1,1],0.0001,My_func3,0))

Total_time=time.time()-start
print(Total_time)
print(Func_count)
