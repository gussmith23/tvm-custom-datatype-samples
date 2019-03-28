import tvm
from ctypes import *
import topi
import tvm.ir_pass as ir_pass
import numpy as np

tgt = "llvm"

# Load the needed libs.
CDLL("./mybfloat16/libmybfloat16.so", RTLD_GLOBAL)
CDLL("./mybfloat16_wrapper/libmybfloat16_wrapper.so", RTLD_GLOBAL)

# TODO(gus) having numbers in typenames causes some weird parsing bug somewhere
#tvm.register_datatype("bfloat16", 24)
tvm.register_datatype("bfloat", 24, 16)

tvm._api_internal._register_Cast("llvm", "bfloat", "float", "FloatToBFloat16_wrapper")
tvm._api_internal._register_Cast("llvm", "float", "bfloat", "BFloat16ToFloat_wrapper")
tvm._api_internal._register_Add("llvm", "bfloat", "BFloat16Add_wrapper")

X = tvm.placeholder((3,), name="X")
Y = tvm.placeholder((3,), name="Y")
Z = topi.cast(topi.cast(X, dtype="custom[bfloat]") + topi.cast(Y, dtype="custom[bfloat]"), dtype="float")

# Create schedule and lower, manually lowering datatypes. Once datatype lowering
# is integrated directly into TVM's lower/build process, we won't need to do
# this manually.
s = tvm.create_schedule([Z.op])
flist = tvm.lower(s, [X,Y,Z])
flist = [flist]

# print(flist[0].body)
# def callback(stmt):
#     if isinstance(stmt, tvm.expr.Load):
#         print(stmt)
# tvm.ir_pass.PostOrderVisit(flist[0].body, callback)
#def callback(stmt):
    #if isinstance(stmt, tvm.expr.Call):
        #print(stmt.name + " " + stmt.dtype)
flist = [ir_pass.LowerDatatypes(func, tgt) for func in flist]
#print(flist[0].body)
#tvm.ir_pass.PostOrderVisit(flist[0].body, callback)

built_cast = tvm.build(flist[0], target=tgt)
#print(built_cast.get_source())
#exit(0)

ctx = tvm.context(tgt, 0)
x = tvm.nd.array(np.random.uniform(size=3).astype(X.dtype), ctx)
y = tvm.nd.array(np.random.uniform(size=3).astype(Y.dtype), ctx)
z = tvm.nd.empty(Z.shape, dtype=Z.dtype, ctx=ctx)

built_cast(x,y,z)

print(" x: " + str(x))
print(" y: " + str(y))
print(" z: " + str(z))
