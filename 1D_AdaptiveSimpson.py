import math

def My_func(x):
    return 1/(1+25*pow(x,2))

def My_func2(x):
    return 1/(1+25*(pow(x[0],2)+pow(x[1],2)))

def Simpson_1D(a,b,f):
    return (b-a)*(f(a)+f(b)+4*f((a+b)/2))/6

def Adaptive_Simpson_1D(a,b,epsilon,f,level):
    m=(a+b)/2
    l_result=Simpson_1D(a,m,f)
    r_result=Simpson_1D(m,b,f)
    result=Simpson_1D(a,b,f)
    if level>20:
        return result
    if abs(result-l_result-r_result)<15*epsilon:
        result=l_result+r_result+(l_result+r_result-result)/15
    else:
        result=Adaptive_Simpson_1D(a,m,epsilon/2,f,level+1)+Adaptive_Simpson_1D(m,b,epsilon/2,f,level+1)
    return result

def Simpson_2D(a,b,epsilon,f):
    def f_fix_x(fix_x,fun):
        def f_1D(y):
            return fun((fix_x,y))
        return f_1D
    def f_fix_y(fix_y,fun):
        def f_1D(x):
            return fun((x,fix_y))
        return f_1D
    def Adaptive_Simpson_1D_wrapper(a,b,epsilon,f):
        def Adaptive_Simpson_1D_y(y):
            return Adaptive_Simpson_1D(a,b,epsilon,f_fix_y(y,f),0)
        return Adaptive_Simpson_1D_y
    m=((a[0]+b[0])/2, (a[1]+b[1])/2)
    return Simpson_1D(a[1],b[1],Adaptive_Simpson_1D_wrapper(a[0],b[0],epsilon,f))

def Adaptive_Simpson_2D(a,b,epsilon,f,level):
    m=((a[0]+b[0])/2, (a[1]+b[1])/2)
    l_result=Simpson_2D(a,m,epsilon/2,f)
    r_result=Simpson_2D(m,b,epsilon/2,f)
    result=Simpson_2D(a,b,epsilon,f)
    if level>20:
        return result
    if abs(result-l_result-r_result)<15*epsilon:
        result=l_result+r_result+(l_result+r_result-result)/15
    else:
        result=Adaptive_Simpson_2D(a,m,epsilon/2,f,level+1)+Adaptive_Simpson_2D(m,b,epsilon/2,f,level+1)
    return result

print(Adaptive_Simpson_1D(-1,1,0.0001,My_func,0))
print(Adaptive_Simpson_2D((-1,-1),(1,1),0.0001,My_func2,0))
